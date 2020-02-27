using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEditor.Attributes
{
    public class FileIconAttribute : Attribute
    {
        #region Properties and Fields

        /// <summary>
        /// The file extension we are mapping to a custom icon source.
        /// </summary>
        public string FileExtension { get; }

        /// <summary>
        /// The relative path from the project directory to the icon.
        /// </summary>
        public string IconSource { get; }

        #endregion

        public FileIconAttribute(string fileExtension, string iconSource)
        {
            FileExtension = fileExtension;
            IconSource = iconSource;
        }
    }
}