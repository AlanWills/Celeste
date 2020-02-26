using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Threading.Tasks;
using System.Xml.Serialization;
using BindingsKernel;

namespace CelesteEngine.Settings
{
	public class GameSettings : ScriptableObject
	{
		[Serialize, DisplayPriority(1)]
		[XmlAttribute("master_volume"), DisplayName("Master Volume")]
		public float MasterVolume { get; set; } = 1.000000f;

		[Serialize, DisplayPriority(2)]
		[XmlAttribute("music_volume"), DisplayName("Music Volume")]
		public float MusicVolume { get; set; } = 1.000000f;

		[Serialize, DisplayPriority(3)]
		[XmlAttribute("sfx_volume"), DisplayName("Sfx Volume")]
		public float SfxVolume { get; set; } = 1.000000f;
	}
}
