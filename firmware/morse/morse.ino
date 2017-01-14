#include <ESP8266WiFi.h>

//////////////////////
// WiFi Definitions //
//////////////////////
const char WiFiAPPSK[] = "sparkfun";

/////////////////////
// Pin Definitions //
/////////////////////
const int LED_PIN = LED_BUILTIN; // Thing's onboard, green LED

////////////////////
// Morse Unit def //
////////////////////
#define UNIT_LENGTH    250

//Build a struct with the morse code mapping
static const struct {
  const char letter, *code;
} MorseMap[] =
{
  { 'A', ".-" },
  { 'B', "-..." },
  { 'C', "-.-." },
  { 'D', "-.." },
  { 'E', "." },
  { 'F', "..-." },
  { 'G', "--." },
  { 'H', "...." },
  { 'I', ".." },
  { 'J', ".---" },
  { 'K', ".-.-" },
  { 'L', ".-.." },
  { 'M', "--" },
  { 'N', "-." },
  { 'O', "---" },
  { 'P', ".--." },
  { 'Q', "--.-" },
  { 'R', ".-." },
  { 'S', "..." },
  { 'T', "-" },
  { 'U', "..-" },
  { 'V', "...-" },
  { 'W', ".--" },
  { 'X', "-..-" },
  { 'Y', "-.--" },
  { 'Z', "--.." },
  { ' ', "     " }, //Gap between word, seven units

  { '1', ".----" },
  { '2', "..---" },
  { '3', "...--" },
  { '4', "....-" },
  { '5', "....." },
  { '6', "-...." },
  { '7', "--..." },
  { '8', "---.." },
  { '9', "----." },
  { '0', "-----" },

  { '.', "·–·–·–" },
  { ',', "--..--" },
  { '?', "..--.." },
  { '!', "-.-.--" },
  { ':', "---..." },
  { ';', "-.-.-." },
  { '(', "-.--." },
  { ')', "-.--.-" },
  { '"', ".-..-." },
  { '@', ".--.-." },
  { '&', ".-..." },
};


WiFiServer server(80);

void setup()
{
  initHardware();
  setupWiFi();
  server.begin();
}

void loop()
{
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }


  // Read the first line of the request
  String req = client.readStringUntil('H');
  req.toLowerCase();
  Serial.println(req);
  if (req.charAt(0) == 'g') return;
  else {
    
    const char * c = req.c_str();
    //Serial.println(c);
    String morseWord = encode(c);
    Serial.println(morseWord);
    Serial.println(morseWord.length());
    for (int i = 34; i <= morseWord.length(); i++)
    {
      Serial.println(morseWord[i]);
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
  }

  client.flush();
}

void setupWiFi()
{
  WiFi.mode(WIFI_AP);

  // Do a little work to get a unique-ish name. Append the
  // last two bytes of the MAC (HEX'd) to "Thing-":
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) +
                 String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  String AP_NameString = "ESP8266 Thing " + macID;

  char AP_NameChar[AP_NameString.length() + 1];
  memset(AP_NameChar, AP_NameString.length() + 1, 0);

  for (int i = 0; i < AP_NameString.length(); i++)
    AP_NameChar[i] = AP_NameString.charAt(i);

  WiFi.softAP(AP_NameChar, WiFiAPPSK);
}

void initHardware()
{
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
}

String encode(const char *string)
{
  size_t i, j;
  String morseWord = "";

  for ( i = 0; string[i]; ++i )
  {
    for ( j = 0; j < sizeof MorseMap / sizeof * MorseMap; ++j )
    {
      if ( toupper(string[i]) == MorseMap[j].letter )
      {
        morseWord += MorseMap[j].code;
        break;
      }
    }
    morseWord += " "; //Add tailing space to seperate the chars
  }

  return morseWord;
}
