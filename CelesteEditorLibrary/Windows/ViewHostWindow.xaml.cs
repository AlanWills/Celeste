using System.Windows.Controls;
using System.Windows;
using CelesteEngineEditor.Views;

namespace CelesteEngineEditor.Windows
{
    /// <summary>
    /// Interaction logic for ViewHostWindow.xaml
    /// </summary>
    public partial class ViewHostWindow : EditorWindow
    {
        #region Properties and Fields

        public BaseView View { get; private set; }

        #endregion

        public ViewHostWindow(
            BaseView view, 
            string title, 
            ResizeMode resizeMode = ResizeMode.NoResize, 
            SizeToContent sizeToContent = SizeToContent.WidthAndHeight) : base(title, resizeMode, sizeToContent)
        {
            View = view;

            Loaded += ViewHostWindow_Loaded;
            InitializeComponent();
            Frame.Navigate(view);
        }

        private void ViewHostWindow_Loaded(object sender, RoutedEventArgs e)
        {
            // Ok this looks totally nuts, but I can explain
            // When you set the window to width & height content sizing, it doesn't calculate the size until after it calculates it's position
            // So the dialog top left always appears in the centre of the screen
            // This code moves the dialog so the centre of the dialog is in the centre of the screen
            if (SizeToContent == SizeToContent.WidthAndHeight)
            {
                View.Measure(new Size(double.PositiveInfinity, double.PositiveInfinity));
                View.Arrange(new Rect(0, 0, DesiredSize.Width, DesiredSize.Height));
                Measure(new Size(double.PositiveInfinity, double.PositiveInfinity));
                Arrange(new Rect(0, 0, DesiredSize.Width, DesiredSize.Height));

                // DO NOT DELETE THE + 1
                // I'm like, super serious - without it, apparently WPF calculates things incorrectly.........

                // Width of View + Margin on frame
                Width = View.ActualWidth + Frame.Margin.Left + Frame.Margin.Right + 1;

                // Height of View + Height of Window (title bar + vertical frame margins)
                Height = View.ActualHeight + ActualHeight + 1;

                if (Owner != null)
                {
                    double top = Owner.Top + ((Owner.Height - Height) / 2);
                    double left = Owner.Left + ((Owner.Width - Width) / 2);

                    // Move the window
                    Top = top < 0 ? 0 : top;
                    Left = left < 0 ? 0 : left;
                }

                // Now prevent any other resizing happening automatically
                SizeToContent = SizeToContent.Manual;
            }
        }
    }
}