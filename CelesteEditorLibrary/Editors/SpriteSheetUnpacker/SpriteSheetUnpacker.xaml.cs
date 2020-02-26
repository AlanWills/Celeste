using BindingsKernel;
using CelesteEngineEditor.Attributes;
using CelesteEngineEditor.Editors;
using CelesteEngineEditor.Windows;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Forms;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace CelesteEngineEditor.Editors
{
    /// <summary>
    /// Interaction logic for Sprite Sheet Unpacker.xaml
    /// </summary>
    [CustomEditor("Sprite Sheet Unpacker")]
    [CustomMenuItem("Sprites/Sprite Sheet Unpacker")]
    public partial class SpriteSheetUnpacker : Editor
    {
        #region Properties and Fields

        private SpriteSheetUnpackerViewModel SpriteSheetUnpackerViewModel { get; set; }

        #endregion

        public SpriteSheetUnpacker(object targetObject) :
            base(new SpriteSheetUnpackerViewModel(targetObject))
        {
            SpriteSheetUnpackerViewModel = ViewModel as SpriteSheetUnpackerViewModel;
            SpriteSheetUnpackerViewModel.PropertyChanged += SpriteSheetUnpackerViewModel_PropertyChanged;

            InitializeComponent();
        }

        private void SpriteSheetUnpackerViewModel_PropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e)
        {
            if (e.PropertyName == nameof(SpriteSheetUnpackerViewModel.SpriteSheetXDimension) ||
                e.PropertyName == nameof(SpriteSheetUnpackerViewModel.SpriteSheetYDimension))
            {
                RebuildLines();
            }
            else if (e.PropertyName == nameof(SpriteSheetUnpackerViewModel.SourceImage))
            {
                Canvas.Width = SpriteSheetUnpackerViewModel.SourceImage.Width;
                Canvas.Height = SpriteSheetUnpackerViewModel.SourceImage.Height;

                RebuildLines();
            }
        }

        private void UnpackButton_Click(object sender, RoutedEventArgs e)
        {
            SpriteSheetUnpackerViewModel.CreateSprites();
            UtilityWindows.MessageWindow("Sprites unpacked from Sprite Sheet and stored in '" + SpriteSheetUnpackerViewModel.OutputDirectory + "'.", "Success");
        }

        #region Utility Functions

        private void RebuildLines()
        {
            Canvas.Children.Clear();
            Canvas.Children.Add(SourceImage);

            for (int row = 1, n = SpriteSheetUnpackerViewModel.SpriteSheetYDimension; row < n; ++row)
            {
                Line line = new Line();
                line.Stroke = Brushes.Blue;
                line.StrokeThickness = 1;

                line.X1 = 0;
                line.X2 = Canvas.Width;
                line.Y1 = (Canvas.Height * row) / n;
                line.Y2 = (Canvas.Height * row) / n;

                Canvas.Children.Add(line);
            }

            for (int column = 1, n = SpriteSheetUnpackerViewModel.SpriteSheetXDimension; column < n; ++column)
            {
                Line line = new Line();
                line.Stroke = Brushes.Blue;
                line.StrokeThickness = 1;

                line.X1 = (Canvas.Width * column) / n;
                line.X2 = (Canvas.Width * column) / n;
                line.Y1 = 0;
                line.Y2 = Canvas.Height;

                Canvas.Children.Add(line);
            }
        }

        #endregion
    }
}
