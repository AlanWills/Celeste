using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace CelesteEngineEditor.Commands
{
    public abstract class BaseCommand : ICommand
    {
        #region Events

        public event EventHandler CanExecuteChanged;

        #endregion

        #region Abstract Functions

        /// <summary>
        /// A function used to validate whether this command can be run.
        /// Returns true if the input and current state allows Execute to complete successfully.
        /// </summary>
        /// <param name="parameter"></param>
        /// <returns></returns>
        public abstract bool CanExecute(object parameter = null);

        /// <summary>
        /// Execute the command using the inputted parameter and state.
        /// </summary>
        /// <param name="parameter"></param>
        public abstract void Execute(object parameter = null);

        #endregion
    }
}
