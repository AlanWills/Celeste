using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Threading.Tasks;
using System.Xml.Serialization;
using BindingsKernel;

namespace Celeste.Physics
{
	public class RigidBody2D : Component
	{
		[Serialize, DisplayPriority(1)]
		[XmlAttribute("active"), DisplayName("Active")]
		public bool Active { get; set; } = true;

		[Serialize, DisplayPriority(2)]
		[XmlAttribute("linear_velocity"), DisplayName("Linear Velocity")]
		public Vector2 LinearVelocity { get; set; } = new Vector2(0.000000f, 0.000000f);

		[Serialize, DisplayPriority(3)]
		[XmlAttribute("min_linear_velocity"), DisplayName("Min Linear Velocity")]
		public Vector2 MinLinearVelocity { get; set; } = new Vector2(-340282346638528859811704183484516925440.000000f, -340282346638528859811704183484516925440.000000f);

		[Serialize, DisplayPriority(4)]
		[XmlAttribute("max_linear_velocity"), DisplayName("Max Linear Velocity")]
		public Vector2 MaxLinearVelocity { get; set; } = new Vector2(340282346638528859811704183484516925440.000000f, 340282346638528859811704183484516925440.000000f);

		[Serialize, DisplayPriority(5)]
		[XmlAttribute("angular_velocity"), DisplayName("Angular Velocity")]
		public float AngularVelocity { get; set; } = 0.000000f;

		[Serialize, DisplayPriority(6)]
		[XmlAttribute("min_angular_velocity"), DisplayName("Min Angular Velocity")]
		public float MinAngularVelocity { get; set; } = -340282346638528859811704183484516925440.000000f;

		[Serialize, DisplayPriority(7)]
		[XmlAttribute("max_angular_velocity"), DisplayName("Max Angular Velocity")]
		public float MaxAngularVelocity { get; set; } = 340282346638528859811704183484516925440.000000f;
	}
}
