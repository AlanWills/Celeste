using BindingsKernel;
using BindingsKernel.Objects;
using BindingsKernel.Serialization;
using CelesteEngineEditor.Assets;
using CelesteEngineEditor.Core.AssetLoaders;
using CelesteEngineEditor.Extensibility;
using CelesteEngineEditor.Settings;
using CelesteEngineEditor.Windows;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using static CelesteEngineEditor.Windows.UtilityWindows;

namespace CelesteEngineEditor.Core
{
    public class Project
    {
        #region Events

        /// <summary>
        /// An event called after a project is successfully loaded.
        /// </summary>
        public static event Action OnProjectLoaded;

        #endregion

        #region Properties and Fields
        
        private static Project current;
        /// <summary>
        /// The currently loaded project that we are editing.
        /// </summary>
        public static Project Current
        {
            get { return current ?? (current = new Project()); }
        }

        /// <summary>
        /// The root directory of the project.
        /// </summary>
        public DirectoryInfo ProjectDirectory { get; private set; }

        private List<IAsset> projectAssets = new List<IAsset>();
        /// <summary>
        /// All of the loaded assets contained within our project directory.
        /// </summary>
        public ReadOnlyCollection<IAsset> ProjectAssets { get; private set; }

        #endregion

        private Project()
        {
            ProjectAssets = new ReadOnlyCollection<IAsset>(projectAssets);
        }

        #region Loading

        /// <summary>
        /// Use the inputted project directory to load a new project.
        /// Will raise the OnProjectLoaded event if this was successful.
        /// </summary>
        /// <param name="projectDirectory"></param>
        public static void Load(string projectDirectory)
        {
            if (string.IsNullOrEmpty(projectDirectory) || !Directory.Exists(projectDirectory))
            {
                CelDebug.Fail();
                return;
            }

            Current.ProjectDirectory = new DirectoryInfo(projectDirectory);
            Current.LoadAssets();

            OnProjectLoaded?.Invoke();

            LocalSettings.Instance.LastOpenedProjectLocation = projectDirectory;
            LocalSettings.Instance.Save();
        }

        /// <summary>
        /// Clears all the loaded objects in the current project and iterates through all the
        /// files within the project directory.
        /// </summary>
        private void LoadAssets()
        {
            projectAssets.Clear();

            foreach (FileInfo file in ProjectDirectory.EnumerateFiles("*", SearchOption.AllDirectories))
            {
                IAsset asset = AssetLoaderExtensibility.LoadAsset(file);
                if (asset != null)
                {
                    projectAssets.Add(asset);
                }
            }

            Dictionary<string, IReference> referenceLookup = new Dictionary<string, IReference>();
            foreach (IAsset asset in ProjectAssets)
            {
                referenceLookup.Add(asset.FileInfo.FullName.Remove(0, ProjectDirectory.FullName.Length), asset.AssetObjectInternal);
            }

            // Now resolve all the scriptable object references since they will all be loaded
            foreach (IAsset asset in ProjectAssets)
            {
                if (asset is ScriptableObjectAsset)
                {
                    (asset as ScriptableObjectAsset).ResolveReferences(referenceLookup);
                }
            }
        }

        #endregion

        #region Saving

        /// <summary>
        /// Save all the assets within the currently loaded project to disk.
        /// </summary>
        public void Save()
        {
            Tuple<ProgressResult, bool> result = ProgressWindow(
                "Saving Assets",
                "Serializing and saving all project assets.",
                ProgressMode.Determinate,
                (args, messageUpdate, progressUpdate, isCancelled) =>
                {
                    IEnumerable<IAsset> dirtyAssets = ProjectAssets.Where(x => x.Dirty);

                    int currentAsset = 0;
                    int totalAssetCount = dirtyAssets.Count();

                    foreach (IAsset asset in dirtyAssets)
                    {
                        if (isCancelled())
                        {
                            return false;
                        }

                        messageUpdate("Saving " + asset.FileInfo.Name);
                        progressUpdate((currentAsset * 100) / totalAssetCount);

                        asset.Save();
                        asset.Dirty = false;

                        ++currentAsset;
                    }

                    return true;
                }, null);
        }

        #endregion

        #region Asset Management

        /// <summary>
        /// Adds the inputted asset to the project to be tracked and saved.
        /// </summary>
        /// <param name="asset"></param>
        public void AddAsset(IAsset asset)
        {
            projectAssets.Add(asset);
        }

        /// <summary>
        /// Removes the inputted asset from the project so it is no longer tracked and saved.
        /// </summary>
        /// <param name="asset"></param>
        public void RemoveAsset(IAsset asset)
        {
            projectAssets.Remove(asset);
        }

        /// <summary>
        /// If the inputted object is a project asset we mark it as dirty.
        /// Otherwise, we attempt to find a project asset corresponding to the inputted object and mark that as dirty.
        /// </summary>
        /// <param name="obj"></param>
        public static void SetDirty(object obj)
        {
            if (obj is IAsset)
            {
                (obj as IAsset).Dirty = true;
            }
            else if (obj != null)
            {
                IAsset asset = Current.ProjectAssets.FirstOrDefault(x => x.AssetObjectInternal == obj);
                if (asset != null)
                {
                    asset.Dirty = true;
                }
            }
        }
        
        /// <summary>
        /// Return all of the assets in the project which are derived from the inputted type.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <returns></returns>
        public List<T> FindAssets<T>() where T : class, IReference
        {
            List<T> assets = new List<T>();

            foreach (IAsset asset in ProjectAssets)
            {
                if (asset.AssetObjectInternal is T)
                {
                    assets.Add(asset.AssetObjectInternal as T);
                }
            }

            return assets;
        }

        #endregion
    }
}
