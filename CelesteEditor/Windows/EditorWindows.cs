using CelesteEngineEditor.Views;
using MahApps.Metro.Controls;
using System;
using System.Linq;
using System.Windows;
using static CelesteEngineEditor.Windows.EditorWindow;

namespace CelesteEngineEditor.Windows
{
    /// <summary>
    /// A class which wraps up set up logic for various windows throughout our application
    /// </summary>
    public class EditorWindows : UtilityWindows
    {
        /// <summary>
        /// Returns a window containing information about the editor.
        /// </summary>
        public static EditorWindow AboutCelesteEngineEditorWindow
        {
            get { return new ViewHostWindow(new AboutCelesteEngineEditorView(), "About Celeste Engine Editor"); }
        }
    }
}