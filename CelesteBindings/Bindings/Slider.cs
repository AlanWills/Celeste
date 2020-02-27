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
	public class Slider : Component
	{
		[Serialize, DisplayPriority(1)]
		[XmlAttribute("active"), DisplayName("Active")]
		public bool Active { get; set; } = true;

		[Serialize, DisplayPriority(2)]
		[XmlAttribute("min"), DisplayName("Min")]
		public float Min { get; set; } = 0.000000f;

		[Serialize, DisplayPriority(3)]
		[XmlAttribute("max"), DisplayName("Max")]
		public float Max { get; set; } = 1.000000f;

		[Serialize, DisplayPriority(4)]
		[XmlAttribute("value"), DisplayName("Value")]
		public float Value { get; set; } = 0.000000f;

		[Serialize, DisplayPriority(5)]
		public List<Component> ValueChangedCallbacks { get; set; } = new List<Component>();
	}
}
