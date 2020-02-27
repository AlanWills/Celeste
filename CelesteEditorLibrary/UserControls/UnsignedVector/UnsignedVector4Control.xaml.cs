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
    /// Interaction logic for UnsignedVector4Control.xaml
    /// </summary>
    public partial class UnsignedVector4Control : UserControl
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
            typeof(UnsignedVector4Control),
            new FrameworkPropertyMetadata(new PropertyChangedCallback(XChanged)));

        private static void XChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            SingleUpDown singleUpDown = ((UnsignedVector4Control)d).XSingleUpDownBox;
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
            typeof(UnsignedVector4Control),
            new FrameworkPropertyMetadata(new PropertyChangedCallback(YChanged)));

        private static void YChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            SingleUpDown singleUpDown = ((UnsignedVector4Control)d).YSingleUpDownBox;
            singleUpDown.Value = (float)e.NewValue;
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
            typeof(float),
            typeof(UnsignedVector4Control),
            new FrameworkPropertyMetadata(new PropertyChangedCallback(ZChanged)));

        private static void ZChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            SingleUpDown singleUpDown = ((UnsignedVector4Control)d).ZSingleUpDownBox;
            singleUpDown.Value = (float)e.NewValue;
        }

        #endregion

        #region W

        public string W
        {
            get { return GetValue(WProperty) as string; }
            set { SetValue(WProperty, value); }
        }

        public static readonly DependencyProperty WProperty =
            DependencyProperty.Register(
            "W",
            typeof(float),
            typeof(UnsignedVector4Control),
            new FrameworkPropertyMetadata(new PropertyChangedCallback(WChanged)));

        private static void WChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            SingleUpDown singleUpDown = ((UnsignedVector4Control)d).WSingleUpDownBox;
            singleUpDown.Value = (float)e.NewValue;
        }

        #endregion

        #endregion

        public UnsignedVector4Control()
        {
            InitializeComponent();
        }
    }
}