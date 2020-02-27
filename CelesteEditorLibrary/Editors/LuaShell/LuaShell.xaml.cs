using BindingsKernel;
using CelesteEditor.Attributes;
using CelesteEditor.Editors;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace CelesteEditor.Editors
{
    /// <summary>
    /// Interaction logic for LuaShell.xaml
    /// </summary>
    [CustomEditor(typeof(void), "LuaShell")]
    [CustomMenuItem("LuaShell")]
    public partial class LuaShell : Editor
    {
        #region Properties and Fields
        
        public LuaShellViewModel LuaShellViewModel { get; }

        #endregion

        public LuaShell() :
            this(null)
        {
        }

        public LuaShell(object targetObject) :
            base(new LuaShellViewModel(targetObject))
        {
            LuaShellViewModel = ViewModel as LuaShellViewModel;

            InitializeComponent();
        }

        #region Event Callbacks

        private void SendButton_Click(object sender, RoutedEventArgs e)
        {
            LuaShellViewModel.Send();
        }

        #endregion
    }
}
