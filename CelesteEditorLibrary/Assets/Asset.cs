using BindingsKernel.Objects;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEngineEditor.Assets
{
    public abstract class Asset<T> : IAsset where T : IReference
    {
        #region Properties and Fields

        /// <summary>
        /// The file info for this asset.
        /// </summary>
        public FileInfo FileInfo { get; private set; }

        /// <summary>
        /// Obtain the loaded object representation of asset.
        /// </summary>
        public T AssetObject { get; private set; }

        /// <summary>
        /// An internal variable.  Use the AssetObject property instead.
        /// </summary>
        public IReference AssetObjectInternal { get { return AssetObject; } }

        /// <summary>
        /// Returns true if this asset has been edited during the editor running.
        /// </summary>
        public bool Dirty { get; set; }
        
        #endregion

        public Asset(FileInfo fileInfo, T assetObject)
        {
            FileInfo = fileInfo;
            AssetObject = assetObject;
        }

        #region Abstract Functions

        public abstract void Save();

        #endregion
    }
}
