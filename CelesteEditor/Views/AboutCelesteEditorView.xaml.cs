using CelesteEditor.ViewModels;

namespace CelesteEditor.Views
{
    /// <summary>
    /// Interaction logic for AboutCelesteEditorViews.xaml
    /// </summary>
    public partial class AboutCelesteEditorView : BaseView
    {
        public AboutCelesteEditorView() :
            base(new AboutCelesteEditorViewModel())
        {
            InitializeComponent();
        }
    }
}
