using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEditor.Commands
{
    public static class EditorCommands
    {
        #region Properties and Fields

        /// <summary>
        /// Returns a new instance of the LoadProjectCommand.
        /// </summary>
        public static LoadProjectCommand LoadProjectCommand
        {
            get { return new LoadProjectCommand(); }
        }

        /// <summary>
        /// Returns a new instance of the SaveProjectCommand.
        /// </summary>
        public static SaveProjectCommand SaveProjectCommand
        {
            get { return new SaveProjectCommand(); }
        }

        #endregion
    }
}
