using CelesteEngineEditor.Attributes;
using CelesteEngineEditor.Editors;
using CelesteEngineEditor.Extensibility;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEngineEditor.Extensibility
{
    public static class EditorExtensibility
    {
        #region Properties and Fields

        private static List<Type> EditorsImpl { get; } = new List<Type>();

        private static ReadOnlyCollection<Type> editors;
        /// <summary>
        /// All of the available custom editors loaded into the application.
        /// Call LoadEditors to refresh this collection.
        /// </summary>
        public static ReadOnlyCollection<Type> Editors
        {
            get
            {
                if (editors == null)
                {
                    editors = new ReadOnlyCollection<Type>(EditorsImpl);
                    LoadEditors();
                }

                return editors;
            }
        }

        #endregion

        public static void LoadEditors()
        {
            EditorsImpl.Clear();

            Type editorType = typeof(Editor);
            foreach (Type type in ExtensibilityUtils.Types)
            {
                CustomEditorAttribute attribute = type.GetCustomAttribute<CustomEditorAttribute>();
                if (attribute != null && !type.IsAbstract && editorType.IsAssignableFrom(type))
                {
                    EditorsImpl.Add(type);
                }
            }
        }
    }
}