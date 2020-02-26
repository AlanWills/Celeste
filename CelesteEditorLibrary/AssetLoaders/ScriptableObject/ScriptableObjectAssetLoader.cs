using BindingsKernel;
using BindingsKernel.Serialization;
using CelesteEngineEditor.Assets;
using CelesteEngineEditor.Core;
using CelesteEngineEditor.Extensibility;
using System;
using System.IO;
using System.Linq;
using System.Xml;
using System.Xml.Serialization;
using static CelesteEngineEditor.Assets.ScriptableObjectAsset;

namespace CelesteEngineEditor.AssetLoaders
{
    public class ScriptableObjectAssetLoader : AssetLoader
    {
        #region Properties and Fields

        /// <summary>
        /// The file extension which this loader is responsible for loading into a project asset.
        /// </summary>
        public const string FileExtension = ".asset";

        /// <summary>
        /// The file extension which this loader is responsible for loading into a project asset.
        /// </summary>
        public override string AssetFileExtension { get { return FileExtension; } }

        #endregion

        #region Load Functions

        /// <summary>
        /// Load the scriptable object asset and return it.
        /// Returns null if this process did not succeed.
        /// </summary>
        /// <param name="filePath"></param>
        /// <returns></returns>
        public override IAsset Load(FileInfo file)
        {
            using (XmlTextReader reader = new XmlTextReader(file.FullName))
            {
                try
                {
                    reader.MoveToContent();
                    string typeName = reader.LocalName;

                    Type type = ScriptableObjectExtensibility.ScriptableObjects.FirstOrDefault(x => x.Name == typeName);
                    CelDebug.AssertNotNull(type);

                    ScriptableObject scriptableObject = Activator.CreateInstance(type) as ScriptableObject;
                    ScriptableObjectAsset asset = new ScriptableObjectAsset(file, scriptableObject);
                    asset.ReadXml(reader);

                    return asset;
                }
                catch (Exception e)
                {
                    CelDebug.Fail(e.Message);
                    return null;
                }
            }
        }

        #endregion
    }
}