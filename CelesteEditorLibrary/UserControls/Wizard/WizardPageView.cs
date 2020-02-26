using CelesteEngineEditor.Views;

namespace CelesteEngineEditor.UserControls.Wizard
{
    public abstract class WizardPageView : BaseView
    {
        #region Properties and Fields

        public WizardPageViewModel WizardViewModel { get; private set; }

        #endregion

        public WizardPageView(WizardPageViewModel viewModel) :
            base(viewModel)
        {
            WizardViewModel = viewModel;
            viewModel.WizardPage = this;
        }
	}
}