using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Threading.Tasks;
using System.Xml.Serialization;
using BindingsKernel;

namespace Celeste.Settings
{
	public class WindowSettings : ScriptableObject
	{
		[Serialize, DisplayPriority(1)]
		[XmlAttribute("window_title"), DisplayName("Window Title")]
		public string WindowTitle { get; set; } = "";

		[Serialize, DisplayPriority(2)]
		[XmlAttribute("window_icon"), DisplayName("Window Icon")]
		public string WindowIcon { get; set; } = "";

		[Serialize, DisplayPriority(3)]
		[XmlAttribute("resolution"), DisplayName("Resolution")]
		public Vector2 Resolution { get; set; } = new Vector2(0.000000f, 0.000000f);

		[Serialize, DisplayPriority(4)]
		[XmlAttribute("windowed"), DisplayName("Windowed")]
		public bool Windowed { get; set; } = false;
	}
}
