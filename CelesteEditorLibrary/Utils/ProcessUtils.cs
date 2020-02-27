using System.Diagnostics;
using System.IO;
using System.Reflection;

namespace CelesteEditor
{
    public static class ProcessUtils
    {
        /// <summary>
        /// Returns true if a process already exists with the name of the Entry Assembly of the calling code.
        /// Returns false otherwise.
        /// </summary>
        /// <returns></returns>
        public static bool IsCurrentProcessRunning()
        {
            return Process.GetProcessesByName(Path.GetFileNameWithoutExtension(Assembly.GetEntryAssembly().Location)).Length > 1;
        }

        /// <summary>
        /// Returns true if a process with the inputted name is already running.
        /// Returns false otherwise.
        /// </summary>
        /// <param name="processName"></param>
        /// <returns></returns>
        public static bool IsProcessRunning(string processName)
        {
            return Process.GetProcessesByName(processName).Length > 0;
        }
    }
}
