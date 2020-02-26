using CelesteEngineEditor.Attributes;
using CelesteEngineEditor.Extensibility;
using DevZest.Windows.Docking;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace CelesteEngineEditor.Editors
{
    public class Editor : UserControl
    {
        #region Properties and Fields

        /// <summary>
        /// The view model which provides the data context for this editor UI.
        /// </summary>
        public EditorViewModel ViewModel { get; }

        private static DockControl DockControl
        {
            get { return Application.Current.MainWindow.FindFirstChild<DockControl>("DockControl"); }
        }

        #endregion

        public Editor(EditorViewModel viewModel)
        {
            ViewModel = viewModel;
            DataContext = viewModel;
        }

        #region Utility Functions

        public static Type GetEditorTypeForObject(object targetObject)
        {
            if (targetObject != null)
            {
                Type targetType = targetObject.GetType();
                foreach (Type type in EditorExtensibility.Editors)
                {
                    CustomEditorAttribute customEditorAttribute = type.GetCustomAttribute<CustomEditorAttribute>();
                    if (type != typeof(Inspector) && customEditorAttribute.TargetType.IsAssignableFrom(targetType))
                    {
                        // Don't want to carry on iterating through custom editors any more
                        return type;
                    }
                }
            }

            return typeof(Inspector);
        }

        public static bool IsEditorOpen<T>() where T : Editor
        {
            return IsEditorOpen(typeof(T));
        }

        public static bool IsEditorOpen(Type editorType)
        {
            DockControl dockControl = DockControl;

            foreach (DockItem dockItem in dockControl.DockItems)
            {
                Type type = (dockItem.Content as ScrollViewer).Content.GetType();
                if (type.IsAssignableFrom(editorType))
                {
                    return true;
                }
            }

            return false;
        }

        #endregion

        #region Open Editor For Object Functions

        /// <summary>
        /// Opens the inputted editor for the inputted object type.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="targetObject"></param>
        public static Editor OpenEditorForObject(
            Type editorType,
            object targetObject,
            DockItemShowMethod dockItemShowMethod = DockItemShowMethod.Select)
        {
            CustomEditorAttribute customEditorAttribute = editorType.GetCustomAttribute<CustomEditorAttribute>();
            return OpenEditor(
                editorType,
                targetObject,
                customEditorAttribute.DisplayName,
                customEditorAttribute.DockPosition,
                dockItemShowMethod);
        }

        /// <summary>
        /// Opens an editor for the inputted object type.
        /// If a custom editor is registered it is opened, otherwise we fall back onto the default inspector.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="targetObject"></param>
        public static Editor OpenEditorForObject(
            object targetObject,
            DockItemShowMethod dockItemShowMethod = DockItemShowMethod.Select)
        {
            Type editorType = GetEditorTypeForObject(targetObject);
            CustomEditorAttribute customEditorAttribute = editorType.GetCustomAttribute<CustomEditorAttribute>();

            return OpenEditor(
                editorType, 
                targetObject, 
                customEditorAttribute.DisplayName, 
                customEditorAttribute.DockPosition, 
                dockItemShowMethod);
        }

        #endregion

        #region Open Editor Functions

        /// <summary>
        /// Opens the editor of the inputted type using it's default custom editor attribute values.
        /// </summary>
        /// <param name="editorType"></param>
        public static Editor OpenEditor(Type editorType)
        {
            CustomEditorAttribute customEditorAttribute = editorType.GetCustomAttribute<CustomEditorAttribute>();
            return OpenEditor(editorType, null, customEditorAttribute.DisplayName, customEditorAttribute.DockPosition);
        }

        /// <summary>
        /// Opens the editor of the inputted type using it's default position, but overriding the display name and tab name with the inputted value.
        /// </summary>
        /// <param name="editorType"></param>
        public static Editor OpenEditor(Type editorType, string editorDisplayName)
        {
            CustomEditorAttribute customEditorAttribute = editorType.GetCustomAttribute<CustomEditorAttribute>();
            return OpenEditor(editorType, null, editorDisplayName, customEditorAttribute.DockPosition);
        }

        /// <summary>
        /// Opens the editor of the inputted type using it's default position, but overriding the display name and tab name with the inputted value.
        /// </summary>
        /// <param name="editorType"></param>
        public static Editor OpenEditor(
            Type editorType, 
            DockPosition dockPosition,
            DockItemShowMethod dockItemShowMethod = DockItemShowMethod.Select)
        {
            CustomEditorAttribute customEditorAttribute = editorType.GetCustomAttribute<CustomEditorAttribute>();
            return OpenEditor(editorType, null, customEditorAttribute.DisplayName, dockPosition, dockItemShowMethod);
        }

        /// <summary>
        /// Opens the editor of the inputted type using the inputted position, but overriding the display name and tab name with the inputted value.
        /// </summary>
        /// <param name="editorType"></param>
        public static Editor OpenEditor(
            Type editorType, 
            object targetObject,
            string editorDisplayName, 
            DockPosition dockPosition, 
            DockItemShowMethod dockItemShowMethod = DockItemShowMethod.Select)
        {
            DockControl control = DockControl;
            
            CustomEditorAttribute customEditorAttribute = editorType.GetCustomAttribute<CustomEditorAttribute>();
            DockItem editor = control.DockItems.FirstOrDefault(x => x.Title == customEditorAttribute.DisplayName);

            if (editor == null)
            {
                ScrollViewer scrollViewer = new ScrollViewer()
                {
                    Content = Activator.CreateInstance(editorType, new object[] { targetObject })
                };

                editor = new DockItem()
                {
                    Title = editorDisplayName,
                    TabText = editorDisplayName,
                    ShowAction = new ShowAsDockPositionAction() { DockPosition = dockPosition },
                    DefaultDockPosition = dockPosition,
                    Content = scrollViewer
                };
            }
            else
            {
                editor.Title = editorDisplayName;
                editor.TabText = editorDisplayName;
                ((editor.Content as ScrollViewer).Content as Editor).ViewModel.TargetObject = targetObject;
            }

            editor.Show(control, dockPosition, dockItemShowMethod);
            return editor.Content as Editor;
        }

        #endregion
    }
}