using CelesteEditor.Views;
using MahApps.Metro.Controls;
using System;
using System.Linq;
using System.Windows;
using static CelesteEditor.Windows.EditorWindow;

namespace CelesteEditor.Windows
{
    /// <summary>
    /// A class which wraps up set up logic for various windows throughout our application
    /// </summary>
    public class EditorWindows : UtilityWindows
    {
        /// <summary>
        /// Returns a window containing information about the editor.
        /// </summary>
        public static EditorWindow AboutCelesteEditorWindow
        {
            get { return new ViewHostWindow(new AboutCelesteEditorView(), "About Celeste Engine Editor"); }
        }
    }
}