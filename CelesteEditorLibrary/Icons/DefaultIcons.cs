using CelesteEditor.Attributes;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEditor.Icons
{
    [FileIcon(".png", "Icons/Image.ico")]
    public class PngIcon { }

    [FileIcon(".jpg", "Icons/Image.ico")]
    public class JpgIcon { }

    [FileIcon(".mp3", "Icons/Audio.ico")]
    public class Mp3Icon { }

    [FileIcon(".wav", "Icons/Audio.ico")]
    public class WavIcon { }
}