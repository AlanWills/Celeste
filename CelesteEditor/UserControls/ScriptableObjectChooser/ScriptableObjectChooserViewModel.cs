using BindingsKernel;
using CelesteEngineEditor.Core;
using CelesteEngineEditor.Editors;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEngineEditor.UserControls
{
    public class ScriptableObjectChooserViewModel : EditorViewModel
    {
        #region Properties and Fields

        /// <summary>
        /// A list of all of the available scriptable object assets within the project
        /// </summary>
        public ObservableCollection<ScriptableObjectAsset> AvailableItems { get; } = new ObservableCollection<ScriptableObjectAsset>();

        private ScriptableObjectAsset selectedItem;
        /// <summary>
        /// The currently selected item within the UI.
        /// </summary>
        public ScriptableObjectAsset SelectedItem
        {
            get { return selectedItem; }
            set
            {
                selectedItem = value;
                NotifyOnPropertyChanged(nameof(SelectedItem));
            }
        }

        /// <summary>
        /// Returns the underlying scriptable object that has been chosen within the UI.
        /// </summary>
        public ScriptableObject SelectedScriptableObject
        {
            get { return selectedItem?.ScriptableObject; }
            set
            {
                // Go through all the items to find the matching ScriptableObjectAsset
            }
        }

        #endregion

        public ScriptableObjectChooserViewModel(Type scriptableObjectType)
        {
            foreach (ScriptableObjectAsset scriptableObjectAsset in Project.Current.FindAllAssetsOfType<ScriptableObjectAsset>())
            {
                if (scriptableObjectType.IsAssignableFrom(scriptableObjectAsset.ScriptableObject.GetType()))
                {
                    AvailableItems.Add(scriptableObjectAsset);
                }
            }
        }
    }
}
