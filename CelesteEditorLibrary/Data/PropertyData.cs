using BindingsKernel;
using CelesteEngineEditor.Assets;
using CelesteEngineEditor.Core;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace CelesteEngineEditor.Data
{
    public class PropertyData
    {
        // Should go in VM
        public string DisplayName { get; set; }

        public string XmlName { get; set; }

        private object val;
        public object Value
        {
            get { return PropertyInfo.GetValue(Parent); }
            set
            {
                if (val != value)
                {
                    Project.SetDirty(Parent);
                }

                val = value;
                PropertyInfo.SetValue(Parent, val);
            }
        }
        
        // Should go in VM
        public bool IsReadOnly { get; set; }

        // Should go in VM
        public int DisplayPriority { get; set; } = int.MaxValue;

        public Type Type { get { return PropertyInfo.PropertyType; } }

        private object Parent { get; set; }
        private PropertyInfo PropertyInfo { get; set; }

        public PropertyData(object parent, PropertyInfo propertyInfo)
        {
            DisplayName = propertyInfo.GetCustomAttribute<DisplayNameAttribute>()?.DisplayName ?? propertyInfo.Name;
            XmlName = propertyInfo.GetCustomAttribute<XmlAttributeAttribute>()?.AttributeName ?? propertyInfo.Name;
            val = propertyInfo.GetValue(parent);
            IsReadOnly = propertyInfo.GetCustomAttribute<IsReadOnlyAttribute>() != null;
            Parent = parent;
            PropertyInfo = propertyInfo;

            DisplayPriorityAttribute displayPriority = propertyInfo.GetCustomAttribute<DisplayPriorityAttribute>();
            if (displayPriority != null)
            {
                DisplayPriority = displayPriority.Priority;
            }
        }

        // Need a view model for this which will dictate whether it's read only and a display string
    }
}
