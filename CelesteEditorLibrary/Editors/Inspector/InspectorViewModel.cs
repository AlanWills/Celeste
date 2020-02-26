using BindingsKernel;
using CelesteEngineEditor.Data;
using CelesteEngineEditor.Editors;
using CelesteEngineEditor.ViewModels;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEngineEditor.Editors
{
    public class InspectorViewModel : EditorViewModel
    {
        #region Properties and Fields
        
        /// <summary>
        /// All of the available properties that can be set on the target object.
        /// </summary>
        public ObservableCollection<PropertyData> PropertyData { get; private set; } = new ObservableCollection<PropertyData>();

        #endregion
        
        public InspectorViewModel(object targetObject) :
            base(targetObject)
        {
        }

        protected override void OnTargetObjectChanged()
        {
            base.OnTargetObjectChanged();

            RebuildPropertyData();
        }

        private void RebuildPropertyData()
        {
            PropertyData.Clear();

            if (TargetObject == null)
            {
                return;
            }
            
            List<PropertyData> data = new List<PropertyData>();
            foreach (PropertyInfo info in TargetObject?.GetType().GetProperties(BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.SetProperty | BindingFlags.GetProperty))
            {
                // Only add the properties which we should be serializing
                if (info.GetCustomAttribute<SerializeAttribute>() != null)
                {
                    data.Add(new PropertyData(TargetObject, info));
                }
            }

            // Sort the property data so that it is in the correct specified display order
            data.Sort((PropertyData lhs, PropertyData rhs) =>
            {
                return lhs.DisplayPriority - rhs.DisplayPriority;
            });

            foreach (PropertyData info in data)
            {
                PropertyData.Add(info);
            }

            NotifyOnPropertyChanged(nameof(PropertyData));
        }
    }
}
