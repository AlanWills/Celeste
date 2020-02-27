using BindingsKernel;
using CelesteEditor.Core;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;

namespace CelesteEditor.Converters
{
    public class Texture2DToImageSourceConverter : IValueConverter
    {
        public object Convert(object value, Type targetType = null, object parameter = null, CultureInfo culture = null)
        {
            Texture2D texture2D = value as Texture2D;
            if (texture2D == null)
            {
                return null;
            }

            return texture2D.ToImageSource();
        }

        public object ConvertBack(object value, Type targetType = null, object parameter = null, CultureInfo culture = null)
        {
            CelDebug.Fail("Not Implemented");
            return null;
        }
    }
}