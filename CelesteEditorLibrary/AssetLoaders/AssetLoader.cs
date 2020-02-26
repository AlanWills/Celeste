using CelesteEngineEditor.Assets;
using CelesteEngineEditor.Core;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEngineEditor.AssetLoaders
{
    public abstract class AssetLoader
    {
        #region Properties and Fields

        /// <summary>
        /// The file extension for this loader which it is capable of loading into an asset.
        /// </summary>
        public abstract string AssetFileExtension { get; }

        #endregion

        #region Loading Functions

        /// <summary>
        /// Attempts to load the inputted file as a project asset.
        /// Will return the newly created project asset if this process was a success and null if not.
        /// </summary>
        /// <param name="filePath"></param>
        /// <returns></returns>
        public abstract IAsset Load(FileInfo file);

        #endregion
    }
}
