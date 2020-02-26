using BindingsKernel;
using CelesteEngineEditor.Attributes;
using CelesteEngineEditor.Extensibility;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEngineEditor.Extensibility
{
    public static class FileIconExtensibility
    {
        #region Properties and Fields

        /// <summary>
        /// The default Uri we use if we cannot find a custom icon for a file extension.
        /// </summary>
        private static string DefaultUri { get; set; } = "pack://application:,,,/CelesteEngineEditor;component/Icons/New.ico";

        private static Dictionary<string, string> fileExtensionToIconLookup;
        /// <summary>
        /// A dictionary we use to provide an association between a file extension and an icon Uri.
        /// </summary>
        private static Dictionary<string, string> FileExtensionToIconLookup
        {
            get
            {
                if (fileExtensionToIconLookup == null)
                {
                    LoadIcons();
                }

                return fileExtensionToIconLookup;
            }
        }

        #endregion

        public static void LoadIcons()
        {
            fileExtensionToIconLookup = new Dictionary<string, string>();

            foreach (Type type in ExtensibilityUtils.Types)
            {
                FileIconAttribute fileIconAttribute = type.GetCustomAttribute<FileIconAttribute>();
                if (fileIconAttribute != null)
                {
                    if (!fileExtensionToIconLookup.ContainsKey(fileIconAttribute.FileExtension))
                    {
                        StringBuilder builder = new StringBuilder("pack://application:,,,/");
                        builder.Append(type.Assembly.GetName().Name);
                        builder.Append(";component/");
                        builder.Append(fileIconAttribute.IconSource);

                        fileExtensionToIconLookup.Add(fileIconAttribute.FileExtension, builder.ToString());
                    }
                    else
                    {
                        CelDebug.Fail();
                    }
                }
            }
        }

        /// <summary>
        /// Obtain a file icon for the inputted file extension.
        /// If no custom icon is set, we return the default icon Uri.
        /// </summary>
        /// <param name="fileExtension"></param>
        /// <returns></returns>
        public static string GetFileIconForExtension(string fileExtension)
        {
            return FileExtensionToIconLookup.ContainsKey(fileExtension) ? FileExtensionToIconLookup[fileExtension] : DefaultUri;
        }
    }
}
