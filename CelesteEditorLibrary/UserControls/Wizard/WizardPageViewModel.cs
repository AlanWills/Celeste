using BindingsKernel;
using CelesteEngineEditor;
using CelesteEngineEditor.UserControls.Wizard;
using CelesteEngineEditor.ViewModels;
using System.Windows;
using static CelesteEngineEditor.Windows.UtilityWindows;
using static CelesteEngineEditor.UserControls.Wizard.WizardWindow;

namespace CelesteEngineEditor.UserControls.Wizard
{
    public abstract class WizardPageViewModel : Notifier
    {
        #region Properties and Fields

        /// <summary>
        /// The string displayed at the top of each wizard page view.
        /// </summary>
        public abstract string Title { get; }

        /// <summary>
        /// The string displayed under the title to explain the purpose of the wizard page view
        /// </summary>
        public abstract string PageExplanation { get; }

        /// <summary>
        /// A flag to indicate whether the cancel button is visible in the wizard for this page.
        /// </summary>
        public virtual bool CancelButtonVisible { get { return true; } }
		
		public virtual bool DescriptionVisible { get { return true; } }
		
		/// <summary>
		/// A flag to indicate whether the cancel button is visible in the wizard for this page.
		/// </summary>
		public virtual bool CanCancel { get { return true; } }

        /// <summary>
        /// The text that will be displayed on the cancel button.
        /// </summary>
        public virtual string CancelButtonText { get { return "Cancel"; } }

        /// <summary>
        /// A flag to indicate whether the back button is visible in the wizard for this page.
        /// </summary>
        public virtual bool BackButtonVisible { get { return true; } }

        /// <summary>
        /// A flag to indicate whether we are able to go to the previous page view in the wizard
        /// </summary>
        public virtual bool CanGoBack { get { return BackButtonVisible; } }

        /// <summary>
        /// The text that will be displayed on the back button.
        /// </summary>
        public virtual string BackButtonText { get { return "Back"; } }

        /// <summary>
        /// A flag to indicate whether the next button is visible in the wizard for this page.
        /// </summary>
        public virtual bool NextButtonVisible { get { return true; } }

        /// <summary>
        /// A flag to indicate whether we are able to go to the next page view in the wizard
        /// </summary>
        public virtual bool CanGoForward { get { return NextButtonVisible; } }

        /// <summary>
        /// The text that will be displayed on the next button.
        /// </summary>
        public virtual string NextButtonText { get { return "Next"; } }

        /// <summary>
        /// Do not use this.  This is set automatically by the wizard and used to close the wizard from the view model.
        /// Not pretty, but this is the best way to do this I can think of for now.
        /// </summary>
        public WizardPageView WizardPage { private get; set; }

        #endregion

        /// <summary>
        /// Refreshes all of the cancel button properties in the following order:
        /// CancelButtonVisible
        /// CanCancel
        /// CancelButtonText
        /// </summary>
        public void RefreshCancelProperties()
        {
            NotifyOnPropertyChanged(nameof(CancelButtonVisible));
            NotifyOnPropertyChanged(nameof(CanCancel));
            NotifyOnPropertyChanged(nameof(CancelButtonText));
        }

        /// <summary>
        /// Refreshes all of the back button properties in the following order:
        /// BackButtonVisible
        /// CanGoBack
        /// BackButtonText
        /// </summary>
        public void RefreshBackProperties()
        {
            NotifyOnPropertyChanged(nameof(BackButtonVisible));
            NotifyOnPropertyChanged(nameof(CanGoBack));
            NotifyOnPropertyChanged(nameof(BackButtonText));
        }

        /// <summary>
        /// Refreshes all of the next button properties in the following order:
        /// NextButtonVisible
        /// CanGoForward
        /// NextButtonText
        /// </summary>
        public void RefreshNextProperties()
        {
            NotifyOnPropertyChanged(nameof(NextButtonVisible));
            NotifyOnPropertyChanged(nameof(CanGoForward));
            NotifyOnPropertyChanged(nameof(NextButtonText));
        }

        /// <summary>
        /// A function called when the back button is pressed.  Allows this page to cancel the back progression.
        /// Return true to continue progressing backwards.
        /// Return false to cancel the progression.
        /// </summary>
        /// <returns></returns>
        public virtual bool ConfirmToPreviousStep() { return true; }

        /// <summary>
        /// Move to the previous page view in the wizard
        /// </summary>
        /// <returns></returns>
        public abstract WizardPageView ToPreviousStep();

        /// <summary>
        /// A function which should be called after we navigate to the next page view in the wizard
        /// </summary>
        public abstract void OnPreviousStep();

        /// <summary>
        /// A function called when the next button is pressed.  Allows this page to cancel the next progression.
        /// Return true to continue progressing backwards.
        /// Return false to cancel the progression.
        /// Base implementation returns true.
        /// </summary>
        /// <returns></returns>
        public virtual bool ConfirmToNextStep() { return true; }

        /// <summary>
        /// Move to the next page view in the wizard
        /// </summary>
        /// <returns></returns>
        public abstract WizardPageView ToNextStep();

        /// <summary>
        /// A function which should be called after we navigate to the previous page view in the wizard
        /// </summary>
        public abstract void OnNextStep();

        /// <summary>
        /// Advance to the next page of the wizard.
        /// </summary>
        public void NextPage()
        {
            if (SuppressUI)
            {
                // If we are not using the UI, we do not need to do anything here
                return;
            }

            WizardWindow window = GetParentWizardWindow();

			window.Next_Click(null, new RoutedEventArgs());
        }

        /// <summary>
        /// Go back to the previous page of the wizard.
        /// </summary>
        public void PreviousPage()
        {
            if (SuppressUI)
            {
                // If we are not using the UI, we do not need to do anything here
                return;
            }

            WizardWindow window = GetParentWizardWindow();

			window.Back_Click(null, new RoutedEventArgs());
        }

        /// <summary>
        /// Closes the wizard window this viewmodel is contained within.
        /// The second parameter is used to control whether we check with the user before closing.
        /// </summary>
        public void CloseWizard(WindowResult windowResult, WizardCloseType closeType = WizardCloseType.kCheckWithUser)
        {
            if (SuppressUI)
            {
                // If we are not using the UI, we can just quit here
                return;
            }

			WizardWindow window = GetParentWizardWindow();
            
			window.SuppressClosingCheck = closeType == WizardCloseType.kForceClose;
            window.CloseWithResult(windowResult);
        }

		public WizardWindow GetParentWizardWindow()
		{
			WizardWindow window = WizardPage.FindFirstParent<WizardWindow>();
			CelDebug.AssertNotNull(window);

			return window;
		}
	}
}