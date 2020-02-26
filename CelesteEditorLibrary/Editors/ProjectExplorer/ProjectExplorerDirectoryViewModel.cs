using BindingsKernel;
using CelesteEngineEditor.Assets;
using CelesteEngineEditor.Core;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Path = System.IO.Path;

namespace CelesteEngineEditor.Editors
{
    public class ProjectExplorerDirectoryViewModel : ProjectExplorerItemViewModel
    {
        #region Properties and Fields

        /// <summary>
        /// A list of children contained within this section.
        /// </summary>
        public ObservableCollection<ProjectExplorerItemViewModel> Children { get; private set; } = new ObservableCollection<ProjectExplorerItemViewModel>();

        /// <summary>
        /// The string which points to the resource containing the icon for this resource.
        /// </summary>
        public string IconSource { get { return "pack://application:,,,/CelesteEngineEditor;component/Icons/Folder.ico"; } }

        /// <summary>
        /// The filesystem information for this directory.
        /// </summary>
        public DirectoryInfo DirectoryInfo { get; private set; }

        /// <summary>
        /// The full path to this directory within the current OS filesystem.
        /// </summary>
        public override string FilePath { get { return DirectoryInfo.FullName; } }

        #endregion

        public ProjectExplorerDirectoryViewModel(ProjectExplorerDirectoryViewModel parent, DirectoryInfo directoryInfo) :
            base(parent, directoryInfo.Name)
        {
            DirectoryInfo = directoryInfo;
        }

        #region Utility Functions

        /// <summary>
        /// Creates and adds a child directory to this section's children.
        /// </summary>
        public ProjectExplorerDirectoryViewModel CreateChildDirectory(DirectoryInfo info)
        {
            ProjectExplorerDirectoryViewModel directory = new ProjectExplorerDirectoryViewModel(this, info);
            Children.Add(directory);

            return directory;
        }

        /// <summary>
        /// Creates and adds a child file to this section's children.
        /// </summary>
        public ProjectExplorerFileViewModel CreateChildFile(IAsset asset)
        {
            ProjectExplorerFileViewModel file = new ProjectExplorerFileViewModel(this, asset);
            Children.Add(file);

            return file;
        }

        /// <summary>
        /// Removes the inputted view model from this directory.
        /// </summary>
        /// <param name="viewModel"></param>
        public void DeleteChild(ProjectExplorerItemViewModel viewModel)
        {
            if (!Children.Contains(viewModel))
            {
                CelDebug.Fail();
                return;
            }

            Children.Remove(viewModel);
            viewModel.OnDeleted();
        }

        /// <summary>
        /// Recursively iterate through all of the children and attempt to add any directories to the inputted dictionary.
        /// </summary>
        /// <param name="viewModel"></param>
        /// <param name="registry"></param>
        public void AddChildDirectoriesTo(Dictionary<DirectoryInfo, ProjectExplorerDirectoryViewModel> registry)
        {
            foreach (ProjectExplorerItemViewModel itemViewModel in Children)
            {
                if (itemViewModel is ProjectExplorerDirectoryViewModel &&
                    !registry.ContainsKey((itemViewModel as ProjectExplorerDirectoryViewModel).DirectoryInfo))
                {
                    ProjectExplorerDirectoryViewModel directoryViewModel = itemViewModel as ProjectExplorerDirectoryViewModel;
                    registry.Add(directoryViewModel.DirectoryInfo, directoryViewModel);
                    directoryViewModel.AddChildDirectoriesTo(registry);
                }
            }
        }

        #endregion

        #region Abstract Overrides

        /// <summary>
        /// When the display name is changed, we change the name of the directory to the new value.
        /// </summary>
        protected override void OnDisplayNameChanged()
        {
            CelDebug.AssertNotNull(DirectoryInfo);
            DirectoryInfo.MoveTo(Path.Combine(DirectoryInfo.Parent.FullName, DisplayName));

            foreach (ProjectExplorerItemViewModel child in Children)
            {
                child.OnParentDirectoryChanged(DirectoryInfo);
            }
        }

        /// <summary>
        /// Updates the directory info for this directory to be under the inputted parent directory.
        /// Will then iterate through all children and perform the same procedure to update their info.
        /// </summary>
        /// <param name="newParentInfo"></param>
        public override void OnParentDirectoryChanged(DirectoryInfo newParentInfo)
        {
            DirectoryInfo = new DirectoryInfo(Path.Combine(newParentInfo.FullName, DisplayName));
            CelDebug.AssertNotNull(DirectoryInfo);

            foreach (ProjectExplorerItemViewModel child in Children)
            {
                child.OnParentDirectoryChanged(DirectoryInfo);
            }
        }

        /// <summary>
        /// When deleted, we remove the directory from on disc and all child directories too.
        /// </summary>
        public override void OnDeleted()
        {
            CelDebug.AssertNotNull(DirectoryInfo);
            DirectoryInfo.Delete(true);
            DirectoryInfo.Refresh();
            CelDebug.Assert(!DirectoryInfo.Exists);
        }

        #endregion
    }
}
