using BindingsKernel;
using CelesteEngineEditor.Extensibility;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEngineEditor.Extensibility
{
    public static class ComponentExtensibility
    {
        #region Properties and Fields

        private static List<Type> ComponentsImpl { get; set; } = new List<Type>();

        private static ReadOnlyCollection<Type> components;
        /// <summary>
        /// All of the available custom editors loaded into the application.
        /// Call LoadEditors to refresh this collection.
        /// </summary>
        public static ReadOnlyCollection<Type> Components
        {
            get
            {
                if (components == null)
                {
                    components = new ReadOnlyCollection<Type>(ComponentsImpl);
                    LoadComponents();
                }

                return components;
            }
        }

        #endregion

        /// <summary>
        /// Iterate through all DLLs in same location as the editor and load all non-abstract classes derived from Component.
        /// </summary>
        public static void LoadComponents()
        {
            ComponentsImpl.Clear();

            // Go through each DLL
            foreach (Type type in ExtensibilityUtils.Types)
            {
                if (!type.IsAbstract && type.IsSubclassOf(typeof(Component)))
                {
                    ComponentsImpl.Add(type);
                }
            }
        }
    }
}
