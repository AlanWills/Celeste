using System;
using System.Windows;
using CelesteEditor.Windows;


namespace CelesteEditor.Views
{
    /// <summary>
    /// Interaction logic for ProgressView.xaml
    /// </summary>
    public partial class ProgressView : BaseProgressView
    {
		public ProgressView(string startingMessage, UtilityWindows.ProgressMode mode, Func<object[], ProgressMessageUpdateCallback, ProgressPercentageUpdateCallback, IsCancelledCallback, object> task, object[] args) :
            base(task, args)
        {
            InitializeComponent();
            Message.Text = startingMessage;

			PercentageComplete.IsIndeterminate = (mode == UtilityWindows.ProgressMode.Indeterminate);
		}

        /// <summary>
        /// Update the progress message
        /// </summary>
        /// <param name="progressMessage"></param>
        protected override void ProgressMessageCallback(string progressMessage)
        {
            Message.Dispatcher.Invoke(() => Message.Text = progressMessage);
        }

		/// <summary>
		/// Update the progress bar
		/// </summary>
		/// <param name="progressMessage"></param>
		protected override void ProgressPercentageCallback(int progressPercentage)
		{
			Message.Dispatcher.Invoke(() => PercentageComplete.Value = progressPercentage);
		}

		/// <summary>
		/// Cancels the task and closes the window.
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		protected override void Cancel_Click(object sender, RoutedEventArgs e)
		{
			base.Cancel_Click(sender, e);
			
			// Disable the button to force the user to wait for the task to get to a cancellable state
			Cancel.IsEnabled = false;

			Message.Text = "Cancelling...";
		}
	}
}
