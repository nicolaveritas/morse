#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "Morse";
const char *password = "";

#define UNIT_LENGTH    250
#define LED_PIN        LED_BUILTIN

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1>");
}

void handleMorse(String content) {
  Serial.println(content);
  const char * c = content.c_str();
  String morseWord = encode(c);
  Serial.println(morseWord);
  
  for (int i = 0; i <= morseWord.length(); i++)
  {
    switch ( morseWord[i] )
    {
      case '.': //dit
        digitalWrite( LED_PIN, LOW );
        delay( UNIT_LENGTH );
        digitalWrite( LED_PIN, HIGH );
        delay( UNIT_LENGTH );

        break;

      case '-': //dah
        digitalWrite( LED_PIN, LOW );
        delay( UNIT_LENGTH * 3 );
        digitalWrite( LED_PIN, HIGH );
        delay( UNIT_LENGTH );

        break;

      case ' ': //gap
        delay( UNIT_LENGTH );
    }
  }

  server.send(200, "text/plain", "Content is " + content + "\n" + morseWord);
}

void setup() {
  delay(1000);
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  
  Serial.println();
  Serial.print("Configuring access point...");
  
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);

  server.on("/morse", []() {
    String content = server.arg("content");
    handleMorse(content);
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
