using CelesteEditor.Attributes;
using CelesteEditor.Views;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEditor.Extensibility
{
    public static class MenuItemExtensibility
    {
        #region Properties and Fields

        private static List<MethodInfo> MenuItemsImpl { get; } = new List<MethodInfo>();

        private static ReadOnlyCollection<MethodInfo> menuItems;
        /// <summary>
        /// All of the available menu items loaded into the application.
        /// Call LoadMenuItems to refresh this collection.
        /// </summary>
        public static ReadOnlyCollection<MethodInfo> MenuItems
        {
            get
            {
                if (menuItems == null)
                {
                    menuItems = new ReadOnlyCollection<MethodInfo>(MenuItemsImpl);
                    LoadMenuItems();
                }

                return menuItems;
            }
        }

        #endregion

        public static void LoadMenuItems()
        {
            MenuItemsImpl.Clear();

            foreach (Type type in ExtensibilityUtils.Types)
            {
                if (!type.IsAbstract)
                {
                    foreach (MethodInfo methodInfo in type.GetMethods(BindingFlags.Static | BindingFlags.Public))
                    {
                        if (methodInfo.GetCustomAttribute<CustomMenuItemAttribute>() != null)
                        {
                            MenuItemsImpl.Add(methodInfo);
                        }
                    }
                }
            }
        }
    }
}
