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
	public class KeyboardTransformer : Component
	{
		[Serialize, DisplayPriority(1)]
		[XmlAttribute("active"), DisplayName("Active")]
		public bool Active { get; set; } = true;

		[Serialize, DisplayPriority(2)]
		[XmlAttribute("translate_left_key"), DisplayName("Translate Left Key")]
		public Key TranslateLeftKey { get; set; } = Key.Unknown;

		[Serialize, DisplayPriority(3)]
		[XmlAttribute("translate_right_key"), DisplayName("Translate Right Key")]
		public Key TranslateRightKey { get; set; } = Key.Unknown;

		[Serialize, DisplayPriority(4)]
		[XmlAttribute("translate_up_key"), DisplayName("Translate Up Key")]
		public Key TranslateUpKey { get; set; } = Key.Unknown;

		[Serialize, DisplayPriority(5)]
		[XmlAttribute("translate_down_key"), DisplayName("Translate Down Key")]
		public Key TranslateDownKey { get; set; } = Key.Unknown;

		[Serialize, DisplayPriority(6)]
		[XmlAttribute("rotate_left_key"), DisplayName("Rotate Left Key")]
		public Key RotateLeftKey { get; set; } = Key.Unknown;

		[Serialize, DisplayPriority(7)]
		[XmlAttribute("rotate_right_key"), DisplayName("Rotate Right Key")]
		public Key RotateRightKey { get; set; } = Key.Unknown;

		[Serialize, DisplayPriority(8)]
		[XmlAttribute("translation_speed"), DisplayName("Translation Speed")]
		public float TranslationSpeed { get; set; } = 1.000000f;

		[Serialize, DisplayPriority(9)]
		[XmlAttribute("rotation_speed"), DisplayName("Rotation Speed")]
		public float RotationSpeed { get; set; } = 0.010000f;
	}
}
