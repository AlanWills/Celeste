using System.Windows;
using System.Windows.Controls;

namespace CelesteEditor.Views
{
    /// <summary>
    /// Interaction logic for YesNoCancelView.xaml
    /// </summary>
    public partial class YesNoCancelView : BaseView
    {
        public YesNoCancelView(string message, string yesButtonLabel = "Yes", string noButtonLabel = "No", string cancelButtonLabel = "Cancel")
        {
            InitializeComponent();

            // Call initialize first to create the text
            Message.Text = message;
            YesButton.Content = yesButtonLabel;
            NoButton.Content = noButtonLabel;
            CancelButton.Content = cancelButtonLabel;
        }
    }
}