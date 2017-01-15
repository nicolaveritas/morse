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
			client.GetAsync("http://192.168.4.1/morse?content=" + entry.Text);
		}
	}
}
