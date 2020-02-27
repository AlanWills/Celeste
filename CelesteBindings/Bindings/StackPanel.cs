using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Threading.Tasks;
using System.Xml.Serialization;
using BindingsKernel;

namespace Celeste.UI
{
	public class StackPanel : Component
	{
		[Serialize, DisplayPriority(1)]
		[XmlAttribute("active"), DisplayName("Active")]
		public bool Active { get; set; } = true;

		[Serialize, DisplayPriority(2)]
		[XmlAttribute("orientation"), DisplayName("Orientation")]
		public Orientation Orientation { get; set; } = Orientation.Vertical;

		[Serialize, DisplayPriority(3)]
		[XmlAttribute("horizontal_alignment"), DisplayName("Horizontal Alignment")]
		public HorizontalAlignment HorizontalAlignment { get; set; } = HorizontalAlignment.Centre;

		[Serialize, DisplayPriority(4)]
		[XmlAttribute("vertical_alignment"), DisplayName("Vertical Alignment")]
		public VerticalAlignment VerticalAlignment { get; set; } = VerticalAlignment.Centre;

		[Serialize, DisplayPriority(5)]
		[XmlAttribute("padding"), DisplayName("Padding")]
		public float Padding { get; set; } = 0.000000f;
	}
}
