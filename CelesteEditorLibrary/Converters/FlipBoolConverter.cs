using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;

namespace CelesteEngineEditor.Converters
{
    public class FlipBoolConverter : IValueConverter
    {
        /// <summary>
        /// If the input is a boolean, returns the not value of the input.
        /// Otherwise returns false.
        /// </summary>
        /// <param name="value"></param>
        /// <param name="targetType"></param>
        /// <param name="parameter"></param>
        /// <param name="culture"></param>
        /// <returns></returns>
        public object Convert(object value, Type targetType = null, object parameter = null, CultureInfo culture = null)
        {
            if (!(value is bool))
            {
                return false;
            }

            return !(bool)value;
        }

        /// <summary>
        /// If the input is a boolean, returns the not value of the input.
        /// Otherwise returns false.
        /// </summary>
        /// <param name="value"></param>
        /// <param name="targetType"></param>
        /// <param name="parameter"></param>
        /// <param name="culture"></param>
        /// <returns></returns>
        public object ConvertBack(object value, Type targetType = null, object parameter = null, CultureInfo culture = null)
        {
            if (!(value is bool))
            {
                return false;
            }

            return !(bool)value;
        }
    }
}