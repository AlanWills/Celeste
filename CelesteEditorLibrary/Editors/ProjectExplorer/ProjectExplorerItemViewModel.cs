using CelesteEngineEditor.ViewModels;
using JulMar.Windows.Actions;
using JulMar.Windows.Interactivity;
using JulMar.Windows.Mvvm;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace CelesteEngineEditor.Editors
{
    public abstract class ProjectExplorerItemViewModel : Notifier
    {
        #region Properties and Fields

        private bool isExpanded = false;
        /// <summary>
        /// A flag to indicate whether this item is expanded.
        /// </summary>
        public bool IsExpanded
        {
            get { return isExpanded; }
            set
            {
                isExpanded = value;
                NotifyOnPropertyChanged(nameof(IsExpanded));
            }
        }

        private bool isSelected = false;
        /// <summary>
        /// A flag to indicate whether this item is selected.
        /// </summary>
        public bool IsSelected
        {
            get { return isSelected; }
            set
            {
                isSelected = value;
                NotifyOnPropertyChanged(nameof(IsSelected));
            }
        }

        private bool isEditingName = false;
        /// <summary>
        /// True/False whether we are changing the name of this item.
        /// </summary>
        public bool IsEditingName
        {
            get { return isEditingName; }
            set
            {
                isEditingName = value;
                NotifyOnPropertyChanged(nameof(IsEditingName));
            }
        }

        /// <summary>
        /// Command used to switch to editing mode
        /// </summary>
        public ICommand SwitchToEditingMode { get; private set; }

        /// <summary>
        /// Command used to delete this item
        /// </summary>
        public ICommand Delete { get; private set; }

        private string displayName = "";
        /// <summary>
        /// A string that will be displayed in the UI to the user.
        /// </summary>
        public string DisplayName
        {
            get { return displayName; }
            set
            {
                IsEditingName = false;

                if (displayName != value)
                {
                    displayName = value;

                    OnDisplayNameChanged();
                    NotifyOnPropertyChanged(nameof(DisplayName));
                }
            }
        }

        /// <summary>
        /// The parent directory this item is contained within.
        /// </summary>
        public ProjectExplorerDirectoryViewModel Parent { get; private set; }

        /// <summary>
        /// The full path to this project item within the current OS filesystem.
        /// </summary>
        public abstract string FilePath { get; }

        #endregion

        public ProjectExplorerItemViewModel(ProjectExplorerDirectoryViewModel parent, string displayName)
        {
            Parent = parent;

            // Set the field so that we don't trigger property bindings
            this.displayName = displayName;

            // Command that switches us into editing mode.
            SwitchToEditingMode = new DelegateCommand(() => IsEditingName = !IsEditingName);

            // Command that deletes this item.
            Delete = new DelegateCommand(() => Parent.DeleteChild(this));
        }

        #region Abstract Functions

        /// <summary>
        /// A function called only when the DisplayName has been actively changed to a new value.
        /// </summary>
        protected abstract void OnDisplayNameChanged();

        /// <summary>
        /// Called when the parent directory is changed, allowing the object to refresh it's file system information.
        /// </summary>
        public abstract void OnParentDirectoryChanged(DirectoryInfo newParentInfo);

        /// <summary>
        /// Called when this item is removed from it's parent directory view model.
        /// Allows an opportunity to perform custom behaviour, e.g. removing items from the filesystem.
        /// </summary>
        public abstract void OnDeleted();

        #endregion
    }
}
