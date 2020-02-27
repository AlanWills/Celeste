using BindingsKernel;
using CelesteEditor.Data;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace CelesteEditor.ViewModels.Windows
{
    public class MainWindowViewModel : INotifyPropertyChanged
    {
        #region Properties and Fields

        public event PropertyChangedEventHandler PropertyChanged;

        /// <summary>
        /// All of the available scriptable objects that can be created from any binding libraries.
        /// </summary>
        public List<Type> AvailableTypes { get; private set; } = new List<Type>();

        #endregion

        public MainWindowViewModel()
        {
            //AvailableTypes = new List<Type>();

            //Type scriptableObject = typeof(ScriptableObject);
            //foreach (FileInfo assembly in Directory.GetParent(Assembly.GetExecutingAssembly().Location).EnumerateFiles("*.dll", SearchOption.AllDirectories))
            //{
            //    foreach (Type type in Assembly.LoadFile(assembly.FullName).GetTypes())
            //    {
            //        if (type.IsSubclassOf(scriptableObject) && !type.IsAbstract)
            //        {
            //            AvailableTypes.Add(type);
            //        }
            //    }
            //}

            //SelectedType = AvailableTypes.Count > 0 ? AvailableTypes[0] : null;
        }

        public void Save()
        {
            //XmlDocument document = new XmlDocument();
            //XmlElement element = document.CreateElement("Root");
            //document.AppendChild(element);
            //XmlElement dataElement = document.CreateElement(SelectedType.Name);
            //element.AppendChild(dataElement);

            //foreach (PropertyData property in PropertyData)
            //{
            //    dataElement.SetAttribute(property.XmlName, property.Value.ToString());
            //}

            //document.Save(System.IO.Path.Combine(Directory.GetCurrentDirectory(), "Test.xml"));
        }

        private void NotifyOnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
