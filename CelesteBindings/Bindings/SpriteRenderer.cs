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
	public class SpriteRenderer : Component
	{
		[Serialize, DisplayPriority(1)]
		[XmlAttribute("active"), DisplayName("Active")]
		public bool Active { get; set; } = true;

		[Serialize, DisplayPriority(2)]
		[XmlAttribute("sprite"), DisplayName("Sprite")]
		public Path Sprite { get; set; } = new Path(@"");

		[Serialize, DisplayPriority(3)]
		[XmlAttribute("size"), DisplayName("Size")]
		public Vector2 Size { get; set; } = new Vector2(0.000000f, 0.000000f);

		[Serialize, DisplayPriority(4)]
		[XmlAttribute("colour"), DisplayName("Colour")]
		public Vector3 Colour { get; set; } = new Vector3(1.000000f, 1.000000f, 1.000000f);

		[Serialize, DisplayPriority(5)]
		[XmlAttribute("opacity"), DisplayName("Opacity")]
		public float Opacity { get; set; } = 1.000000f;

		[Serialize, DisplayPriority(6)]
		[XmlAttribute("preserve_aspect_ratio"), DisplayName("Preserve Aspect Ratio")]
		public bool PreserveAspectRatio { get; set; } = false;

		[Serialize, DisplayPriority(7)]
		[XmlAttribute("scissor_rectangle_dimensions"), DisplayName("Scissor Rectangle Dimensions")]
		public Vector2 ScissorRectangleDimensions { get; set; } = new Vector2(0.000000f, 0.000000f);

		[Serialize, DisplayPriority(8)]
		[XmlAttribute("scissor_rectangle_centre"), DisplayName("Scissor Rectangle Centre")]
		public Vector2 ScissorRectangleCentre { get; set; } = new Vector2(0.000000f, 0.000000f);
	}
}
