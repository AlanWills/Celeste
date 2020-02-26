using BindingsKernel;
using CelesteEngineEditor.Core;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;

namespace CelesteEngineEditor
{
    public static class Texture2DExtensions
    {
        #region Texture 2D To Image Source

        /// <summary>
        /// Create a new Image Source for a WPF Image from the inputted Texture2D path and the project directory.
        /// </summary>
        /// <param name="texture2D"></param>
        /// <returns></returns>
        public static ImageSource ToImageSource(this Texture2D texture2D)
        {
            using (Bitmap bitmap = texture2D.ToBitmap())
            {
                return bitmap.ToImageSource();
            }
        }

        /// <summary>
        /// Create a new Bitmap Image from the inputted Texture2D path and the project directory.
        /// </summary>
        /// <param name="texture2D"></param>
        /// <returns></returns>
        public static Bitmap ToBitmap(this Texture2D texture2D)
        {
            return Image.FromFile(System.IO.Path.Combine(Project.Current.ProjectDirectory.FullName, texture2D.UniqueIdentifier)) as Bitmap;
        }

        #endregion
    }
}