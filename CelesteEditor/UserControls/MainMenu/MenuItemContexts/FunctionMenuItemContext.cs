using CelesteEditor.Attributes;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace CelesteEditor.UserControls.MainMenu.MenuItemContexts
{
    public class FunctionMenuItemContext : MenuItemContext
    {
        #region Properties and Fields

        private MethodInfo Function { get; set; }

        #endregion

        public FunctionMenuItemContext(MethodInfo function) :
            base(function.GetCustomAttribute<CustomMenuItemAttribute>().MenuItemPath)
        {
            Function = function;
        }

        #region Abstract Overrides

        public override MenuItem CreateMenuItem()
        {
            MenuItem item = base.CreateMenuItem();
            item.Click += (object sender, RoutedEventArgs e) => { Function.Invoke(null, null); };

            return item;
        }

        #endregion
    }
}
