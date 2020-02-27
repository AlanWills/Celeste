using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Interactivity;

namespace CelesteEditor.Behaviours
{
	public class AutoFocusBehaviour : Behavior<UIElement>
	{
        protected override void OnAttached()
        {
            base.OnAttached();

            AssociatedObject.Focus();
        }
    }
}
