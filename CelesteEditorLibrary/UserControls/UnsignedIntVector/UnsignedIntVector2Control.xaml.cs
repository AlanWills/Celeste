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

namespace CelesteEditor.UserControls.UnsignedIntVector
{
    /// <summary>
    /// Interaction logic for UnsignedIntVector2Control.xaml
    /// </summary>
    public partial class UnsignedIntVector2Control : UserControl
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
            typeof(uint),
            typeof(UnsignedIntVector2Control),
            new FrameworkPropertyMetadata(new PropertyChangedCallback(XChanged)));

        private static void XChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            uint newValue = (uint)e.NewValue;
            IntegerUpDown integerUpDown = ((UnsignedIntVector2Control)d).XIntegerUpDownBox;

            integerUpDown.Value = (int)newValue;
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
            typeof(uint),
            typeof(UnsignedIntVector2Control),
            new FrameworkPropertyMetadata(new PropertyChangedCallback(YChanged)));

        private static void YChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            uint newValue = (uint)e.NewValue;
            IntegerUpDown integerUpDown = ((UnsignedIntVector2Control)d).YIntegerUpDownBox;

            integerUpDown.Value = (int)newValue;
        }

        #endregion

        #endregion

        public UnsignedIntVector2Control()
        {
            InitializeComponent();
        }
    }
}