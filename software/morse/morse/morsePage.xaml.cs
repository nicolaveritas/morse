using Xamarin.Forms;
using System.Net.Http;
using System.Text;

namespace morse
{
	public partial class morsePage : ContentPage
	{

		HttpClient client;

		public morsePage()
		{
			InitializeComponent();
			client = new HttpClient();
		}

		void Turn_on(object sender, System.EventArgs e)
		{
			var content = new StringContent("0", Encoding.UTF8, "text/plain");
			client.PostAsync("http://192.168.4.1/led/" + entry.Text, null);
			client.GetAsync("http://192.168.4.1/");
		}
	}
}
