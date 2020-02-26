using BindingsKernel;
using CelesteEngineEditor.Core;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEngineEditor.Assets
{
    public class FontAsset : Asset<Font>
    {
        public FontAsset(FileInfo fileInfo, Font font) : 
            base(fileInfo, font)
        {
            font.UniqueIdentifier = fileInfo.FullName.Substring(Project.Current.ProjectDirectory.FullName.Length + 1);
        }

        public override void Save()
        {
            
        }
    }
}
