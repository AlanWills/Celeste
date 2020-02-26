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
    public class Texture2DAsset : Asset<Texture2D>
    {
        public Texture2DAsset(FileInfo fileInfo, Texture2D texture2D) : 
            base(fileInfo, texture2D)
        {
            texture2D.UniqueIdentifier = fileInfo.FullName.Substring(Project.Current.ProjectDirectory.FullName.Length + 1);
        }

        public override void Save()
        {
        }
    }
}
