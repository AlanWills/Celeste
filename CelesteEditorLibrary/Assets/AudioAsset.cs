using BindingsKernel;
using CelesteEditor.Core;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEditor.Assets
{
    public class AudioAsset : Asset<Audio>
    {
        public AudioAsset(FileInfo fileInfo, Audio audio) : 
            base(fileInfo, audio)
        {
            audio.UniqueIdentifier = fileInfo.FullName.Substring(Project.Current.ProjectDirectory.FullName.Length + 1);
        }

        public override void Save()
        {
            
        }
    }
}
