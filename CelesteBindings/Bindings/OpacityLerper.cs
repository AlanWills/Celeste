using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Threading.Tasks;
using System.Xml.Serialization;
using BindingsKernel;

namespace Celeste
{
	public class OpacityLerper : Component
	{
		[Serialize, DisplayPriority(1)]
		[XmlAttribute("active"), DisplayName("Active")]
		public bool Active { get; set; } = true;

		[Serialize, DisplayPriority(2)]
		[XmlAttribute("max"), DisplayName("Max")]
		public float Max { get; set; } = 1.000000f;

		[Serialize, DisplayPriority(3)]
		[XmlAttribute("min"), DisplayName("Min")]
		public float Min { get; set; } = 0.000000f;

		[Serialize, DisplayPriority(4)]
		[XmlAttribute("lerp_up_time"), DisplayName("Lerp Up Time")]
		public float LerpUpTime { get; set; } = 1.000000f;

		[Serialize, DisplayPriority(5)]
		[XmlAttribute("lerp_down_time"), DisplayName("Lerp Down Time")]
		public float LerpDownTime { get; set; } = 1.000000f;

		[Serialize, DisplayPriority(6)]
		[XmlAttribute("max_wait_time"), DisplayName("Max Wait Time")]
		public float MaxWaitTime { get; set; } = 0.000000f;

		[Serialize, DisplayPriority(7)]
		[XmlAttribute("min_wait_time"), DisplayName("Min Wait Time")]
		public float MinWaitTime { get; set; } = 0.000000f;

		[Serialize, DisplayPriority(8)]
		[XmlAttribute("lerping_up"), DisplayName("Lerping Up")]
		public bool LerpingUp { get; set; } = true;
	}
}
