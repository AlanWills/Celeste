using BindingsKernel;
using CelesteEngineEditor.Attributes;
using CelesteEngineEditor.Editors;
using CelesteEngineEditor.Extensibility;
using DevZest.Windows.Docking;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace CelesteEngineEditor.Editors
{
    /// <summary>
    /// Interaction logic for ProjectExplorer.xaml
    /// </summary>
    [CustomEditor("Project Explorer", DockPosition.Left)]
    [CustomMenuItem("Project Explorer")]
    public partial class ProjectExplorer : Editor
    {
        #region Properties and Fields

        private ProjectExplorerViewModel ProjectExplorerViewModel { get; set; }

        #endregion

        public ProjectExplorer() :
            this(null)
        {
        }

        public ProjectExplorer(object targetObject) :
            base(new ProjectExplorerViewModel(targetObject))
        {
            ProjectExplorerViewModel = ViewModel as ProjectExplorerViewModel;
            ProjectExplorerViewModel.HookUpEvents();
            ProjectExplorerViewModel.PropertyChanged += ViewModel_PropertyChanged;

            InitializeComponent();

            ContextMenu contextMenu = new ContextMenu();
            
            MenuItem createMenuItem = new MenuItem() { Header = "Create" };
            contextMenu.Items.Add(createMenuItem);

            // Create folder context menu item
            {
                MenuItem folderMenuItem = new MenuItem() { Header = "Folder" };
                folderMenuItem.Click += FolderMenuItem_Click;
                createMenuItem.Items.Add(folderMenuItem);
            }

            // Create screen context menu item
            {
                MenuItem screenMenuItem = new MenuItem() { Header = "Screen" };
                screenMenuItem.Click += CreateScreenMenuItem_Click;
                createMenuItem.Items.Add(screenMenuItem);
            }

            // Create prefab context menu item
            {
                MenuItem prefabMenuItem = new MenuItem() { Header = "Prefab" };
                prefabMenuItem.Click += CreatePrefabMenuItem_Click;
                createMenuItem.Items.Add(prefabMenuItem);
            }

            MenuItem scriptableObjectMenuItem = new MenuItem() { Header = "Scriptable Objects" };
            createMenuItem.Items.Add(scriptableObjectMenuItem);

            foreach (Type type in ScriptableObjectExtensibility.ScriptableObjects)
            {
                MenuItem scriptableObjectItem = new MenuItem() { Header = type.Name };
                scriptableObjectItem.Click += ScriptableObjectItem_Click;
                scriptableObjectItem.DataContext = type;
                scriptableObjectMenuItem.Items.Add(scriptableObjectItem);
            }

            MenuItem deleteMenuItem = new MenuItem() { Header = "Delete" };
            deleteMenuItem.Click += DeleteMenuItem_Click;
            contextMenu.Items.Add(deleteMenuItem);

            MenuItem setDirtyMenuItem = new MenuItem() { Header = "Set Dirty" };
            setDirtyMenuItem.Click += SetDirtyMenuItem_Click;
            contextMenu.Items.Add(setDirtyMenuItem);

            MenuItem showInExplorerMenuItem = new MenuItem() { Header = "Show In Explorer" };
            showInExplorerMenuItem.Click += ShowInExplorerMenuItem_Click;
            contextMenu.Items.Add(showInExplorerMenuItem);

            ContextMenu = contextMenu;
        }

        private void ViewModel_PropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            if (e.PropertyName == "SelectedItemFocus")
            {
                TreeViewItem item = GetTreeViewItem(ItemInfoTree, ProjectExplorerViewModel.SelectedItem);
                TextBox tb = item.FindFirstChild<TextBox>("etb");
                CelDebug.AssertNotNull(tb);

                tb.Focus();
            }
        }

        #region Tool Bar Button Callbacks

        private void RefreshProjectButton_Click(object sender, RoutedEventArgs e)
        {
            ProjectExplorerViewModel.RefreshProject();
        }

        #endregion

        #region Context Menu Callbacks

        private void FolderMenuItem_Click(object sender, RoutedEventArgs e)
        {
            ProjectExplorerViewModel.CreateFolder();
        }

        private void CreateScreenMenuItem_Click(object sender, RoutedEventArgs e)
        {
            ProjectExplorerViewModel.CreateScreen();
        }

        private void CreatePrefabMenuItem_Click(object sender, RoutedEventArgs e)
        {
            ProjectExplorerViewModel.CreatePrefab();
        }

        private void ScriptableObjectItem_Click(object sender, RoutedEventArgs e)
        {
            Type selectedType = (sender as MenuItem).DataContext as Type;
            ProjectExplorerViewModel.CreateScriptableObject(selectedType);
        }

        private void DeleteMenuItem_Click(object sender, RoutedEventArgs e)
        {
            ProjectExplorerViewModel.SelectedItem.Delete.Execute(null);
        }

        private void SetDirtyMenuItem_Click(object sender, RoutedEventArgs e)
        {
            ProjectExplorerFileViewModel selectedFile = ProjectExplorerViewModel.SelectedItem as ProjectExplorerFileViewModel;
            if (selectedFile != null)
            {
                selectedFile.Asset.Dirty = true;
            }
        }

        private void ShowInExplorerMenuItem_Click(object sender, RoutedEventArgs e)
        {
            ProjectExplorerItemViewModel item = ProjectExplorerViewModel.SelectedItem;
            string filePath = item.Parent.FilePath;

            if (item is ProjectExplorerDirectoryViewModel)
            {
                filePath = (item as ProjectExplorerDirectoryViewModel).DirectoryInfo.FullName;
            }

            Process process = new Process();
            process.StartInfo.UseShellExecute = true;
            process.StartInfo.FileName = @"explorer";
            process.StartInfo.Arguments = filePath;
            process.Start();
        }

        #endregion

        private void ProjectExplorer_ItemLostFocus(object sender, RoutedEventArgs e)
        {
            TextBox text = sender as TextBox;
            BindingOperations.GetBindingExpression(text, TextBox.TextProperty).UpdateSource();
        }

        private void ProjectExplorer_ItemTextBoxIsVisibleChanged(object sender, DependencyPropertyChangedEventArgs e)
        {
            TextBox text = sender as TextBox;
            if (text.IsVisible)
            {
                text.Focus();
            }
        }

        private void Grid_MouseDown(object sender, MouseButtonEventArgs e)
        {
            ProjectExplorerViewModel.SelectedItem = (sender as FrameworkElement).DataContext as ProjectExplorerItemViewModel;
        }

        #region Stack Overflow Function Madness

        /// <summary>
        /// Utility function to find all the children of an inputted object
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="depObj"></param>
        /// <returns></returns>
        public IEnumerable<T> FindVisualChildren<T>(DependencyObject depObj) where T : DependencyObject
        {
            if (depObj != null)
            {
                for (int i = 0; i < VisualTreeHelper.GetChildrenCount(depObj); i++)
                {
                    DependencyObject child = VisualTreeHelper.GetChild(depObj, i);

                    if (child != null && child is T)
                        yield return (T)child;

                    foreach (T childOfChild in FindVisualChildren<T>(child))
                        yield return childOfChild;
                }
            }
        }

        /// <summary>
        /// Recursively search for an item in this subtree.
        /// </summary>
        /// <param name="container">
        /// The parent ItemsControl. This can be a TreeView or a TreeViewItem.
        /// </param>
        /// <param name="item">
        /// The item to search for.
        /// </param>
        /// <returns>
        /// The TreeViewItem that contains the specified item.
        /// </returns>
        private TreeViewItem GetTreeViewItem(ItemsControl container, object item)
        {
            if (container != null)
            {
                if (container.DataContext == item)
                {
                    return container as TreeViewItem;
                }

                // Expand the current container
                if (container is TreeViewItem && !((TreeViewItem)container).IsExpanded)
                {
                    container.SetValue(TreeViewItem.IsExpandedProperty, true);
                }

                // Try to generate the ItemsPresenter and the ItemsPanel.
                // by calling ApplyTemplate.  Note that in the 
                // virtualizing case even if the item is marked 
                // expanded we still need to do this step in order to 
                // regenerate the visuals because they may have been virtualized away.

                container.ApplyTemplate();
                ItemsPresenter itemsPresenter =
                    (ItemsPresenter)container.Template.FindName("ItemsHost", container);
                if (itemsPresenter != null)
                {
                    itemsPresenter.ApplyTemplate();
                }
                else
                {
                    // The Tree template has not named the ItemsPresenter, 
                    // so walk the descendents and find the child.
                    itemsPresenter = FindVisualChild<ItemsPresenter>(container);
                    if (itemsPresenter == null)
                    {
                        container.UpdateLayout();

                        itemsPresenter = FindVisualChild<ItemsPresenter>(container);
                    }
                }

                Panel itemsHostPanel = (Panel)VisualTreeHelper.GetChild(itemsPresenter, 0);


                // Ensure that the generator for this panel has been created.
                UIElementCollection children = itemsHostPanel.Children;

                VirtualizingStackPanel virtualizingPanel = itemsHostPanel as VirtualizingStackPanel;

                for (int i = 0, count = container.Items.Count; i < count; i++)
                {
                    TreeViewItem subContainer;
                    if (virtualizingPanel != null)
                    {
                        // Bring the item into view so 
                        // that the container will be generated.
                        virtualizingPanel.BringIntoView();

                        subContainer =
                            (TreeViewItem)container.ItemContainerGenerator.
                            ContainerFromIndex(i);
                    }
                    else
                    {
                        subContainer =
                            (TreeViewItem)container.ItemContainerGenerator.
                            ContainerFromIndex(i);

                        // Bring the item into view to maintain the 
                        // same behavior as with a virtualizing panel.
                        subContainer.BringIntoView();
                    }

                    if (subContainer != null)
                    {
                        // Search the next level for the object.
                        TreeViewItem resultContainer = GetTreeViewItem(subContainer, item);
                        if (resultContainer != null)
                        {
                            return resultContainer;
                        }
                        else
                        {
                            // The object is not under this TreeViewItem
                            // so collapse it.
                            subContainer.IsExpanded = false;
                        }
                    }
                }
            }

            return null;
        }

        /// <summary>
        /// Search for an element of a certain type in the visual tree.
        /// </summary>
        /// <typeparam name="T">The type of element to find.</typeparam>
        /// <param name="visual">The parent element.</param>
        /// <returns></returns>
        private T FindVisualChild<T>(Visual visual) where T : Visual
        {
            for (int i = 0; i < VisualTreeHelper.GetChildrenCount(visual); i++)
            {
                Visual child = (Visual)VisualTreeHelper.GetChild(visual, i);
                if (child != null)
                {
                    T correctlyTyped = child as T;
                    if (correctlyTyped != null)
                    {
                        return correctlyTyped;
                    }

                    T descendent = FindVisualChild<T>(child);
                    if (descendent != null)
                    {
                        return descendent;
                    }
                }
            }

            return null;
        }

        #endregion
    }
}