using BindingsKernel;
using CelesteEngineEditor.AssetLoaders;
using CelesteEngineEditor.Assets;
using CelesteEngineEditor.Extensibility;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;

namespace CelesteEngineEditor.Core.AssetLoaders
{
    public static class AssetLoaderExtensibility
    {
        #region Properties and Fields

        private static Dictionary<string, AssetLoader> AssetLoadersImpl { get; set; } = new Dictionary<string, AssetLoader>();

        private static ReadOnlyDictionary<string, AssetLoader> assetLoaders;
        /// <summary>
        /// All of the available custom asset loaders loaded into the application.
        /// Call LoadAssetLoaders to refresh this collection.
        /// </summary>
        public static ReadOnlyDictionary<string, AssetLoader> AssetLoaders
        {
            get
            {
                if (assetLoaders == null)
                {
                    assetLoaders = new ReadOnlyDictionary<string, AssetLoader>(AssetLoadersImpl);
                    LoadAssetLoaders();
                }

                return assetLoaders;
            }
        }

        /// <summary>
        /// The asset loader to use if no custom asset loader could be found when trying to load a project asset.
        /// </summary>
        private static UnknownAssetLoader FallbackAssetLoader { get; } = new UnknownAssetLoader();

        #endregion

        /// <summary>
        /// Iterate through all the DLLs in the same location as the editor and load all non-abstract classes derived from AssetLoader.
        /// </summary>
        public static void LoadAssetLoaders()
        {
            AssetLoadersImpl.Clear();

            // Go through each DLL
            foreach (Type type in ExtensibilityUtils.Types)
            {
                if (!type.IsAbstract && type.IsSubclassOf(typeof(AssetLoader)))
                {
                    AssetLoader assetLoader = Activator.CreateInstance(type) as AssetLoader;
                    AssetLoadersImpl.Add(assetLoader.AssetFileExtension, assetLoader);
                }
            }
        }

        /// <summary>
        /// Attempt to load the asset at the inputted file path using all of the registered asset loaders.
        /// Will return null if there was a problem performing this loading.
        /// </summary>
        /// <param name="file"></param>
        public static IAsset LoadAsset(string filePath)
        {
            return LoadAsset(new FileInfo(filePath));
        }

        /// <summary>
        /// Attempt to load the asset at the inputted path using all of the registered asset loaders.
        /// Will return null if the file does not exist.
        /// </summary>
        /// <param name="file"></param>
        public static IAsset LoadAsset(FileInfo file)
        {
            if (!file.Exists)
            {
                CelDebug.Fail("Inputted filepath does not exist.");
                return null;
            }
            else if (!AssetLoaders.ContainsKey(file.Extension))
            {
                // No custom loader found, so use the fallback
                return FallbackAssetLoader.Load(file);
            }

            return AssetLoaders[file.Extension].Load(file);
        }
    }
}
