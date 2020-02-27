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
	public class ProgressBar : Component
	{
		[Serialize, DisplayPriority(1)]
		[XmlAttribute("active"), DisplayName("Active")]
		public bool Active { get; set; } = true;
	}
}
