using BindingsKernel;
using CelesteEngineEditor.Core;
using Microsoft.WindowsAPICodePack.Dialogs;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Input;

namespace CelesteEngineEditor.Commands
{
    public class LoadProjectCommand : BaseCommand
    {
        #region Abstract Overrides

        /// <summary>
        /// Returns true if the inputted object is null, an empty string or points to an existent directory.
        /// </summary>
        /// <param name="parameter"></param>
        /// <returns></returns>
        public override bool CanExecute(object parameter = null)
        {
            return parameter == null ||
                   (parameter is string && (string.IsNullOrEmpty(parameter as string) || Directory.Exists(parameter as string)));
        }
        
        /// <summary>
        /// If the inputted parameter is null or empty, we open a directory dialog browser to allow the user to choose a directory.
        /// If the inputted parameter is a valid directory, we load the project from the inputted directory.
        /// </summary>
        /// <param name="parameter"></param>
        public override void Execute(object parameter = null)
        {
            CelDebug.Assert(CanExecute(parameter));

            string directoryPath = parameter as string;
            if (string.IsNullOrEmpty(directoryPath) || !Directory.Exists(directoryPath))
            {
                // We have entered an invalid directory, so we open up a dialog to allow the player to choose a directory
                Tuple<CommonFileDialogResult, string> dialogResult = FileSystemUtils.PickDirectory();
                if (dialogResult.Item1 == CommonFileDialogResult.Cancel)
                {
                    // User cancelled the dialog, so we have nothing to load here.
                    return;
                }

                directoryPath = dialogResult.Item2;
            }

            Project.Load(directoryPath);
        }

        #endregion
    }
}