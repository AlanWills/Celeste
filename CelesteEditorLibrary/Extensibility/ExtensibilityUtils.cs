using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEngineEditor.Extensibility
{
    public static class ExtensibilityUtils
    {
        #region Properties and Fields

        private static List<Assembly> AssembliesImpl { get; } = new List<Assembly>();
        private static ReadOnlyCollection<Assembly> assemblies;
        /// <summary>
        /// All of the assemblies present in the same folder as the editor application.
        /// Call LoadAssemblies to refresh this collection.
        /// </summary>
        public static ReadOnlyCollection<Assembly> Assemblies
        {
            get
            {
                if (assemblies == null)
                {
                    assemblies = new ReadOnlyCollection<Assembly>(AssembliesImpl);
                    LoadAssemblies();
                }

                return assemblies;
            }
        }

        private static List<Type> TypesImpl { get; } = new List<Type>();
        private static ReadOnlyCollection<Type> types;
        /// <summary>
        /// All of the types loaded from the Assemblies.
        /// Call LoadTypes to refresh this collection.
        /// </summary>
        public static ReadOnlyCollection<Type> Types
        {
            get
            {
                if (types == null)
                {
                    types = new ReadOnlyCollection<Type>(TypesImpl);
                    LoadTypes();
                }

                return types;
            }
        }

        #endregion

        public static void LoadAssemblies()
        {
            AssembliesImpl.Clear();

            foreach (FileInfo assemblyFile in Directory.GetParent(Assembly.GetEntryAssembly().Location).EnumerateFiles("*.dll", SearchOption.AllDirectories))
            {
                try
                {
                    Assembly assembly = Assembly.LoadFile(assemblyFile.FullName);
                    AssembliesImpl.Add(assembly);
                }
                catch { }
            }
        }

        public static void LoadTypes()
        {
            TypesImpl.Clear();

            foreach (Assembly assembly in Assemblies)
            {
                try
                {
                    TypesImpl.AddRange(assembly.GetTypes());
                }
                catch { }
            }
        }
    }
}