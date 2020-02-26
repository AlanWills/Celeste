using CelesteEngineEditor.ViewModels;

namespace CelesteEngineEditor.Views
{
    /// <summary>
    /// Interaction logic for AboutCelesteEngineEditorViews.xaml
    /// </summary>
    public partial class AboutCelesteEngineEditorView : BaseView
    {
        public AboutCelesteEngineEditorView() :
            base(new AboutCelesteEngineEditorViewModel())
        {
            InitializeComponent();
        }
    }
}
