using BindingsKernel;
using CelesteEditor.Assets;
using CelesteEditor.Core;
using CelesteEditor.Extensibility;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace CelesteEditor.Editors
{
    public class ProjectExplorerFileViewModel : ProjectExplorerItemViewModel
    {
        #region Properties and Fields

        /// <summary>
        /// The project asset that this file represents.
        /// </summary>
        public IAsset Asset { get; private set; }

        /// <summary>
        /// The filesystem information for this file.
        /// </summary>
        public FileInfo FileInfo
        {
            get
            {
                CelDebug.AssertNotNull(Asset);
                return Asset?.FileInfo;
            }
        }

        /// <summary>
        /// The full path to the file within the current OS filesystem.
        /// </summary>
        public override string FilePath { get { return FileInfo.FullName; } }

        #endregion

        public ProjectExplorerFileViewModel(ProjectExplorerDirectoryViewModel directory, IAsset asset) :
            base(directory, asset?.FileInfo?.Name)
        {
            Asset = asset;
        }
        
        #region Abstract Overrides

        /// <summary>
        /// When we change the display name, we rename the file too.
        /// </summary>
        protected override void OnDisplayNameChanged()
        {
            CelDebug.AssertNotNull(FileInfo);
            FileInfo.MoveTo(System.IO.Path.Combine(FileInfo.Directory.FullName, DisplayName));
        }

        /// <summary>
        /// When the parent directory changes, we make sure the file info is kept up to date.
        /// </summary>
        /// <param name="newParentInfo"></param>
        public override void OnParentDirectoryChanged(DirectoryInfo newParentInfo)
        {
            //FileInfo = new FileInfo(Path.Combine(newParentInfo.FullName, DisplayName));
            CelDebug.AssertNotNull(FileInfo);
        }

        /// <summary>
        /// When this object is deleted, we attempt to delete the file from disc.
        /// </summary>
        public override void OnDeleted()
        {
            CelDebug.AssertNotNull(FileInfo);
            if (!FileInfo.DeleteFileNoThrow())
            {
                CelDebug.Fail();
            }

            Project.Current.RemoveAsset(Asset);
        }

        #endregion
    }
}
