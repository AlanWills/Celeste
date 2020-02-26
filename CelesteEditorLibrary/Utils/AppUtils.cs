using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEngineEditor
{
    public static class AppUtils
    {
        #region Properties and Fields

        /// <summary>
        /// The name of the application.
        /// </summary>
        public const string Name = "Celeste Engine Editor";

        /// <summary>
        /// The current published version of the editor.
        /// </summary>
        public static Version Version
        {
            get { return Assembly.GetEntryAssembly().GetName().Version; }
        }

        /// <summary>
        /// The directory in the user's local AppData where we store temporary data.
        /// </summary>
        public static string AppDataFolderFullPath { get; set; } = Path.Combine(Path.GetTempPath(), Name);
        
        /// <summary>
        /// Returns the directory of the current running executable.
        /// </summary>
        /// <returns></returns>
        public static string InstallLocation
        {
            get { return Directory.GetParent(Assembly.GetEntryAssembly()?.Location)?.FullName; }
        }

        #endregion
    }
}
