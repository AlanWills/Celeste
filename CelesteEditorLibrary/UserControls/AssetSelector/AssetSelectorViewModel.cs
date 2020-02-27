using CelesteEditor.Assets;
using CelesteEditor.Core;
using CelesteEditor.ViewModels;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEditor.UserControls.ProjectAssetSelector
{
    public class AssetSelectorViewModel : Notifier
    {
        #region Properties and Fields

        private Type assetType;
        public Type AssetType
        {
            get { return assetType; }
            set
            {
                assetType = value;
                RebuildItems();
            }
        }

        public ObservableCollection<IAsset> Items { get; private set; } = new ObservableCollection<IAsset>();

        private IAsset selectedItem;
        public IAsset SelectedItem
        {
            get { return selectedItem; }
            set
            {
                selectedItem = value;
                NotifyOnPropertyChanged(nameof(SelectedItem));
            }
        }

        #endregion
        
        #region Utility Functions

        private void RebuildItems()
        {
            Items.Clear();
            
            foreach (IAsset asset in Project.Current.ProjectAssets)
            {
                Type assetType = asset.AssetObjectInternal.GetType();
                if (AssetType.IsAssignableFrom(assetType))
                {
                    Items.Add(asset);
                }
            }
        }

        #endregion
    }
}