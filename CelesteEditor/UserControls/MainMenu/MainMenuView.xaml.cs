using BindingsKernel;
using CelesteEditor.Attributes;
using CelesteEditor.Editors;
using CelesteEditor.Extensibility;
using CelesteEditor.UserControls.MainMenu.MenuItemContexts;
using DevZest.Windows.Docking;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Windows;
using System.Windows.Controls;

namespace CelesteEditor.UserControls
{
    /// <summary>
    /// Interaction logic for MainMenuView.xaml
    /// </summary>
    public partial class MainMenuView : UserControl
    {
        #region Properties and Fields

        private MainMenuViewModel MainMenu { get; set; } = new MainMenuViewModel();

        #endregion

        public MainMenuView()
        {
            DataContext = MainMenu;
            InitializeComponent();

            AddMenuItems();
        }

        #region Menu Item Utility Functions

        private void AddMenuItems()
        {
            List<MenuItemContext> contexts = CollectMenuItems();
            Dictionary<string, MenuItem> menuItemLookup = new Dictionary<string, MenuItem>();

            foreach (MenuItemContext context in contexts)
            {
                MenuItem menuItem = context.CreateMenuItem();
                
                if (string.IsNullOrEmpty(context.ParentPath))
                {
                    EditorItem.Items.Add(menuItem);
                    menuItemLookup.Add(context.Name, menuItem);
                }
                else if (menuItemLookup.ContainsKey(context.ParentPath))
                {
                    menuItemLookup[context.ParentPath].Items.Add(menuItem);
                    menuItemLookup.Add(context.ParentPath + "/" + context.Name, menuItem);
                }
                else
                {
                    CelDebug.Fail();
                }
            }
        }

        private List<MenuItemContext> CollectMenuItems()
        {
            HashSet<string> foundItems = new HashSet<string>();
            List<MenuItemContext> menuItemContexts = new List<MenuItemContext>();

            foreach (Type type in EditorExtensibility.Editors)
            {
                CustomMenuItemAttribute menuItemAttribute = type.GetCustomAttribute<CustomMenuItemAttribute>();
                if (menuItemAttribute != null)
                {
                    AddParentMenuContexts(menuItemAttribute, menuItemContexts, foundItems);

                    MenuItemContext menuItemContext = new EditorMenuItemContext(type);
                    menuItemContexts.Add(menuItemContext);
                    foundItems.Add(menuItemContext.ParentPath);
                }
            }

            foreach (MethodInfo methodInfo in MenuItemExtensibility.MenuItems)
            {
                CustomMenuItemAttribute menuItemAttribute = methodInfo.GetCustomAttribute<CustomMenuItemAttribute>();
                CelDebug.AssertNotNull(menuItemAttribute);

                AddParentMenuContexts(menuItemAttribute, menuItemContexts, foundItems);

                MenuItemContext menuItemContext = new FunctionMenuItemContext(methodInfo);
                menuItemContexts.Add(menuItemContext);
                foundItems.Add(menuItemContext.ParentPath);
            }

            menuItemContexts.Sort((a, b) => { return b.ParentPath.Count(x => x == '/') - a.ParentPath.Count(x => x == '/'); });

            return menuItemContexts;
        }

        private void Concatenate(string[] strs, int index, StringBuilder builder)
        {
            builder.ToString();

            for (int i = 0; i < index + 1; ++i)
            {
                builder.Append(strs[i]);
            }
        }

        private void AddParentMenuContexts(CustomMenuItemAttribute menuItemAttribute, List<MenuItemContext> menuItemContexts, HashSet<string> foundItems)
        {
            string[] subSections = menuItemAttribute.MenuItemPath.Split(new[] { '/' }, StringSplitOptions.RemoveEmptyEntries);
            StringBuilder builder = new StringBuilder(menuItemAttribute.MenuItemPath.Length);

            // Don't include last name because that will be the actual menu item
            for (int i = 0; i < subSections.Length - 1; ++i)
            {
                Concatenate(subSections, i, builder);

                if (!foundItems.Contains(builder.ToString()))
                {
                    MenuItemContext context = new MenuItemContext(builder.ToString());
                    menuItemContexts.Add(context);
                    foundItems.Add(context.ParentPath);
                }
            }
        }

        #endregion

        #region Click Callbacks

        private void NewProject_Click(object sender, RoutedEventArgs e)
        {
            MainMenu.NewProject();
        }

        private void OpenProject_Click(object sender, RoutedEventArgs e)
        {
            MainMenu.OpenProject();
        }
        
        private void SaveProject_Click(object sender, RoutedEventArgs e)
        {
            MainMenu.SaveProject();
        }
        
        private void Exit_Click(object sender, RoutedEventArgs e)
        {
            MainMenu.Exit();
        }
        
        private void AboutCelesteEditor_Click(object sender, RoutedEventArgs e)
        {
            MainMenu.AboutCelesteEditor();
        }

        #endregion
    }
}