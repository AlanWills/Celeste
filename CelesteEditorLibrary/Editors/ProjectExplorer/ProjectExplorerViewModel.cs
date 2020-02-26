using BindingsKernel;
using BindingsKernel.Objects;
using CelesteEngineEditor.Assets;
using CelesteEngineEditor.Comparer;
using CelesteEngineEditor.Core;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;

namespace CelesteEngineEditor.Editors
{
    public class ProjectExplorerViewModel : EditorViewModel
    {
        #region Properties and Fields

        /// <summary>
        /// A list of all of the root items contained within the project directory.
        /// </summary>
        public ObservableCollection<ProjectExplorerItemViewModel> Items
        {
            get { return ProjectDirectory != null ? ProjectDirectory.Children : new ObservableCollection<ProjectExplorerItemViewModel>(); }
        }
        
        private ProjectExplorerItemViewModel selectedItem;
        /// <summary>
        /// A reference to the current selected item within the project explorer.
        /// </summary>
        public ProjectExplorerItemViewModel SelectedItem
        {
            get { return selectedItem; }
            set
            {
                if (selectedItem != value)
                {
                    selectedItem.IsSelected = false;
                    selectedItem = value;
                    selectedItem.IsSelected = true;

                    if (selectedItem is ProjectExplorerFileViewModel)
                    {
                        Editor.OpenEditorForObject((selectedItem as ProjectExplorerFileViewModel).Asset.AssetObjectInternal);
                    }
                    else
                    {
                        Editor.OpenEditorForObject(null);
                    }

                    NotifyOnPropertyChanged(nameof(SelectedItem));
                }
            }
        }

        /// <summary>
        /// The root directory for the project.  This is not displayed in the tree view, but is required for hierarchy purposes.
        /// </summary>
        private ProjectExplorerDirectoryViewModel ProjectDirectory { get; set; }

        #endregion

        public ProjectExplorerViewModel(object targetObject) :
            base(targetObject)
        {
            if (Project.Current.ProjectDirectory != null)
            {
                // We had a previously opened project so we open that immediately
                Project_OnProjectLoaded();
            }
        }

        #region Event Management

        public void HookUpEvents()
        {
            Project.OnProjectLoaded += Project_OnProjectLoaded;
        }

        public void UnhookEvents()
        {
            Project.OnProjectLoaded -= Project_OnProjectLoaded;
        }

        #endregion

        #region Event Callbacks

        private void Project_OnProjectLoaded()
        {
            ProjectDirectory = new ProjectExplorerDirectoryViewModel(null, Project.Current.ProjectDirectory);
            selectedItem = ProjectDirectory;

            // Add all the directory view models
            foreach (DirectoryInfo directory in Project.Current.ProjectDirectory.EnumerateDirectories())
            {
                ProjectExplorerDirectoryViewModel directoryVM = ProjectDirectory.CreateChildDirectory(directory);
                AddDirectoryViewModels(directory, directoryVM);
            }

            // Create a lookup to allow us to obtain the directory view model from a file system directory path.
            Dictionary<DirectoryInfo, ProjectExplorerDirectoryViewModel> directoryLookup = new Dictionary<DirectoryInfo, ProjectExplorerDirectoryViewModel>(new DirectoryInfoEqualityComparer());
            directoryLookup.Add(ProjectDirectory.DirectoryInfo, ProjectDirectory);
            ProjectDirectory.AddChildDirectoriesTo(directoryLookup);

            // Now, iterate through all the assets in the project and create file view models appropriately for them
            foreach (IAsset asset in Project.Current.ProjectAssets)
            {
                CelDebug.Assert(directoryLookup.ContainsKey(asset.FileInfo.Directory));
                directoryLookup[asset.FileInfo.Directory].CreateChildFile(asset);
            }

            NotifyOnPropertyChanged(nameof(Items));
        }

        #endregion

        #region Project Management Functions

        public void RefreshProject()
        {
            Project.Load(Project.Current.ProjectDirectory.FullName);
        }

