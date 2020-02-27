using BindingsKernel;
using CelesteEditor.Attributes;
using CelesteEditor.Editors;
using CelesteEditor.Extensibility;
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

namespace CelesteEditor.Editors
{
    /// <summary>
    /// Interaction logic for Hierarchy.xaml
    /// </summary>
    [CustomEditor(typeof(Screen), "Hierarchy", DockPosition.Left)]
    [CustomMenuItem("Hierarchy")]
    public partial class Hierarchy : Editor
    {
        #region Properties and Fields

        private HierarchyViewModel HierarchyViewModel { get; set; }

        #endregion

        public Hierarchy() :
            this(null)
        {
        }

        public Hierarchy(object targetObject) :
            base(new HierarchyViewModel(targetObject))
        {
            HierarchyViewModel = ViewModel as HierarchyViewModel;

            InitializeComponent();

            ContextMenu contextMenu = new ContextMenu();

            MenuItem createMenuItem = new MenuItem() { Header = "Create" };
            contextMenu.Items.Add(createMenuItem);

            // Create game object context menu item
            {
                MenuItem gameObjectMenuItem = new MenuItem() { Header = "GameObject" };
                gameObjectMenuItem.Click += GameObjectMenuItem_Click;
                createMenuItem.Items.Add(gameObjectMenuItem);
            }

            ContextMenu = contextMenu;
        }

        #region Context Menu Callbacks

        private void GameObjectMenuItem_Click(object sender, RoutedEventArgs e)
        {
            HierarchyViewModel.CreateNewGameObject(HierarchyViewModel.SelectedItem);
        }

        #endregion

        #region Event Callbacks

        private void Grid_MouseDown(object sender, MouseButtonEventArgs e)
        {
            HierarchyViewModel.SelectedItem = (sender as FrameworkElement).DataContext as HierarchyEntityViewModel;
        }

        #endregion
    }
}