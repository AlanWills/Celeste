using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Threading.Tasks;
using System.Xml.Serialization;
using BindingsKernel;

namespace Celeste.Rendering
{
	public class TextRenderer : Component
	{
		[Serialize, DisplayPriority(1)]
		[XmlAttribute("active"), DisplayName("Active")]
		public bool Active { get; set; } = true;

		[Serialize, DisplayPriority(2)]
		[XmlAttribute("font"), DisplayName("Font")]
		public Path Font { get; set; } = new Path(@"Fonts\Arial.ttf");

		[Serialize, DisplayPriority(3)]
		[XmlAttribute("font_height"), DisplayName("Font Height")]
		public float FontHeight { get; set; } = 12.000000f;

		[Serialize, DisplayPriority(4)]
		[XmlAttribute("horizontal_alignment"), DisplayName("Horizontal Alignment")]
		public HorizontalAlignment HorizontalAlignment { get; set; } = HorizontalAlignment.Centre;

		[Serialize, DisplayPriority(5)]
		[XmlAttribute("vertical_alignment"), DisplayName("Vertical Alignment")]
		public VerticalAlignment VerticalAlignment { get; set; } = VerticalAlignment.Centre;

		[Serialize, DisplayPriority(6)]
		[XmlAttribute("colour"), DisplayName("Colour")]
		public Vector3 Colour { get; set; } = new Vector3(1.000000f, 1.000000f, 1.000000f);

		[Serialize, DisplayPriority(7)]
		[XmlAttribute("opacity"), DisplayName("Opacity")]
		public float Opacity { get; set; } = 1.000000f;

		[Serialize, DisplayPriority(8)]
		[XmlChildElementName("Line")]
		public List<string> Lines { get; set; } = new List<string>();
	}
}
