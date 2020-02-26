using CelesteEngineEditor.Core;
using CelesteEngineEditor.UserControls.ProjectAssetSelector;
using System;
using System.Collections.Generic;
using System.ComponentModel;
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

namespace CelesteEngineEditor.UserControls
{
    /// <summary>
    /// Interaction logic for AssetSelector.xaml
    /// </summary>
    public partial class AssetSelector : UserControl
    {
        #region Dependency Properties

        #region Project Asset Type

        public Type AssetType
        {
            get { return (Type)GetValue(AssetTypeProperty); }
            set { SetValue(AssetTypeProperty, value); }
        }

        public static readonly DependencyProperty AssetTypeProperty =
            DependencyProperty.Register(
            "AssetType",
            typeof(Type),
            typeof(AssetSelector),
            new FrameworkPropertyMetadata(new PropertyChangedCallback(AssetTypeChanged))
            {
                BindsTwoWayByDefault = true,
                DefaultUpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
            });

        private static void AssetTypeChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            ((AssetSelector)d).AssetSelectorViewModel.AssetType = e.NewValue as Type;
        }

        #endregion

        #region Selected Asset

        public object SelectedAsset
        {
            get { return GetValue(SelectedAssetProperty); }
            set { SetValue(SelectedAssetProperty, value); }
        }

        public static readonly DependencyProperty SelectedAssetProperty =
            DependencyProperty.Register(
            "SelectedAsset",
            typeof(object),
            typeof(AssetSelector),
            new FrameworkPropertyMetadata(SelectedAssetChanged)
            {
                BindsTwoWayByDefault = true,
                DefaultUpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
            });

        private static void SelectedAssetChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            ((AssetSelector)d).AssetSelectorViewModel.SelectedItem = Project.Current.ProjectAssets.FirstOrDefault(x => x.AssetObjectInternal == e.NewValue);
        }

        #endregion

        public AssetSelectorViewModel AssetSelectorViewModel { get; private set; } = new AssetSelectorViewModel();

        #endregion

        public AssetSelector()
        {
            InitializeComponent();

            AssetSelectorViewModel.PropertyChanged += AssetSelectorViewModel_PropertyChanged;
        }

        private void AssetSelectorViewModel_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            if (AssetSelectorViewModel.SelectedItem != null && e.PropertyName == nameof(AssetSelectorViewModel.SelectedItem))
            {
                SetValue(SelectedAssetProperty, AssetSelectorViewModel.SelectedItem.AssetObjectInternal);
                GetBindingExpression(SelectedAssetProperty).UpdateSource();
            }
        }
    }
}
