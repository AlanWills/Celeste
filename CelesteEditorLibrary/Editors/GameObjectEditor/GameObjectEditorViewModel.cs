using BindingsKernel;
using CelesteEditor.Attributes;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEditor.Editors
{
    public class GameObjectEditorViewModel : EditorViewModel
    {
        #region Properties and Fields

        public GameObject GameObject { get { return TargetObject as GameObject; } }

        public ObservableCollection<Type> ComponentTypes { get; } = new ObservableCollection<Type>();

        #endregion

        public GameObjectEditorViewModel(GameObject targetGameObject) :
            base(targetGameObject)
        {
            RefreshComponentTypes();
        }

        #region Virtual Functions

        protected override void OnTargetObjectChanged()
        {
            base.OnTargetObjectChanged();

            RefreshComponentTypes();
        }

        #endregion

        #region Component Management

        private void RefreshComponentTypes()
        {
            ComponentTypes.Clear();

            if (GameObject != null)
            {
                foreach (Component component in GameObject.Components)
                {
                    ComponentTypes.Add(component.GetType());
                }
            }
        }

        public void AddComponent(Type type)
        {
            GameObject.Components.Add(Activator.CreateInstance(type) as Component);
            ComponentTypes.Add(type);
        }

        #endregion
    }
}
