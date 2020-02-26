using BindingsKernel;
using CelesteEngineEditor.Attributes;
using CelesteEngineEditor.Extensibility;
using System;
using System.ComponentModel;
using System.Windows;
using System.Windows.Controls;

namespace CelesteEngineEditor.Editors
{
    /// <summary>
    /// Interaction logic for GameObjectEditor.xaml
    /// </summary>
    [CustomEditor(typeof(GameObject), "Game Object Editor")]
    public partial class GameObjectEditor : Editor
    {
        #region Properties and Fields

        public GameObjectEditorViewModel GameObjectEditorViewModel { get; private set; }

        #endregion

        public GameObjectEditor(GameObject targetGameObject) :
            base(new GameObjectEditorViewModel(targetGameObject))
        {
            InitializeComponent();

            GameObjectEditorViewModel = ViewModel as GameObjectEditorViewModel;

            ContextMenu contextMenu = new ContextMenu();

            foreach (Type type in ComponentExtensibility.Components)
            {
                MenuItem menuItem = new MenuItem();
                menuItem.Header = type.Name;
                menuItem.DataContext = type;
                menuItem.Click += ComponentMenuItem_Click;

                contextMenu.Items.Add(menuItem);
            }

            contextMenu.Items.SortDescriptions.Add(new SortDescription() { PropertyName = "Header" });
            ComponentsList.ContextMenu = contextMenu;
        }

        private void ComponentMenuItem_Click(object sender, RoutedEventArgs e)
        {
            GameObjectEditorViewModel.AddComponent((sender as MenuItem).DataContext as Type);
        }
    }
}
