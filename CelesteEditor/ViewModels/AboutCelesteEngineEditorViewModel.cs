namespace CelesteEngineEditor.ViewModels
{
    public class AboutCelesteEngineEditorViewModel : Notifier
    {
        #region Properties and Fields

        public string CelesteEngineEditorDisplayString
        {
            get { return "Celeste Engine Editor v" + AppUtils.Version; }
        }

        #endregion
    }
}
