using BindingsKernel;
using MahApps.Metro.Controls;
using System.Windows;
using static CelesteEngineEditor.Windows.UtilityWindows;

namespace CelesteEngineEditor.Windows
{
    public abstract class EditorWindow : MetroWindow
    {        
        public enum CloseButtonVisibility
        {
            kHidden,
            kShown
        }

        #region Properties and Fields

        /// <summary>
        /// An enum to allow us to distinguish between all close cases for a window.
        /// </summary>
        public WindowResult WindowResult { get; set; } = WindowResult.Cancelled;

        #endregion

        public EditorWindow(
            string title = "",
            ResizeMode resizeMode = ResizeMode.NoResize,
            SizeToContent sizeToContent = SizeToContent.WidthAndHeight)
        {
            Title = title;

            // Ensures this window always appears on top of the main window (if it exists and is not this window)
            if (Application.Current.MainWindow != null && 
                Application.Current.MainWindow != this)
            {
                Owner = Application.Current.MainWindow;
            }

            ResizeMode = resizeMode;
            SizeToContent = sizeToContent;
        }

        public void CloseWithResult(WindowResult result)
        {
            WindowResult = result;

            if (System.Windows.Interop.ComponentDispatcher.IsThreadModal)
            {
                // Assigning the dialog result will close the window
                switch (result)
                {
                    case WindowResult.Success:
                        DialogResult = true;
                        break;

                    case WindowResult.Failure:
                        DialogResult = false;
                        break;

                    case WindowResult.Cancelled:
                        DialogResult = false;
                        break;

                    default:
                        CelDebug.Fail("Unhandled WindowResult case");
                        break;
                }
            }
            else
            {
                Close();
            }
        }
    }
}
