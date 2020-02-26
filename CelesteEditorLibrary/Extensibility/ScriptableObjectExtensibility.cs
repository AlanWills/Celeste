using BindingsKernel;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Xml;
using System.Xml.Serialization;
using static CelesteEngineEditor.Assets.ScriptableObjectAsset;

namespace CelesteEngineEditor.Extensibility
{
    public static class ScriptableObjectExtensibility
    {
        #region Properties and Fields

        private static List<Type> ScriptableObjectsImpl { get; set; } = new List<Type>();

        private static ReadOnlyCollection<Type> scriptableObjects;
        /// <summary>
        /// All of the available custom editors loaded into the application.
        /// Call LoadEditors to refresh this collection.
        /// </summary>
        public static ReadOnlyCollection<Type> ScriptableObjects
        {
            get
            {
                if (scriptableObjects == null)
                {
                    scriptableObjects = new ReadOnlyCollection<Type>(ScriptableObjectsImpl);
                    LoadScriptableObjects();
                }

                return scriptableObjects;
            }
        }

        #endregion

        /// <summary>
        /// Iterate through all DLLs in same location as the editor and load all non-abstract classes derived from scriptable object.
        /// </summary>
        public static void LoadScriptableObjects()
        {
            ScriptableObjectsImpl.Clear();

            // Go through each DLL
            foreach (Type type in ExtensibilityUtils.Types)
            {
                if (!type.IsAbstract && type.IsSubclassOf(typeof(ScriptableObject)))
                {
                    ScriptableObjectsImpl.Add(type);
                }
            }
        }

        //public static ScriptableObject LoadScriptableObject(FileInfo objectFile)
        //{
        //    return LoadScriptableObject(objectFile.FullName);
        //}

        //public static ScriptableObject LoadScriptableObject(string objectFilePath)
        //{
        //    using (XmlTextReader reader = new XmlTextReader(objectFilePath))
        //    {
        //        try
        //        {
        //            XmlSerializer serializer = new XmlSerializer(typeof(Root));
        //            return (serializer.Deserialize(reader) as Root).ScriptableObject;
        //        }
        //        catch (Exception e)
        //        {
        //            CelDebug.Fail(e.Message);
        //            return null;
        //        }
        //    }
        //}
    }
}