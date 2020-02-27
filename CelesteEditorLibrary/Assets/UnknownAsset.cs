using CelesteEditor.Objects;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEditor.Assets
{
    public class UnknownAsset : Asset<Unknown>
    { 
        public UnknownAsset(FileInfo fileInfo, object assetObject) : 
            base(fileInfo, new Unknown(assetObject))
        {
        }

        public override void Save()
        {
            // No-op
        }
    }
}
