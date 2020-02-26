using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Threading.Tasks;
using System.Xml.Serialization;
using BindingsKernel;

namespace CelesteEngine.Audio
{
	public class AudioSource : Component
	{
		[Serialize, DisplayPriority(1)]
		[XmlAttribute("active"), DisplayName("Active")]
		public bool Active { get; set; } = true;

		[Serialize, DisplayPriority(2)]
		[XmlAttribute("sound"), DisplayName("Sound")]
		public Path Sound { get; set; } = new Path(@"");

		[Serialize, DisplayPriority(3)]
		[XmlAttribute("is_playing"), DisplayName("Is Playing")]
		public bool IsPlaying { get; set; } = false;

		[Serialize, DisplayPriority(4)]
		[XmlAttribute("is_looping"), DisplayName("Is Looping")]
		public bool IsLooping { get; set; } = false;

		[Serialize, DisplayPriority(5)]
		[XmlAttribute("volume"), DisplayName("Volume")]
		public float Volume { get; set; } = 1.000000f;

		[Serialize, DisplayPriority(6)]
		[XmlAttribute("audio_type"), DisplayName("Audio Type")]
		public AudioType AudioType { get; set; } = AudioType.Music;
	}
}
