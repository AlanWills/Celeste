using BindingsKernel;
using CelesteEngineEditor.Core;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEngineEditor.Settings
{
    [Serializable]
    public class LocalSettings
    {
        #region Properties and Fields

        private static LocalSettings instance;
        /// <summary>
        /// Singleton instance of the local settings.
        /// Will automatically load the settings when first referenced.
        /// </summary>
        public static LocalSettings Instance
        {
            get
            {
                if (instance == null)
                {
                    Load();
                }

                return instance;
            }
        }

        /// <summary>
        /// The path to the local settings file containing non-essential application instance data.
        /// Can be deleted to revert application back to default settings.
        /// </summary>
        public static string LocalSettingsFilePath
        {
            get { return System.IO.Path.Combine(AppUtils.AppDataFolderFullPath, "LocalSettings.settings"); }
        }

        /// <summary>
        /// The full location to the directory we last opened as a project.
        /// </summary>
        public string LastOpenedProjectLocation { get; set; } = "";

        #endregion

        private LocalSettings()
        {
        }

        #region Saving

        public void Save()
        {
            // Clear/create the file if it exists
            FileSystemUtils.CleanFile(LocalSettingsFilePath);

            try
            {
                // Catch the situation where we can't serialize the file
                File.WriteAllText(LocalSettingsFilePath, JsonConvert.SerializeObject(instance, Formatting.Indented));
            }
            catch { CelDebug.Fail(); }
        }

        #endregion

        #region Loading

        public static void Load()
        {
            if (!File.Exists(LocalSettingsFilePath))
            {
                instance = new LocalSettings();
                return;
            }

            try
            {
                // Catch the situation where we can't deserialize the file
                // and create a new instance otherwise.
                instance = JsonConvert.DeserializeObject<LocalSettings>(File.ReadAllText(LocalSettingsFilePath));

                // Don't do anything too drastic post load.  I tried to load the project here, but things went wrong
                // because other bits and bobs weren't set up correctly
            }
            catch (Exception e)
            {
                CelDebug.Fail(e.Message);
                instance = new LocalSettings();
            }
        }

        #endregion
    }
}
