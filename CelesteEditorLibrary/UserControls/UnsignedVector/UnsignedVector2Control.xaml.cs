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

namespace CelesteEditor.UserControls.UnsignedVector
{
    /// <summary>
    /// Interaction logic for UnsignedVector2Control.xaml
    /// </summary>
    public partial class UnsignedVector2Control : UserControl
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
            typeof(float),
            typeof(UnsignedVector2Control),
            new FrameworkPropertyMetadata(new PropertyChangedCallback(XChanged)));

        private static void XChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            SingleUpDown singleUpDown = ((UnsignedVector2Control)d).XSingleUpDownBox;
            singleUpDown.Value = (float)e.NewValue;
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
            typeof(float),
            typeof(UnsignedVector2Control),
            new FrameworkPropertyMetadata(new PropertyChangedCallback(YChanged)));

        private static void YChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            SingleUpDown integerUpDown = ((UnsignedVector2Control)d).XSingleUpDownBox;
            integerUpDown.Value = (float)e.NewValue;
        }

        #endregion

        #endregion

        public UnsignedVector2Control()
        {
            InitializeComponent();
        }
    }
}