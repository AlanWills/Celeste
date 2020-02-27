using BindingsKernel.Objects;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEditor.Assets
{
    public interface IAsset
    {
        #region Properties and Fields

        /// <summary>
        /// The file info for this asset.
        /// </summary>
        FileInfo FileInfo { get; }

        /// <summary>
        /// Obtain the loaded object representation of asset.
        /// </summary>
        IReference AssetObjectInternal { get; }

        /// <summary>
        /// Returns true if this asset has been modified during the duration of the editor running.
        /// </summary>
        bool Dirty { get; set; }
        
        #endregion
        
        #region Save Functions

        /// <summary>
        /// Save this project asset.
        /// </summary>
        void Save();

        #endregion
    }
}
