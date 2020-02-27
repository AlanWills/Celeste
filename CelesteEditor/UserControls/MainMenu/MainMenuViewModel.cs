using CelesteEditor.Commands;
using CelesteEditor.ViewModels;
using CelesteEditor.Windows;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Windows;

namespace CelesteEditor.UserControls
{
    public class MainMenuViewModel : Notifier
    {
        #region Menus

        #region File Submenu
        
        /// <summary>
        /// Creates a new project.
        /// </summary>
        public void NewProject()
        {
            //if (DesktopCommands.ResetPlatformCommand.CanExecute())
            //{
            //    DesktopCommands.ResetPlatformCommand.Execute();
            //}
        }

        /// <summary>
        /// Open an existing project.
        /// </summary>
        /// <param name="stlxFile"></param>
        public void OpenProject()
        {
            if (EditorCommands.LoadProjectCommand.CanExecute())
            {
                EditorCommands.LoadProjectCommand.Execute();
            }
        }
        
        /// <summary>
        /// Saves the project.
        /// </summary>
        /// <param name="stlxFilePath"></param>
        public void SaveProject()
        {
            if (EditorCommands.SaveProjectCommand.CanExecute())
            {
                EditorCommands.SaveProjectCommand.Execute();
            }
        }
        
        /// <summary>
        /// Closes the program
        /// </summary>
        public void Exit()
        {
            Application.Current.MainWindow.Close();
        }

        #endregion
        
        #region Help Submenu

        /// <summary>
        /// Launches a modal dialog with information about the editor.  
        /// Therefore we are guaranteed only one instance of this window, so don't need to do any checks on that.
        /// </summary>
        public void AboutCelesteEditor()
        {
            EditorWindows.AboutCelesteEditorWindow.ShowDialog();
        }
        
        #endregion
        
		#endregion
	}
}