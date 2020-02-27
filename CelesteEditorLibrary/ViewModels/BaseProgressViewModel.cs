using CelesteEditor.Views;
using System;
using System.Threading;
using System.Threading.Tasks;
using static CelesteEditor.Windows.UtilityWindows;

namespace CelesteEditor.ViewModels
{
    public class BaseProgressViewModel : Notifier
	{
		#region Properties and Fields

		private Func<object[], ProgressMessageUpdateCallback, ProgressPercentageUpdateCallback, IsCancelledCallback, object> TaskToPerform { get; set; }

		private object[] Args { get; set; }

		protected CancellationTokenSource TokenSource { get; private set; }

		private CancellationToken Token { get; set; }

		public object TaskResult { get; private set; }

        public ProgressResult ProgressResult { get { return TokenSource.IsCancellationRequested ? ProgressResult.Cancelled : ProgressResult.Completed; } }
		
		public string ProgressMessage { get; private set; }

		public int ProgressPercentage { get; private set; }

		#endregion

		public BaseProgressViewModel(Func<object[], ProgressMessageUpdateCallback, ProgressPercentageUpdateCallback, IsCancelledCallback, object> task, object[] args)
		{
			TaskToPerform = task;
			Args = args;

			TokenSource = new CancellationTokenSource();
			Token = TokenSource.Token;
		}

		/// <summary>
		/// Start the task asynchronously.
		/// </summary>
		/// <returns></returns>
		public async void StartTaskAsync()
		{
			TaskResult = await Task.Run(() =>
			{
				return TaskToPerform.Invoke(Args, ProgressMessageCallback, ProgressPercentageCallback, CancellationRequested);
			});

			if (CancellationRequested())
				NotifyOnPropertyChanged("TaskCancelled");
			else
				NotifyOnPropertyChanged("TaskSuccessfullyCompleted");
		}

		public void Cancel()
		{
			TokenSource.Cancel();
		}

		/// <summary>
		/// A function that can be used to signal the UI to update.  Called from within the task and the
		/// inputted argument is a message from the task.
		/// Ensure that any UI that is updated is done so via it's Dispatcher.
		/// </summary>
		/// <param name="progressMessage"></param>
		protected virtual void ProgressMessageCallback(string progressMessage)
		{
            if (CancellationRequested())
            {
                // Do not update if cancelled
                return;
            }

			ProgressMessage = progressMessage;
			NotifyOnPropertyChanged(nameof(ProgressMessage));
		}

		protected virtual void ProgressPercentageCallback(int progressPercentage)
		{
            if (CancellationRequested())
            {
                // Do not update if cancelled
                return;
            }

            ProgressPercentage = progressPercentage;
			NotifyOnPropertyChanged(nameof(ProgressPercentage));
		}

		/// <summary>
		/// Returns whether the task has been cancelled by the user.
		/// </summary>
		/// <returns></returns>
		private bool CancellationRequested()
		{
			return Token.IsCancellationRequested;
		}
	}
}
