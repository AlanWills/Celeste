using BindingsKernel;
using CelesteEngineEditor.ViewModels;
using DevZest.Windows.Docking;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEngineEditor.Editors
{
    public abstract class HierarchyEntityViewModel : Notifier
    {
        #region Properties and Fields

        public Entity Entity { get; private set; }

        private bool isExpanded = true;
        /// <summary>
        /// A flag to indicate whether this item is expanded.
        /// </summary>
        public bool IsExpanded
        {
            get { return isExpanded; }
            set
            {
                if (isExpanded != value)
                {
                    isExpanded = value;
                    NotifyOnPropertyChanged(nameof(IsExpanded));
                }
            }
        }

        private bool isSelected = false;
        /// <summary>
        /// A flag to indicate whether this item is selected.
        /// </summary>
        public bool IsSelected
        {
            get { return isSelected; }
            set
            {
                if (isSelected != value)
                {
                    isSelected = value;
                    NotifyOnPropertyChanged(nameof(IsSelected));

                    if (isSelected)
                    {
                        // This line is to fix a bug between the hierarchy and other editors
                        // If we do not use Deselect, the current selection in the hierarchy will be destroyed by other dock items
                        // But the dock item needs to be open to be populated properly when an item is selected
                        Type editorType = Editor.GetEditorTypeForObject(Entity);
                        if (!Editor.IsEditorOpen(editorType))
                        {
                            Editor.OpenEditor(editorType);
                        }

                        Editor.OpenEditorForObject(Entity, DockItemShowMethod.Deselect);
                    }
                }
            }
        }

        /// <summary>
        /// A list of child game objects.
        /// </summary>
        public ObservableCollection<HierarchyGameObjectViewModel> ChildGameObjects { get; } = new ObservableCollection<HierarchyGameObjectViewModel>();

        protected Dictionary<string, HierarchyGameObjectViewModel> ChildGameObjectLookup { get; } = new Dictionary<string, HierarchyGameObjectViewModel>();

        #endregion

        public HierarchyEntityViewModel(Entity entity)
        {
            Entity = entity;
        }

        #region Game Object Utility Functions

        public bool HasChildGameObject(string gameObjectName)
        {
            return ChildGameObjectLookup.ContainsKey(gameObjectName);
        }

        public HierarchyGameObjectViewModel FindChildGameObject(string gameObjectName)
        {
            return HasChildGameObject(gameObjectName) ? ChildGameObjectLookup[gameObjectName] : null;
        }

        public void AddGameObjectOnUIThread(HierarchyGameObjectViewModel childGameObject)
        {
            //CelDebug.Assert(!HasChildGameObject(childGameObject.DisplayName));

            ChildGameObjectLookup[childGameObject.DisplayName] = childGameObject;
            ChildGameObjects.AddOnUIThread(childGameObject);

            OnAddGameObject(childGameObject);
        }

        public void RemoveGameObjectOnUIThread(HierarchyGameObjectViewModel childGameObject)
        {
            //CelDebug.Assert(HasChildGameObject(childGameObject.DisplayName));

            ChildGameObjectLookup.Remove(childGameObject.DisplayName);
            ChildGameObjects.RemoveOnUIThread(childGameObject);

            OnRemoveGameObject(childGameObject);
        }

        #endregion

        #region Virtual Functions

        protected virtual void OnAddGameObject(HierarchyGameObjectViewModel childGameObject) { }

        protected virtual void OnRemoveGameObject(HierarchyGameObjectViewModel childGameObject) { }

        #endregion
    }
}
