using CelesteEditor.Views;
using System;
using static CelesteEditor.Windows.EditorWindow;

namespace CelesteEditor.Windows
{
    /// <summary>
    /// A class which wraps up set up logic for various windows throughout our application
    /// </summary>
    public class UtilityWindows
    {
        /// <summary>
        /// An enum used for dialog boxes which have both a No and Cancel option to enable differentiating
        /// between these two cases.
        /// </summary>
        public enum WindowResult
        {
            Success,
            Failure,
            Cancelled,
        }

        public enum ProgressMode
		{
			Determinate,
			Indeterminate,
		}

        public enum ProgressResult
        {
            Completed,
            Cancelled,
        }

        /// <summary>
        /// A flag we can use to suppress the blocking message dialog boxes.
        /// Useful in unit tests to prevent blocking of test runs by planned errors.
        /// </summary>
        public static bool SuppressUI { get; set; } = false;
        
        /// <summary>
        /// Creates a blocking message box with the inputted message and title.
        /// </summary>
        /// <param name="message"></param>
        /// <param name="title"></param>
        public static void MessageWindow(
            string message, 
            string title = "Error", 
            CloseButtonVisibility closeButtonVisibility = CloseButtonVisibility.kShown,
			string okText = "OK")
        {
            if (!SuppressUI)
            {
                ViewHostWindow window = new ViewHostWindow(new MessageView(message, okText),title);
                window.ShowCloseButton = closeButtonVisibility == CloseButtonVisibility.kShown;
                window.ShowDialog();
            }
        }

        /// <summary>
        /// Creates a blocking yes, no dialog box with the inputted message and title.
        /// Returns true if the user clicks on Yes.  Returns false if the user clicks on No or the dialog is suppressed.
        /// If suppressed, returns true.
        /// </summary>
        /// <param name="message"></param>
        /// <param name="title"></param>
        /// <returns></returns>
        public static bool YesNoWindow(
            string message, 
            string title = "Error", 
            string yesButtonLabel = "Yes", 
            string noButtonLabel = "No")
        {
            if (!SuppressUI)
            {
                bool? result = new ViewHostWindow(new YesNoView(message, yesButtonLabel, noButtonLabel), title).ShowDialog();
                return result.HasValue && result.Value;
            }

            return true;
        }

        /// <summary>
        /// Creates a blocking yes, no, cancel dialog box with the inputted message and title.
        /// Returns WindowResult.Success if the user clicks on Yes.  
        /// Returns WindowResult.Failure if the user clicks on No.
        /// Returns WindowResult.Cancelled if the user clicks on Cancel.
        /// If suppressed, returns true.
        /// </summary>
        /// <param name="message"></param>
        /// <param name="title"></param>
        /// <returns></returns>
        public static WindowResult YesNoCancelWindow(
            string message,
            string title = "Error",
            string yesButtonLabel = "Yes",
            string noButtonLabel = "No",
            string cancelButtonLabel = "Cancel",
            CloseButtonVisibility closeButtonVisibility = CloseButtonVisibility.kShown)
        {
            if (!SuppressUI)
            {
                EditorWindow window = new ViewHostWindow(new YesNoCancelView(message, yesButtonLabel, noButtonLabel, cancelButtonLabel), title);
                window.ShowCloseButton = closeButtonVisibility == CloseButtonVisibility.kShown;
                window.ShowDialog();

                return window.WindowResult;
            }

            return WindowResult.Success;
        }

        /// <summary>
        /// Creates a blocking ok, cancel dialog box with the inputted message and title.
        /// Returns true if the user clicks on OK.  Returns false if the user clicks on Cancel or the dialog is suppressed.
        /// If suppressed, returns true.
        /// </summary>
        /// <param name="message"></param>
        /// <param name="title"></param>
        /// <returns></returns>
        public static bool OKCancelWindow(
            string message, 
            string title = "Error",
            CloseButtonVisibility closeButtonVisibility = CloseButtonVisibility.kShown)
        {
            if (!SuppressUI)
            {
                ViewHostWindow window = new ViewHostWindow(new YesNoView(message, "OK", "Cancel"), title);
                window.ShowCloseButton = closeButtonVisibility == CloseButtonVisibility.kShown;

                bool? result = window.ShowDialog();
                return result.HasValue && result.Value;
            }

            return true;
        }

        /// <summary>
		/// Wrapper function for general usage.
        /// </summary>
        /// <param name="message"></param>
        /// <param name="title"></param>
        /// <returns></returns>
        public static Tuple<ProgressResult, T> ProgressWindow<T>(
            string title, 
            string startingMessage,
			ProgressMode mode,
			Func<object[], ProgressMessageUpdateCallback, ProgressPercentageUpdateCallback, IsCancelledCallback, T> task, 
            params object[] args)
        {
            return ProgressWindow<ProgressView, T>(title, startingMessage, mode, task, args);
        }

		/// <summary>
		/// Creates a progress dialog that performs a task in a background worker with the inputted view as the hosted UI.
		/// Provides an aynschronous way to update the user on a task's progress.
		/// The task to perform takes a generic list of objects for it's arguments, to allow passing of several arguments.
		/// The Action<string> is a callback for updating the text on the window.  Simply call it and pass your message.
		/// This function will return a tuple containing whether the task was cancelled and the result of the task.
		/// </summary>
		/// <param name="message"></param>
		/// <param name="title"></param>
		/// <returns></returns>
		public static Tuple<ProgressResult, K> ProgressWindow<T, K>(
            string title, 
            string startingMessage,
			ProgressMode mode,
			Func<object[], ProgressMessageUpdateCallback, ProgressPercentageUpdateCallback, IsCancelledCallback, K> task, 
            params object[] args) where T : BaseProgressView
        {
            // We have to do this weird templating rather than passing the view in, because we cannot create
            // UI stuff in unit tests.  Therefore, if we passed the view in, we would have no way of running the task
            // without also generating the UI and so we would not be able to separate the task from the UI.

            if (SuppressUI)
                return new Tuple<ProgressResult, K>(ProgressResult.Completed, task.Invoke(args, (string str) => { }, (int perc) => { }, () => { return false; }));

            // Have to cast the function to return an object for the ProgressView constructor
            Func<object[], ProgressMessageUpdateCallback, ProgressPercentageUpdateCallback, IsCancelledCallback, object> viewFunc = (object[] parameters, ProgressMessageUpdateCallback messageCallback, ProgressPercentageUpdateCallback percentageCallback, IsCancelledCallback cancelledCallback) =>
            {
                return task.Invoke(parameters, messageCallback, percentageCallback, cancelledCallback);
            };

            T view = (T)Activator.CreateInstance(typeof(T), startingMessage, mode, viewFunc, args);
            ViewHostWindow window = new ViewHostWindow(view, title);
            window.ShowCloseButton = false;
            window.ShowDialog();

            K result = view.BaseProgress.TaskResult is K ? (K)view.BaseProgress.TaskResult : default(K);
            return new Tuple<ProgressResult, K>(view.BaseProgress.ProgressResult, result);
        }
    }
}