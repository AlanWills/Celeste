using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace CelTestSharp
{
    public class Resources
    {
        #region Directories

        /// <summary>
        /// A directory for temporary data which will be cleared after every test beginning and end,
        /// every class beginning and end and at the beginning and end of every test run.
        /// </summary>
        public static string TempDir { get; } = Path.Combine(Directory.GetCurrentDirectory(), "Temp");

        #endregion

        /// <summary>
        /// Make sure no-one can create an instance of this class.
        /// </summary>
        private Resources()
        {
        }

        #region Utility Functions

        /// <summary>
        /// Deletes the temp directory and all it's contents and then recreates it afresh.
        /// </summary>
        public static void CleanTempDir()
        {
            if (Directory.Exists(TempDir))
            {
                Directory.Delete(TempDir, true);
            }

            Directory.CreateDirectory(TempDir);
        }

        #endregion
    }
}
