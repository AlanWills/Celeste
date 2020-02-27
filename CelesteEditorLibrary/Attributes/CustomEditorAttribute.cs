using DevZest.Windows.Docking;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEditor.Attributes
{
    public class CustomEditorAttribute : Attribute
    {
        #region Properties and Fields

        public Type TargetType { get; }

        public DockPosition DockPosition { get; }
        
        public string DisplayName { get; }

        #endregion

        public CustomEditorAttribute(string displayName, DockPosition dockPosition = DockPosition.Right) :
            this(typeof(void), displayName, dockPosition)
        {
        }
        
        public CustomEditorAttribute(Type targetType, string displayName, DockPosition dockPosition = DockPosition.Right)
        {
            TargetType = targetType;
            DisplayName = displayName;
            DockPosition = dockPosition;
        }
    }
}