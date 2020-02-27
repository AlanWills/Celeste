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
	public class LimitedLifeTime : Component
	{
		[Serialize, DisplayPriority(1)]
		[XmlAttribute("active"), DisplayName("Active")]
		public bool Active { get; set; } = true;

		[Serialize, DisplayPriority(2)]
		[XmlAttribute("lifetime"), DisplayName("Lifetime")]
		public float Lifetime { get; set; } = 0.000000f;

		[Serialize, DisplayPriority(3)]
		[XmlAttribute("trigger_key"), DisplayName("Trigger Key")]
		public Key TriggerKey { get; set; } = Key.Unknown;

		[Serialize, DisplayPriority(4)]
		public List<Component> OnDeathCallbacks { get; set; } = new List<Component>();
	}
}
