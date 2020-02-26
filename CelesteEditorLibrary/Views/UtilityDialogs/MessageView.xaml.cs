using System.Windows.Controls;

namespace CelesteEngineEditor.Views
{
    /// <summary>
    /// Interaction logic for MessageView.xaml
    /// </summary>
    public partial class MessageView : BaseView
    {
        public MessageView(string message, string okText)
        {
            InitializeComponent();

            // Call initialize first to create the text
            Message.Text = message;
			OkButton.Content = okText;
        }
    }
}
