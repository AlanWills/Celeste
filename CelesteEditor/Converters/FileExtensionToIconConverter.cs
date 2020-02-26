using BindingsKernel;
using CelesteEngineEditor.Extensibility;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Data;

namespace CelesteEngineEditor.Converters
{
    public class FileExtensionToIconConverter : IValueConverter
    {
        /// <summary>
        /// Attempt to convert the inputted object to a file icon uri.
        /// If the input is not a string, we return null.
        /// Otherwise we return a Uri to an icon.
        /// </summary>
        /// <param name="value"></param>
        /// <param name="targetType"></param>
        /// <param name="parameter"></param>
        /// <param name="culture"></param>
        /// <returns></returns>
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (!(value is string))
            {
                CelDebug.Fail();
                return null;
            }

            return FileIconExtensibility.GetFileIconForExtension(value as string);
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            CelDebug.Fail();
            throw new NotImplementedException();
        }
    }
}
