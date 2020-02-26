namespace CelesteEngineEditor.Views
{
    /// <summary>
    /// Interaction logic for MessageView.xaml
    /// </summary>
    public partial class YesNoView : BaseView
    {
        public YesNoView(string message, string yesButtonText = "Yes", string noButtonText = "No")
        {
            InitializeComponent();

            // Call initialize first to create the text
            Message.Text = message;

            YesButton.Content = yesButtonText;
            NoButton.Content = noButtonText;
        }
	}
}
