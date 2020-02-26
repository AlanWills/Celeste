using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace CelesteEngineEditor.UserControls.MainMenu.MenuItemContexts
{
    public class MenuItemContext
    {
        #region Properties and Fields

        public string Name { get; private set; }
        public string ParentPath { get; private set; }

        #endregion

        public MenuItemContext(string fullMenuItemPath)
        {
            Name = GetMenuItemName(fullMenuItemPath);
            ParentPath = GetParentPath(fullMenuItemPath);
        }

        #region Virtual Functions

        public virtual MenuItem CreateMenuItem()
        {
            MenuItem item = new MenuItem();
            item.Header = Name;
            item.Style = Application.Current.FindResource("DefaultSubMenuItem") as Style;

            return item;
        }

        #endregion

        #region Utility Functions

        private string GetMenuItemName(string fullMenuItemPath)
        {
            int lastIndexOf = fullMenuItemPath.LastIndexOf('/');
            return lastIndexOf < 0 ? fullMenuItemPath : fullMenuItemPath.Substring(lastIndexOf + 1);
        }

        private string GetParentPath(string fullMenuItemPath)
        {
            int lastIndexOf = fullMenuItemPath.LastIndexOf('/');
            return lastIndexOf < 0 ? "" : fullMenuItemPath.Substring(0, lastIndexOf);
        }

        #endregion
    }
}
