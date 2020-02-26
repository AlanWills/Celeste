using CelesteEngineEditor.ViewModels;
using System;
using System.ComponentModel;
using System.Windows;
using static CelesteEngineEditor.Windows.UtilityWindows;

namespace CelesteEngineEditor.Views
{
    public delegate void ProgressMessageUpdateCallback(string message);
	public delegate void ProgressPercentageUpdateCallback(int percentage);
	public delegate bool IsCancelledCallback();

    public abstract class BaseProgressView : BaseView
    {
        #region Properties and Fields

		public BaseProgressViewModel BaseProgress { get; private set; }
        
		#endregion

		public BaseProgressView(Func<object[], ProgressMessageUpdateCallback, ProgressPercentageUpdateCallback, IsCancelledCallback, object> task, object[] args)
        {
			BaseProgress = new BaseProgressViewModel(task, args);

			// Subscribe to events from the model
			BaseProgress.PropertyChanged += BaseProgress_PropertyChanged;

			DataContext = BaseProgress;

            Loaded += BaseProgressView_Loaded;
        }
        
        private void BaseProgressView_Loaded(object sender, RoutedEventArgs e)
        {
			// Start the task only when the UI has finished loading
			BaseProgress.StartTaskAsync();
        }

		private void BaseProgress_PropertyChanged(object sender, PropertyChangedEventArgs e)
		{
			if (e.PropertyName == "TaskSuccessfullyCompleted")
			{
				// If the task was not cancelled it must have run to completion
				Dispatcher.Invoke(() => { this.CloseWindow(WindowResult.Success); });
			}
			else if (e.PropertyName == "TaskCancelled")
			{
				// If the task was not cancelled it must have run to completion
				Dispatcher.Invoke(() => { this.CloseWindow(WindowResult.Cancelled); });
			}
			else if (e.PropertyName == "ProgressMessage")
			{
				ProgressMessageCallback(BaseProgress.ProgressMessage);
			}
			else if (e.PropertyName == "ProgressPercentage")
			{
				ProgressPercentageCallback(BaseProgress.ProgressPercentage);
			}
		}

		/// <summary>
		/// A function that can be used to signal the UI to update.  Called from within the task and the
		/// inputted argument is a message from the task.
		/// Ensure that any UI that is updated is done so via it's Dispatcher.
		/// </summary>
		/// <param name="progressMessage"></param>
		protected abstract void ProgressMessageCallback(string progressMessage);
		
		protected abstract void ProgressPercentageCallback(int progressPercentage);

		/// <summary>
		/// Cancels the task
		/// </summary>
		/// <param name="sender"></param>
		/// <param name="e"></param>
		protected virtual void Cancel_Click(object sender, RoutedEventArgs e)
        {
			BaseProgress.Cancel();
        }
    }
}