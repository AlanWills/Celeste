using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Interactivity;

namespace CelesteEditor.Behaviours
{
    public class CursorAtEndOfTextBoxBehaviour : Behavior<TextBox>
    {
        private TextBox TextBox { get; set; }

        protected override void OnAttached()
        {
            base.OnAttached();

            TextBox = AssociatedObject as TextBox;

            if (TextBox == null)
            {
                return;
            }

            TextBox.GotFocus += TextBoxGotFocus;
        }

        protected override void OnDetaching()
        {
            if (TextBox == null)
            {
                return;
            }

            TextBox.GotFocus -= TextBoxGotFocus;

            base.OnDetaching();
        }

        private void TextBoxGotFocus(object sender, RoutedEventArgs routedEventArgs)
        {
            TextBox.CaretIndex = TextBox.Text.Length;
        }
    }
}
