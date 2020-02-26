using CelesteEngineEditor.Extensibility;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Resources;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace CelesteEngineEditor.Extensibility
{
    public static class ResourceExtensibility
    {
        /// <summary>
        /// Iterate through all DLLs in same location as the editor and see if they have a resource dictionary in the following location:
        /// ResourceDictionaries/EditorResources.xaml
        /// If the dictionary exists, add it to the inputted dictionary's merged dictionaries.
        /// </summary>
        public static void LoadExternalEditorResources(ResourceDictionary resourceDictionary)
        {
            // Go through each DLL
            foreach (Assembly assembly in ExtensibilityUtils.Assemblies)
            {
                string loadedAssemblyName = assembly.GetName().Name;
                using (var resourceStream = assembly.GetManifestResourceStream(loadedAssemblyName + ".g.resources"))
                {
                    // See if we actually have some resources to load
                    if (resourceStream != null)
                    {
                        // Then attempt to find the corresponding property data template 
                        ResourceSet resourceSet = new ResourceSet(resourceStream);

                        // Check to see if we have a xaml resource dictionary specifying custom data templates
                        if (resourceSet.GetObject("resourcedictionaries/editorresources.xaml") != null)
                        {
                            // Create the resource dictionary and add it to the inputted dictionary's merged dictionaries.
                            ResourceDictionary assemblyDictionary = new ResourceDictionary();
                            assemblyDictionary.Source = new Uri("pack://application:,,,/" + loadedAssemblyName + ";component/ResourceDictionaries/EditorResources.xaml", UriKind.RelativeOrAbsolute);
                            resourceDictionary.MergedDictionaries.Add(assemblyDictionary);
                        }
                    }
                }
            }
        }
    }
}
