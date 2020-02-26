using BindingsKernel;
using CelesteEngineEditor.Core;
using Microsoft.Win32;
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

namespace CelesteEngineEditor.UserControls
{
    /// <summary>
    /// Interaction logic for FileSelector.xaml
    /// </summary>
    public partial class FileSelector : UserControl
    {
        #region Dependency Properties

        #region Label

        public string Label
        {
            get { return GetValue(LabelProperty) as string; }
            set { SetValue(LabelProperty, value); }
        }

        public static readonly DependencyProperty LabelProperty =
            DependencyProperty.Register(
            "Label",
            typeof(string),
            typeof(FileSelector),
            new FrameworkPropertyMetadata(new PropertyChangedCallback(LabelChanged)));

        private static void LabelChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            string newValue = e.NewValue.ToString();
            TextBlock textBlock = ((FileSelector)d).LabelTextBlock;

            textBlock.Text = newValue;
            textBlock.Visibility = string.IsNullOrEmpty(newValue) ? Visibility.Collapsed : Visibility.Visible;
        }

        #endregion

        #region Selected Path

        public Path SelectedPath
        {
            get { return (Path)GetValue(SelectedPathProperty); }
            set { SetValue(SelectedPathProperty, value); }
        }

        public static readonly DependencyProperty SelectedPathProperty =
            DependencyProperty.Register(
            "SelectedPath",
            typeof(Path),
            typeof(FileSelector),
            new FrameworkPropertyMetadata(new PropertyChangedCallback(SelectedPathChanged))
            {
                BindsTwoWayByDefault = true,
                DefaultUpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
            });

        private static void SelectedPathChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            ((FileSelector)d).SelectedPathTextBox.Text = e.NewValue.ToString();
        }

        #endregion

        #region File Type Display Name

        public string FileTypeDisplayName
        {
            get { return GetValue(FileTypeDisplayNameProperty) as string; }
            set { SetValue(FileTypeDisplayNameProperty, value); }
        }

        public static readonly DependencyProperty FileTypeDisplayNameProperty =
            DependencyProperty.Register(
            "FileTypeDisplayName",
            typeof(string),
            typeof(FileSelector),
            new PropertyMetadata(""));

        #endregion

        #region File Extensions

        public List<string> FileExtensions
        {
            get { return GetValue(FileExtensionsProperty) as List<string>; }
            set { SetValue(FileExtensionsProperty, value); }
        }

        public static readonly DependencyProperty FileExtensionsProperty =
            DependencyProperty.Register(
            "FileExtensions",
            typeof(List<string>),
            typeof(FileSelector),
            new PropertyMetadata(new List<string>()));

        #endregion

        #endregion

        public FileSelector()
        {
            InitializeComponent();
        }

        private void BrowseButton_Click(object sender, RoutedEventArgs e)
        {
            Tuple<System.Windows.Forms.DialogResult, string> result = FileSystemUtils.PickFileForSaving(FileTypeDisplayName, FileExtensions);

            if (result.Item1 == System.Windows.Forms.DialogResult.OK)
            {
                SelectedPathTextBox.Text = result.Item2;
                SelectedPath = new Path(result.Item2);
                GetBindingExpression(SelectedPathProperty).UpdateSource();
            }
        }

        private void SelectedPathTextBox_LostKeyboardFocus(object sender, KeyboardFocusChangedEventArgs e)
        {
            SelectedPath = new Path(SelectedPathTextBox.Text);
            GetBindingExpression(SelectedPathProperty).UpdateSource();
        }
    }
}
