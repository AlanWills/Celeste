using BindingsKernel;
using CelesteEngineEditor.Assets;
using CelesteEngineEditor.Core;
using System.IO;

namespace CelesteEngineEditor.AssetLoaders
{
    public class JpgAssetLoader : AssetLoader
    {
        #region Properties and Fields

        /// <summary>
        /// The file extension which this loader is responsible for loading into a project asset.
        /// </summary>
        public const string FileExtension = ".jpg";

        /// <summary>
        /// The file extension which this loader is responsible for loading into a project asset.
        /// </summary>
        public override string AssetFileExtension { get { return FileExtension; } }

        #endregion

        #region Load Functions

        /// <summary>
        /// Load the scriptable object asset and return it.
        /// Returns null if this process did not succeed.
        /// </summary>
        /// <param name="filePath"></param>
        /// <returns></returns>
        public override IAsset Load(FileInfo file)
        {
            return new Texture2DAsset(file, new Texture2D());
        }

        #endregion
    }
}
