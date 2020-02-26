using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Threading.Tasks;
using System.Xml.Serialization;
using BindingsKernel;

namespace CelesteEngine.Physics
{
	public class RectangleCollider : Component
	{
		[Serialize, DisplayPriority(1)]
		[XmlAttribute("active"), DisplayName("Active")]
		public bool Active { get; set; } = true;

		[Serialize, DisplayPriority(2)]
		[XmlAttribute("trigger"), DisplayName("Trigger")]
		public bool Trigger { get; set; } = false;

		[Serialize, DisplayPriority(3)]
		[XmlAttribute("dimensions"), DisplayName("Dimensions")]
		public Vector2 Dimensions { get; set; } = new Vector2(0.000000f, 0.000000f);

		[Serialize, DisplayPriority(4)]
		[XmlAttribute("offset"), DisplayName("Offset")]
		public Vector2 Offset { get; set; } = new Vector2(0.000000f, 0.000000f);
	}
}
