using CelesteEngineEditor.ViewModels;
using System.Windows;
using System.Windows.Controls;
using static CelesteEngineEditor.Windows.UtilityWindows;

namespace CelesteEngineEditor.Views
{
    public abstract class BaseView : Page
    {
        #region Properties and Fields
        public Notifier ViewModel { get; private set; }

        #endregion

        public BaseView() { }

        public BaseView(Notifier viewModel)
        {
            ViewModel = viewModel;
            DataContext = viewModel;
        }
        
        /// <summary>
        /// A function called no matter the dialog result, just before we close the hosting window.
        /// </summary>
        protected virtual void OnCloseWindow() { }

        /// <summary>
        /// A callback used to close the containing window with a success result
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected virtual void CloseWindow_Success(object sender, RoutedEventArgs e)
        {
            OnCloseWindow();
            this.CloseWindow(WindowResult.Success);
        }

        /// <summary>
        /// A callback used to close the containing window with a failure result.
        /// Consider using IsCancel in the Xaml as this may provide all the functionality you require.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected virtual void CloseWindow_Failure(object sender, RoutedEventArgs e)
        {
            OnCloseWindow();
            this.CloseWindow(WindowResult.Failure);
        }

        /// <summary>
        /// A callback used to cancel the containing window
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected virtual void CloseWindow_Cancel(object sender, RoutedEventArgs e)
        {
            OnCloseWindow();
            this.CloseWindow(WindowResult.Cancelled);
        }
    }
}