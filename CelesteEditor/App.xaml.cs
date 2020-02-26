using CelesteEngineEditor.Core;
using CelesteEngineEditor.DataTemplates;
using CelesteEngineEditor.Extensibility;
using CelesteEngineEditor.Settings;
using CelesteEngineEditor.Windows;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Navigation;

namespace CelesteEngineEditor
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        protected override void OnStartup(StartupEventArgs e)
        {
            base.OnStartup(e);

            Current.DispatcherUnhandledException += Current_DispatcherUnhandledException;

            // Load up our local settings to initialize any custom app data
            LocalSettings.Load();

            // Load any resources from 3rd party dlls
            ResourceExtensibility.LoadExternalEditorResources(Resources);

            if (Directory.Exists(LocalSettings.Instance.LastOpenedProjectLocation))
            {
                // We want to load our previous project so do that now
                Project.Load(LocalSettings.Instance.LastOpenedProjectLocation);
            }
        }

        private void Current_DispatcherUnhandledException(object sender, System.Windows.Threading.DispatcherUnhandledExceptionEventArgs e)
        {
            Exception exc = e.Exception;

            while (exc != null)
            {
                EditorWindows.MessageWindow(exc.Message);
                exc = exc.InnerException;
            }

            EditorWindows.MessageWindow(e.Exception.StackTrace);
        }
    }
}
