using BindingsKernel;
using CelesteEditor.Data;
using CelesteEditor.Editors;
using CelesteEditor.ViewModels;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace CelesteEditor.Editors
{
    public class SpriteSheetUnpackerViewModel : EditorViewModel
    {
        #region Properties and Fields

        private Path sourcePath = new Path();
        public Path SourcePath
        {
            get { return sourcePath; }
            set
            {
                bool sourceChanged = sourcePath.FullPath != value.FullPath;
                sourcePath = value;

                if (sourceChanged && System.IO.File.Exists(sourcePath.FullPath))
                {
                    using (Bitmap bitmap = Image.FromFile(sourcePath.FullPath) as Bitmap)
                    {
                        SourceImage = bitmap.ToImageSource();
                    }
                }
            }
        }

        private ImageSource sourceImage;
        public ImageSource SourceImage
        {
            get { return sourceImage; }
            set
            {
                sourceImage = value;
                NotifyOnPropertyChanged(nameof(SourceImage));
            }
        }

        private Path outputDirectory = new Path("");
        public Path OutputDirectory
        {
            get { return outputDirectory; }
            set
            {
                outputDirectory = value;
                NotifyOnPropertyChanged(nameof(OutputDirectory));
            }
        }

        private int spriteSheetXDimensions = 2;
        public int SpriteSheetXDimension
        {
            get { return spriteSheetXDimensions; }
            set
            {
                spriteSheetXDimensions = Math.Max(1, value);
                NotifyOnPropertyChanged(nameof(SpriteSheetXDimension));
            }
        }

        private int spriteSheetYDimension = 2;
        public int SpriteSheetYDimension
        {
            get { return spriteSheetYDimension; }
            set
            {
                spriteSheetYDimension = Math.Max(1, value);
                NotifyOnPropertyChanged(nameof(SpriteSheetYDimension));
            }
        }

        #endregion

        public SpriteSheetUnpackerViewModel(object targetObject) :
            base(targetObject)
        {
        }
        
        #region Sprite Sheet Functions

        public void CreateSprites()
        {
            string sourceImageName = System.IO.Path.GetFileNameWithoutExtension(SourcePath.FullPath) + "_";
            string sourceImageExtension = System.IO.Path.GetExtension(SourcePath.FullPath);

            using (Bitmap sourceImage = Image.FromFile(sourcePath.FullPath) as Bitmap)
            {
                int singleImageWidth = sourceImage.Width / SpriteSheetXDimension;
                int singleImageHeight = sourceImage.Height / SpriteSheetYDimension;

                for (int row = 0; row < SpriteSheetYDimension; ++row)
                {
                    for (int column = 0; column < SpriteSheetXDimension; ++column)
                    {
                        using (Bitmap bitmap = new Bitmap(singleImageWidth, singleImageHeight))
                        {
                            for (int y = 0; y < singleImageHeight; ++y)
                            {
                                for (int x = 0; x < singleImageWidth; ++x)
                                {
                                    bitmap.SetPixel(x, y, sourceImage.GetPixel(column * singleImageWidth + x, row * singleImageHeight + y));
                                }
                            }

                            bitmap.MakeTransparent();

                            string imageIndexStr = (row * SpriteSheetXDimension + column).ToString();
                            bitmap.Save(System.IO.Path.Combine(OutputDirectory.FullPath, sourceImageName + imageIndexStr + sourceImageExtension), ImageFormat.Png);
                        }
                    }
                }
            }
        }

        #endregion
    }
}