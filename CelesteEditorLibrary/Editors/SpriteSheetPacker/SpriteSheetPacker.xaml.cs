using BindingsKernel;
using CelesteEditor.Attributes;
using CelesteEditor.Editors;
using CelesteEditor.Windows;
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

namespace CelesteEditor.Editors
{
    /// <summary>
    /// Interaction logic for Sprite Sheet Packer.xaml
    /// </summary>
    [CustomEditor("Sprite Sheet Packer")]
    [CustomMenuItem("Sprites/Sprite Sheet Packer")]
    public partial class SpriteSheetPacker : Editor
    {
        #region Properties and Fields

        private SpriteSheetPackerViewModel SpriteSheetPackerViewModel { get; set; }

        #endregion

        public SpriteSheetPacker(object targetObject) :
            base(new SpriteSheetPackerViewModel(targetObject))
        {
            SpriteSheetPackerViewModel = ViewModel as SpriteSheetPackerViewModel;

            InitializeComponent();
        }

        private void AddButton_Click(object sender, RoutedEventArgs e)
        {
            Tuple<DialogResult, List<string>> result = FileSystemUtils.PickFilesForLoading(".", new List<string>()
            {
                ".png",
                ".jpg"
            });

            if (result.Item1 == DialogResult.OK)
            {
                SpriteSheetPackerViewModel.AddSpritePaths(result.Item2);
            }
        }

        private void CreateButton_Click(object sender, RoutedEventArgs e)
        {
            SpriteSheetPackerViewModel.CreateSpriteSheet();
            UtilityWindows.MessageWindow("Sprite Sheet created at '" + SpriteSheetPackerViewModel.OutputPath + "'.", "Success");
        }
    }
}
