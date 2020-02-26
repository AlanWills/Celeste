using CelesteEngineEditor.Attributes;
using CelesteEngineEditor.Editors;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace CelesteEngineEditor.UserControls.MainMenu.MenuItemContexts
{
    public class EditorMenuItemContext : MenuItemContext
    {
        #region Properties and Fields

        private Type EditorType { get; set; }

        #endregion

        public EditorMenuItemContext(Type editorType) :
            base(editorType.GetCustomAttribute<CustomMenuItemAttribute>().MenuItemPath)
        {
            EditorType = editorType;
        }

        #region Abstract Overrides

        public override MenuItem CreateMenuItem()
        {
            MenuItem item = base.CreateMenuItem();
            item.DataContext = EditorType;
            item.Click += EditorItem_Click;

            return item;
        }

        #endregion

        private static void EditorItem_Click(object sender, RoutedEventArgs e)
        {
            MenuItem menuItem = sender as MenuItem;
            Type type = menuItem.DataContext as Type;

            Editor.OpenEditor(type);
        }
    }
}
