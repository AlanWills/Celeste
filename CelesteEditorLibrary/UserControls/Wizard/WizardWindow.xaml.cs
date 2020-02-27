using System.Windows.Controls;
using System.Windows;
using System.ComponentModel;
using System.Windows.Input;
using CelesteEditor.Windows;
using CelesteEditor.UserControls.Wizard;
using CelesteEditor.Converters;

namespace CelesteEditor.UserControls.Wizard
{
    /// <summary>
    /// Interaction logic for WizardWindow.xaml
    /// </summary>
    public partial class WizardWindow : EditorWindow
    {
        public enum WizardCloseType
        {
            kCheckWithUser,
            kForceClose
        }

        #region Properties and Fields

        private WizardPageView CurrentView { get; set; }

        /// <summary>
        /// If set to true, the user will not be asked before they close the wizard.
        /// </summary>
        public bool SuppressClosingCheck { get; set; }

        #endregion

        public WizardWindow(
            WizardPageView wizardPageView, 
            string title,
            ResizeMode resizeMode = ResizeMode.CanResizeWithGrip,
            SizeToContent sizeToContent = SizeToContent.Manual) : base(title, resizeMode, sizeToContent)
        {
            InitializeComponent();

            Navigate(wizardPageView);
        }

        public void Navigate(WizardPageView newView)
        {
            if (CurrentView != null)
            {
                // Cleanup old events to allow GCing
                CurrentView.ViewModel.PropertyChanged -= ViewModel_PropertyChanged;
            }

            // Attach new property changed event to detect buttons being enabled
            CurrentView = newView;
            CurrentView.ViewModel.PropertyChanged += ViewModel_PropertyChanged;

            BoolToCollapsedVisibilityConverter converter = new BoolToCollapsedVisibilityConverter();

            CancelButton.Visibility = (Visibility)converter.Convert(CurrentView.WizardViewModel.CancelButtonVisible);
            CancelButton.IsEnabled = CurrentView.WizardViewModel.CanCancel;
            CancelButton.Content = CurrentView.WizardViewModel.CancelButtonText;

			BackButton.Visibility = (Visibility)converter.Convert(CurrentView.WizardViewModel.BackButtonVisible);
			BackButton.IsEnabled = CurrentView.WizardViewModel.CanGoBack;
            BackButton.Content = CurrentView.WizardViewModel.BackButtonText;

            NextButton.Visibility = (Visibility)converter.Convert(CurrentView.WizardViewModel.NextButtonVisible);
            NextButton.IsEnabled = CurrentView.WizardViewModel.CanGoForward;
            NextButton.Content = CurrentView.WizardViewModel.NextButtonText;

            PageTitle.Text = CurrentView.WizardViewModel.Title;
            Description.Text = CurrentView.WizardViewModel.PageExplanation;
			Description.Visibility = (Visibility)converter.Convert(CurrentView.WizardViewModel.DescriptionVisible);		
			
			Frame.Navigate(CurrentView);

            // WPF Frames maintain a navigation history of content, clear this everytime we navigate to a new page.
            // This prevents 'Backspace' from changing the content
            NavigationCommands.BrowseBack.InputGestures.Clear();
            NavigationCommands.BrowseForward.InputGestures.Clear();
        }

        private void ViewModel_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            // YEAAAHHHHH
            // I wonder if there is a way to do data binding to these properties - I gave it a brief go and it didn't seem to work
            // But maybe I was missing a property changed invoke or something.
            if (e.PropertyName == nameof(CurrentView.WizardViewModel.CanGoForward))
            {
                NextButton.IsEnabled = CurrentView.WizardViewModel.CanGoForward;
            }
            else if (e.PropertyName == nameof(CurrentView.WizardViewModel.CanGoBack))
            {
                BackButton.IsEnabled = CurrentView.WizardViewModel.CanGoBack;
            }
            else if (e.PropertyName == nameof(CurrentView.WizardViewModel.CanCancel))
            {
                CancelButton.IsEnabled = CurrentView.WizardViewModel.CanCancel;
            }
            else if (e.PropertyName == nameof(CurrentView.WizardViewModel.NextButtonVisible))
            {
                NextButton.Visibility = (Visibility)new BoolToCollapsedVisibilityConverter().Convert(CurrentView.WizardViewModel.NextButtonVisible);
            }
            else if (e.PropertyName == nameof(CurrentView.WizardViewModel.BackButtonVisible))
            {
                BackButton.Visibility = (Visibility)new BoolToCollapsedVisibilityConverter().Convert(CurrentView.WizardViewModel.BackButtonVisible);
            }
            else if (e.PropertyName == nameof(CurrentView.WizardViewModel.CancelButtonVisible))
            {
                CancelButton.Visibility = (Visibility)new BoolToCollapsedVisibilityConverter().Convert(CurrentView.WizardViewModel.CancelButtonVisible);
            }
            else if (e.PropertyName == nameof(CurrentView.WizardViewModel.NextButtonText))
            {
                NextButton.Content = CurrentView.WizardViewModel.NextButtonText;
            }
            else if (e.PropertyName == nameof(CurrentView.WizardViewModel.BackButtonText))
            {
                BackButton.Content = CurrentView.WizardViewModel.BackButtonText;
            }
            else if (e.PropertyName == nameof(CurrentView.WizardViewModel.CancelButtonText))
            {
                CancelButton.Content = CurrentView.WizardViewModel.CancelButtonText;
            }
			else if (e.PropertyName == nameof(CurrentView.WizardViewModel.DescriptionVisible))
			{
				Description.Visibility = (Visibility)new BoolToCollapsedVisibilityConverter().Convert(CurrentView.WizardViewModel.DescriptionVisible);
			}
		}

        protected override void OnClosing(CancelEventArgs e)
        {
            if (!SuppressClosingCheck && !UtilityWindows.YesNoWindow("Are you sure you wish to close the " + Title + " wizard?  All progress will be lost.", "Confirm Close"))
            {
                e.Cancel = true;
                return;
            }

            base.OnClosing(e);
        }
        
        private void CloseWizard(object sender, RoutedEventArgs e)
        {
            CloseWithResult(UtilityWindows.WindowResult.Cancelled);
        }

        public void Back_Click(object sender, RoutedEventArgs e)
        {
            if (CurrentView.WizardViewModel.ConfirmToPreviousStep())
            {
                WizardPageView currentView = CurrentView;
                WizardPageView viewToTransitionTo = CurrentView.WizardViewModel.ToPreviousStep();

                if (viewToTransitionTo != null)
                {
                    Navigate(viewToTransitionTo);
                }

                currentView.WizardViewModel.OnPreviousStep();

                if (viewToTransitionTo == null)
                {
                    currentView.ViewModel.PropertyChanged -= ViewModel_PropertyChanged;
                    CloseWizard(sender, e);
                }
            }
        }

        public void Next_Click(object sender, RoutedEventArgs e)
        {
            if (CurrentView.WizardViewModel.ConfirmToNextStep())
            {
                WizardPageView currentView = CurrentView;
                WizardPageView viewToTransitionTo = CurrentView.WizardViewModel.ToNextStep();

                if (viewToTransitionTo != null)
                {
                    Navigate(viewToTransitionTo);
                }

                currentView.WizardViewModel.OnNextStep();

                if (viewToTransitionTo == null)
                {
                    currentView.ViewModel.PropertyChanged -= ViewModel_PropertyChanged;
                    CloseWizard(sender, e);
                }
            }
        }
    }
}