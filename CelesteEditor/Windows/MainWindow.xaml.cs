using CelesteEditor.Attributes;
using CelesteEditor.Core;
using CelesteEditor.DataTemplates;
using CelesteEditor.Editors;
using CelesteEditor.Extensibility;
using CelesteEditor.Settings;
using CelesteEditor.UserControls;
using CelesteEditor.ViewModels.Windows;
using DevZest.Windows.Docking;
using MahApps.Metro.Controls;
using NodeNetwork.Toolkit.NodeList;
using NodeNetwork.Toolkit.ValueNode;
using NodeNetwork.ViewModels;
using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Reactive.Linq;
using System.Reflection;
using System.Resources;
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

namespace CelesteEditor.Windows
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : MetroWindow
    {
        #region Properties and Fields

        private MainWindowViewModel ViewModel { get; set; }
        
        #endregion

        public MainWindow()
        {
            InitializeComponent();

            ViewModel = DataContext as MainWindowViewModel;
        }
        
        private void SaveButton_Click(object sender, RoutedEventArgs e)
        {
            ViewModel.Save();
        }
    }
}