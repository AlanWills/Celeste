using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEditor.Attributes
{
    public class CustomMenuItemAttribute : Attribute
    {
        #region Properties and Fields

        public string MenuItemPath { get; private set; }

        #endregion

        public CustomMenuItemAttribute(string menuItemPath)
        {
            MenuItemPath = menuItemPath;
        }
    }
}
