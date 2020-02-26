using CelesteEngineEditor.Core;
using CelesteEngineEditor.ViewModels;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEngineEditor.Editors
{
    public class EditorViewModel : Notifier
    {
        #region Properties and Fields

        private object targetObject;
        /// <summary>
        /// The object that is bound to the UI which we will be editing.
        /// </summary>
        public object TargetObject
        {
            get { return targetObject; }
            set
            {
                if (targetObject != value)
                {
                    targetObject = value;
                    NotifyOnPropertyChanged("");    // This should refresh all bindings automatically

                    OnTargetObjectChanged();
                }
            }
        }

        #endregion

        public EditorViewModel(object targetObject)
        {
            TargetObject = targetObject;
        }

        #region Virtual Functions

        /// <summary>
        /// A function called after the target object has explicitly changed.
        /// </summary>
        protected virtual void OnTargetObjectChanged() { }

        protected override void NotifyOnPropertyChanged(string propertyName)
        {
            base.NotifyOnPropertyChanged(propertyName);
            Project.SetDirty(TargetObject);
        }

        #endregion
    }
}
