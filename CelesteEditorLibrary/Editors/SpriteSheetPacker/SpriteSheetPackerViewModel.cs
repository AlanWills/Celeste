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
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace CelesteEditor.Editors
{
    public class SpriteSheetPackerViewModel : EditorViewModel
    {
        #region Properties and Fields

        public ObservableCollection<string> SpritePaths { get; private set; } = new ObservableCollection<string>();

        private Path outputPath = new Path("");
        public Path OutputPath
        {
            get { return outputPath; }
            set
            {
                outputPath = value;
                NotifyOnPropertyChanged(nameof(OutputPath));
            }
        }

        private int spriteSheetXDimensions = 1;
        public int SpriteSheetXDimension
        {
            get { return spriteSheetXDimensions; }
            set
            {
                spriteSheetXDimensions = Math.Max(1, value);

                RebuildPreviewImage();
                NotifyOnPropertyChanged(nameof(SpriteSheetXDimension));
            }
        }

        private int spriteSheetYDimension = 1;
        public int SpriteSheetYDimension
        {
            get { return spriteSheetYDimension; }
            set
            {
                spriteSheetYDimension = Math.Max(1, value);

                RebuildPreviewImage();
                NotifyOnPropertyChanged(nameof(SpriteSheetYDimension));
            }
        }

        private HorizontalAnchor horizontalAnchor = HorizontalAnchor.Left;
        public HorizontalAnchor HorizontalAnchor
        {
            get { return horizontalAnchor; }
            set
            {
                horizontalAnchor = value;
                RebuildPreviewImage();
            }
        }

        private VerticalAnchor verticalAnchor = VerticalAnchor.Top;
        public VerticalAnchor VerticalAnchor
        {
            get { return verticalAnchor; }
            set
            {
                verticalAnchor = value;
                RebuildPreviewImage();
            }
        }

        private ImageSource previewImage;
        public ImageSource PreviewImage
        {
            get { return previewImage; }
            set
            {
                previewImage = value;
                NotifyOnPropertyChanged(nameof(previewImage));
            }
        }

        #endregion

        public SpriteSheetPackerViewModel(object targetObject) :
            base(targetObject)
        {
        }

        #region Sprite Path Functions

        public void AddSpritePaths(List<string> paths)
        {
            foreach (string path in paths)
            {
                // Do not use AddSpritePath here as it will cause a preview rebuild for every path
                SpritePaths.Add(path);
            }
            
            RebuildPreviewImage();
        }

        public void AddSpritePath(string path)
        {
            SpritePaths.Add(path);
            RebuildPreviewImage();
        }

        #endregion

        #region Sprite Sheet Functions

        private void RebuildPreviewImage()
        {
            using (Bitmap bitmap = CreateSpriteSheetBitmap())
            {
                PreviewImage = bitmap.ToImageSource();
            }
        }

        private Bitmap CreateSpriteSheetBitmap()
        {
            List<Image> images = new List<Image>(SpritePaths.Count);

            foreach (string str in SpritePaths)
            {
                images.Add(Image.FromFile(str));
            }

            Bitmap bitmap = new Bitmap(SpriteSheetXDimension * images[0].Width, SpriteSheetYDimension * images[0].Height);
            for (int row = 0; row < SpriteSheetYDimension; ++row)
            {
                for (int column = 0; column < SpriteSheetXDimension; ++column)
                {
                    int currentImageIndex = column + row * SpriteSheetXDimension;
                    if (currentImageIndex < images.Count)
                    {
                        Bitmap image = images[currentImageIndex] as Bitmap;

                        int horizontalOffset = horizontalAnchor == HorizontalAnchor.Left ?
                                        column * image.Width : (SpriteSheetXDimension - column - 1) * image.Width;

                        int verticalOffset = verticalAnchor == VerticalAnchor.Top ?
                                        row * image.Height : (SpriteSheetYDimension - row - 1) * image.Height;

                        for (int y = 0; y < image.Height; ++y)
                        {
                            for (int x = 0; x < image.Width; ++x)
                            {
                                bitmap.SetPixel(horizontalOffset + x, verticalOffset + y, image.GetPixel(x, y));
                            }
                        }
                    }
                }
            }

            return bitmap;
        }

        public void CreateSpriteSheet()
        {
            CelDebug.Assert(!string.IsNullOrEmpty(OutputPath.FullPath));

            if (!string.IsNullOrEmpty(OutputPath.FullPath))
            {
                List<Image> images = new List<Image>(SpritePaths.Count);

                foreach (string str in SpritePaths)
                {
                    images.Add(Image.FromFile(str));
                }

                using (Bitmap bitmap = CreateSpriteSheetBitmap())
                {
                    bitmap.MakeTransparent();
                    bitmap.Save(OutputPath.FullPath, ImageFormat.Png);
                }
            }
        }

        #endregion
    }
}
