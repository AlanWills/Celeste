using System;
using System.Globalization;
using System.Windows;
using System.Windows.Data;
using System.Windows.Markup;

namespace CelesteEngineEditor.Converters
{
    public class BoolToCollapsedVisibilityConverter : MarkupExtension, IValueConverter
    {
        /// <summary>
        /// Converts true to Visible.
        /// Converts false to Collapsed.
        /// </summary>
        /// <param name="value"></param>
        /// <param name="targetType"></param>
        /// <param name="parameter"></param>
        /// <param name="culture"></param>
        /// <returns></returns>
        public object Convert(object value, Type targetType = null, object parameter = null, CultureInfo culture = null)
        {
            bool b = value is bool ? (bool)value : true;
            return b ? Visibility.Visible : Visibility.Collapsed;
        }

        /// <summary>
        /// Converts Collapsed to false.
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
            return v == Visibility.Collapsed ? false : true;
        }

        public override object ProvideValue(IServiceProvider serviceProvider)
        {
            return this;
        }
    }


    public class InverseBoolToCollapsedVisibilityConverter : IValueConverter
    {
        /// <summary>
        /// Converts true to Visible.
        /// Converts false to Collapsed.
        /// </summary>
        /// <param name="value"></param>
        /// <param name="targetType"></param>
        /// <param name="parameter"></param>
        /// <param name="culture"></param>
        /// <returns></returns>
        public object Convert(object value, Type targetType = null, object parameter = null, CultureInfo culture = null)
        {
            bool b = value is bool ? (bool)value : true;
            return b ? Visibility.Collapsed : Visibility.Visible  ;
        }

        /// <summary>
        /// Converts Collapsed to false.
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
            return v == Visibility.Collapsed ? true : false;
        }
    }
}
