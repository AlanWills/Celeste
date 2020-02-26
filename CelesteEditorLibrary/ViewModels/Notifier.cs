using System.ComponentModel;

namespace CelesteEngineEditor.ViewModels
{
    /// <summary>
    /// An implementation of the INotifyPropertyChanged interface which allows other classes to inherit a unified interface implementation.
    /// </summary>
    public class Notifier : INotifyPropertyChanged
    {
        #region Properties and Fields

        public event PropertyChangedEventHandler PropertyChanged;

        #endregion

        /// <summary>
        /// Triggers any events subscribed when we change a value.
        /// </summary>
        /// <param name="propertyName"></param>
        protected virtual void NotifyOnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
