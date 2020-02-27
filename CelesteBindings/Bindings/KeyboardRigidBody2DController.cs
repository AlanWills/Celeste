using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Threading.Tasks;
using System.Xml.Serialization;
using BindingsKernel;

namespace Celeste.Input
{
	public class KeyboardRigidBody2DController : Component
	{
		[Serialize, DisplayPriority(1)]
		[XmlAttribute("active"), DisplayName("Active")]
		public bool Active { get; set; } = true;

		[Serialize, DisplayPriority(2)]
		[XmlAttribute("decrease_x_linear_velocity_key"), DisplayName("Decrease X Linear Velocity Key")]
		public Key DecreaseXLinearVelocityKey { get; set; } = Key.Unknown;

		[Serialize, DisplayPriority(3)]
		[XmlAttribute("increase_x_linear_velocity_key"), DisplayName("Increase X Linear Velocity Key")]
		public Key IncreaseXLinearVelocityKey { get; set; } = Key.Unknown;

		[Serialize, DisplayPriority(4)]
		[XmlAttribute("decrease_y_linear_velocity_key"), DisplayName("Decrease Y Linear Velocity Key")]
		public Key DecreaseYLinearVelocityKey { get; set; } = Key.Unknown;

		[Serialize, DisplayPriority(5)]
		[XmlAttribute("increase_y_linear_velocity_key"), DisplayName("Increase Y Linear Velocity Key")]
		public Key IncreaseYLinearVelocityKey { get; set; } = Key.Unknown;

		[Serialize, DisplayPriority(6)]
		[XmlAttribute("decrease_angular_velocity_key"), DisplayName("Decrease Angular Velocity Key")]
		public Key DecreaseAngularVelocityKey { get; set; } = Key.Unknown;

		[Serialize, DisplayPriority(7)]
		[XmlAttribute("increase_angular_velocity_key"), DisplayName("Increase Angular Velocity Key")]
		public Key IncreaseAngularVelocityKey { get; set; } = Key.Unknown;

		[Serialize, DisplayPriority(8)]
		[XmlAttribute("linear_velocity_delta"), DisplayName("Linear Velocity Delta")]
		public Vector2 LinearVelocityDelta { get; set; } = new Vector2(0.000000f, 0.000000f);

		[Serialize, DisplayPriority(9)]
		[XmlAttribute("angular_velocity_delta"), DisplayName("Angular Velocity Delta")]
		public float AngularVelocityDelta { get; set; } = 0.000000f;

		[Serialize, DisplayPriority(10)]
		[XmlAttribute("space"), DisplayName("Space")]
		public Space Space { get; set; } = Space.Local;

		[Serialize, DisplayPriority(11)]
		[XmlAttribute("increment_mode"), DisplayName("Increment Mode")]
		public IncrementMode IncrementMode { get; set; } = IncrementMode.Continuous;
	}
}
