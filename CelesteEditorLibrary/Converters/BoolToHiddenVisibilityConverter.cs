using System;
using System.Globalization;
using System.Windows;
using System.Windows.Data;

namespace CelesteEditor.Converters
{
    public class BoolToHiddenVisibilityConverter : IValueConverter
    {
        /// <summary>
        /// Converts true to Visible.
        /// Converts false to Hidden.
        /// </summary>
        /// <param name="value"></param>
        /// <param name="targetType"></param>
        /// <param name="parameter"></param>
        /// <param name="culture"></param>
        /// <returns></returns>
        public object Convert(object value, Type targetType = null, object parameter = null, CultureInfo culture = null)
        {
            bool b = value is bool ? (bool)value : true;
            return b ? Visibility.Visible : Visibility.Hidden;
        }

        /// <summary>
        /// Converts Hidden to false.
        /// Converts anything else to true.
        /// </summary>
        /// <param name="value"></param>
        /// <param name="targetType"></param>
        /// <param name="parameter"></param>
        /// <param name="culture"></param>
        /// <returns></returns>
        public object ConvertBack(object value, Type targetType = null, object parameter = null, CultureInfo culture = null)
        {
            Visibility v = value is Visibility ? (Visibility)value : Visibility.Visible;
            return v == Visibility.Hidden ? false : true;
        }
    }
}
