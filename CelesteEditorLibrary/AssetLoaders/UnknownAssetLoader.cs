using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using CelesteEngineEditor.Assets;

namespace CelesteEngineEditor.AssetLoaders
{
    public class UnknownAssetLoader : AssetLoader
    {
        #region Properties and Fields

        /// <summary>
        /// Returns the empty string - this asset loader should be used explicitly and not accidently matched up to assets with another valid loader.
        /// </summary>
        public override string AssetFileExtension { get { return ""; } }

        #endregion

        #region AssetLoader Overrides

        /// <summary>
        /// Returns an unknown asset which we can use as a placeholder.
        /// </summary>
        /// <param name="file"></param>
        /// <returns></returns>
        public override IAsset Load(FileInfo file)
        {
            return new UnknownAsset(file, new object());
        }

        #endregion
    }
}
