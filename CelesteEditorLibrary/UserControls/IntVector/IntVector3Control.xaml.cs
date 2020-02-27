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
using Xceed.Wpf.Toolkit;

namespace CelesteEditor.UserControls.IntVector
{
    /// <summary>
    /// Interaction logic for IntVector3Control.xaml
    /// </summary>
    public partial class IntVector3Control : UserControl
    {
        #region Properties and Fields

        #region X

        public string X
        {
            get { return GetValue(XProperty) as string; }
            set { SetValue(XProperty, value); }
        }

        public static readonly DependencyProperty XProperty =
            DependencyProperty.Register(
            "X",
            typeof(int),
            typeof(IntVector3Control),
            new FrameworkPropertyMetadata(new PropertyChangedCallback(XChanged)));

        private static void XChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            IntegerUpDown integerUpDown = ((IntVector3Control)d).XIntegerUpDownBox;
            integerUpDown.Value = (int)e.NewValue;
        }

        #endregion
    
        #region Y

        public string Y
        {
            get { return GetValue(YProperty) as string; }
            set { SetValue(YProperty, value); }
        }

        public static readonly DependencyProperty YProperty =
            DependencyProperty.Register(
            "Y",
            typeof(int),
            typeof(IntVector3Control),
            new FrameworkPropertyMetadata(new PropertyChangedCallback(YChanged)));

        private static void YChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            IntegerUpDown integerUpDown = ((IntVector3Control)d).YIntegerUpDownBox;
            integerUpDown.Value = (int)e.NewValue;
        }

        #endregion

        #region Z

        public string Z
        {
            get { return GetValue(ZProperty) as string; }
            set { SetValue(ZProperty, value); }
        }

        public static readonly DependencyProperty ZProperty =
            DependencyProperty.Register(
            "Z",
            typeof(int),
            typeof(IntVector3Control),
            new FrameworkPropertyMetadata(new PropertyChangedCallback(ZChanged)));

        private static void ZChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            IntegerUpDown integerUpDown = ((IntVector3Control)d).ZIntegerUpDownBox;
            integerUpDown.Value = (int)e.NewValue;
        }

        #endregion

        #endregion

        public IntVector3Control()
        {
            InitializeComponent();
        }
    }
}