        public void CreateFolder()
        {
            ProjectExplorerDirectoryViewModel parentDirectory = GetDirectoryForSelectedItem();
            if (parentDirectory != null)
            {
                string path = System.IO.Path.Combine(parentDirectory.DirectoryInfo.FullName, "New Folder");
                path = FileSystemUtils.CreateUniqueDirectoryName(path);

                DirectoryInfo info = new DirectoryInfo(path);
                info.Create();

                parentDirectory.IsExpanded = true;
                ProjectExplorerDirectoryViewModel directoryVM = parentDirectory.CreateChildDirectory(info);
                directoryVM.IsSelected = true;
                directoryVM.IsEditingName = true;
                SelectedItem = directoryVM;

                NotifyOnPropertyChanged(nameof(Items));
                NotifyOnPropertyChanged("SelectedItemFocus");
            }
        }

        public void CreateScreen()
        {
            CreateAssetInProject<Screen, ScreenAsset>(".screen");
        }

        public void CreatePrefab()
        {
            CreateAssetInProject<Prefab, PrefabAsset>(".prefab");
        }

        public void CreateScriptableObject(Type type)
        {
            CreateAssetInProject<ScriptableObject, ScriptableObjectAsset>(type, ".asset");
        }

        private Tuple<TAsset, TProjectAsset> CreateAssetInProject<TAsset, TProjectAsset>(Type type, string extension) where TAsset : class, IReference 
                                                                                                                      where TProjectAsset : class, IAsset
        {
            TAsset asset = null;
            TProjectAsset projectAsset = default(TProjectAsset);

            ProjectExplorerDirectoryViewModel parentDirectory = GetDirectoryForSelectedItem();
            if (parentDirectory != null)
            {
                string path = System.IO.Path.Combine(parentDirectory.DirectoryInfo.FullName, "New " + type.Name + extension);
                path = FileSystemUtils.CreateUniqueFileName(path);

                FileInfo info = new FileInfo(path);
                using (info.Create()) { };

                asset = Activator.CreateInstance(type) as TAsset;
                projectAsset = Activator.CreateInstance(typeof(TProjectAsset), new object[] { info, asset }) as TProjectAsset;
                projectAsset.Save();
                Project.Current.AddAsset(projectAsset);

                parentDirectory.IsExpanded = true;
                ProjectExplorerFileViewModel fileVM = parentDirectory.CreateChildFile(projectAsset);
                fileVM.IsSelected = true;
                fileVM.IsEditingName = true;
                SelectedItem = fileVM;

                NotifyOnPropertyChanged("SelectedItemFocus");
            }

            return new Tuple<TAsset, TProjectAsset>(asset, projectAsset);
        }

        private Tuple<TAsset, TProjectAsset> CreateAssetInProject<TAsset, TProjectAsset>(string extension) where TAsset : class, IReference
                                                                                                           where TProjectAsset : class, IAsset
        {
            return CreateAssetInProject<TAsset, TProjectAsset>(typeof(TAsset), extension);
        }

        #endregion

        #region Utility Functions

        private void AddDirectoryViewModels(DirectoryInfo info, ProjectExplorerDirectoryViewModel parentDirectory)
        {
            foreach (DirectoryInfo directory in info.EnumerateDirectories())
            {
                AddDirectoryViewModel(directory, parentDirectory);
            }
        }

        private void AddDirectoryViewModel(DirectoryInfo directoryInfo, ProjectExplorerDirectoryViewModel parentDirectory)
        {
            ProjectExplorerDirectoryViewModel directoryVM = parentDirectory.CreateChildDirectory(directoryInfo);
            AddDirectoryViewModels(directoryInfo, directoryVM);
        }
        
        private ProjectExplorerDirectoryViewModel GetDirectoryForSelectedItem()
        {
            CelDebug.AssertNotNull(SelectedItem);

            ProjectExplorerDirectoryViewModel parentDirectory = SelectedItem as ProjectExplorerDirectoryViewModel;
            if (parentDirectory == null)
            {
                parentDirectory = (SelectedItem as ProjectExplorerFileViewModel).Parent;
            }

            CelDebug.AssertNotNull(parentDirectory);
            return parentDirectory;
        }

        #endregion
    }
}
