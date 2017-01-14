using Xamarin.Forms;

namespace morse
{
	public partial class App : Application
	{
		public App()
		{
			InitializeComponent();

			MainPage = new morsePage();
		}

		protected override void OnStart()
		{
			// Handle when your app starts
		}

		protected override void OnSleep()
		{
			// Handle when your app sleeps
		}

		protected override void OnResume()
		{
			// Handle when your app resumes
		}
	}
}
