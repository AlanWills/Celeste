using BindingsKernel;
using CelesteEngineEditor.Core;
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
    public class SaveProjectCommand : BaseCommand
    {
        #region Abstract Overrides

        /// <summary>
        /// Returns true if there is a project loaded.
        /// </summary>
        /// <param name="parameter"></param>
        /// <returns></returns>
        public override bool CanExecute(object parameter = null)
        {
            return Project.Current != null;
        }
        
        /// <summary>
        /// Calls save on the currently loaded project.
        /// </summary>
        /// <param name="parameter"></param>
        public override void Execute(object parameter = null)
        {
            CelDebug.Assert(CanExecute(parameter));
            Project.Current.Save();
        }

        #endregion
    }
}