using BindingsKernel;
using CelesteEngineEditor.Assets;
using CelesteEngineEditor.Extensibility;
using System.IO;

namespace CelesteEngineEditor.AssetLoaders
{
    public class ScreenAssetLoader : AssetLoader
    {
        #region Properties and Fields

        /// <summary>
        /// The file extension which this loader is responsible for loading into a project asset.
        /// </summary>
        public const string FileExtension = ".screen";

        /// <summary>
        /// The file extension which this loader is responsible for loading into a project asset.
        /// </summary>
        public override string AssetFileExtension { get { return FileExtension; } }

        #endregion

        #region Load Functions

        public override IAsset Load(FileInfo file)
        {
            return new ScreenAsset(file, Screen.Load(file, ComponentExtensibility.Components));
        }

        #endregion
    }
}