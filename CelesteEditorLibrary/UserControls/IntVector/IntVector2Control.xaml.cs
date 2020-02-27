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
    /// Interaction logic for IntVector2Control.xaml
    /// </summary>
    public partial class IntVector2Control : UserControl
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
            typeof(IntVector2Control),
            new FrameworkPropertyMetadata(new PropertyChangedCallback(XChanged)));

        private static void XChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            IntegerUpDown integerUpDown = ((IntVector2Control)d).XIntegerUpDownBox;
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
            typeof(IntVector2Control),
            new FrameworkPropertyMetadata(new PropertyChangedCallback(YChanged)));

        private static void YChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            IntegerUpDown integerUpDown = ((IntVector2Control)d).YIntegerUpDownBox;
            integerUpDown.Value = (int)e.NewValue;
        }

        #endregion

        #endregion

        public IntVector2Control()
        {
            InitializeComponent();
        }
    }
}