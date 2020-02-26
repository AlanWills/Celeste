using BindingsKernel;
using CelesteEngineEditor.Attributes;
using CelesteEngineEditor.Editors;
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

namespace CelesteEngineEditor.Editors
{
    /// <summary>
    /// Interaction logic for Inspector.xaml
    /// </summary>
    [CustomEditor(typeof(object), "Inspector")]
    [CustomMenuItem("Inspector")]
    public partial class Inspector : Editor
    {
        public Inspector() :
            this(null)
        {
        }

        public Inspector(object targetObject) :
            base(new InspectorViewModel(targetObject))
        {
            InitializeComponent();
        }
    }
}
