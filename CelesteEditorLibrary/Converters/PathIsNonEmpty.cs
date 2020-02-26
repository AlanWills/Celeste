using BindingsKernel;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;

namespace CelesteEngineEditor.Converters
{
    public class PathIsNonEmpty : IValueConverter
    {
        /// <summary>
        /// Returns true if the inputted object is a non-empty string or non-empty path.
        /// </summary>
        /// <param name="value"></param>
        /// <param name="targetType"></param>
        /// <param name="parameter"></param>
        /// <param name="culture"></param>
        /// <returns></returns>
        public object Convert(object value, Type targetType = null, object parameter = null, CultureInfo culture = null)
        {
            if (value is Path)
            {
                return !string.IsNullOrEmpty((value as Path).FullPath);
            }
            else if (value is string)
            {
                return !string.IsNullOrEmpty(value as string);
            }

            return false;
        }

        public object ConvertBack(object value, Type targetType = null, object parameter = null, CultureInfo culture = null)
        {
            throw new NotImplementedException();
        }
    }
}