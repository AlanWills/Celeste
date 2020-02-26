using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Threading.Tasks;
using System.Xml.Serialization;
using BindingsKernel;

namespace CelesteEngine.UI
{
	public class Button : Component
	{
		[Serialize, DisplayPriority(1)]
		[XmlAttribute("active"), DisplayName("Active")]
		public bool Active { get; set; } = true;

		[Serialize, DisplayPriority(2)]
		[XmlAttribute("default_texture"), DisplayName("Default Texture")]
		public Path DefaultTexture { get; set; } = new Path(@"Textures\UI\ButtonDefault.png");

		[Serialize, DisplayPriority(3)]
		[XmlAttribute("highlighted_texture"), DisplayName("Highlighted Texture")]
		public Path HighlightedTexture { get; set; } = new Path(@"Textures\UI\ButtonHighlighted.png");

		[Serialize, DisplayPriority(4)]
		[XmlAttribute("clicked_texture"), DisplayName("Clicked Texture")]
		public Path ClickedTexture { get; set; } = new Path(@"Textures\UI\ButtonClicked.png");

		[Serialize, DisplayPriority(5)]
		[XmlAttribute("highlighted_sound"), DisplayName("Highlighted Sound")]
		public Path HighlightedSound { get; set; } = new Path(@"Audio\SFX\ButtonHover.wav");

		[Serialize, DisplayPriority(6)]
		[XmlAttribute("clicked_sound"), DisplayName("Clicked Sound")]
		public Path ClickedSound { get; set; } = new Path(@"Audio\SFX\ButtonClicked.wav");

		[Serialize, DisplayPriority(7)]
		public List<Component> LeftClickCallbacks { get; set; } = new List<Component>();
	}
}
