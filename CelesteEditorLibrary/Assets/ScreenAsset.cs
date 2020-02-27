using BindingsKernel;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.Xml.Serialization;

namespace CelesteEditor.Assets
{
    public class ScreenAsset : Asset<Screen>
    {
        public ScreenAsset(FileInfo fileInfo, Screen screen) :
                  base(fileInfo, screen)
        {
        }

        #region Saving Overrides

        public override void Save()
        {
            using (XmlTextWriter writer = new XmlTextWriter(FileInfo.FullName, Encoding.UTF8))
            {
                writer.Formatting = Formatting.Indented;
                writer.WriteStartDocument();

                try
                {
                    XmlSerializer serializer = new XmlSerializer(AssetObject.GetType());
                    serializer.Serialize(writer, AssetObject);
                }
                catch (Exception e)
                {
                    CelDebug.Fail(e.Message);
                }
                finally
                {
                    writer.WriteEndDocument();
                }
            }
        }

        private void WriteDefaultScreenFile()
        {
            XmlDocument document = new XmlDocument();
            document.AppendChild(document.CreateXmlDeclaration("1.0", "utf-8", ""));

            XmlElement screenElement = document.CreateElementAndAppend("Screen");
            screenElement.CreateAttributeAndAppend("name", AssetObject.Name);
            screenElement.CreateAttributeAndAppend("guid", AssetObject.UniqueIdentifier);

            XmlElement resourcesElement = screenElement.CreateElementAndAppend("Resources");
            resourcesElement.CreateElementAndAppend("Fonts");
            resourcesElement.CreateElementAndAppend("VertexShaders");
            resourcesElement.CreateElementAndAppend("FragmentShaders");
            resourcesElement.CreateElementAndAppend("Sounds");
            resourcesElement.CreateElementAndAppend("Textures");
            resourcesElement.CreateElementAndAppend("Data");
            resourcesElement.CreateElementAndAppend("Models");

            XmlElement gameObjectsElement = screenElement.CreateElementAndAppend("GameObjects");
            XmlElement gameObjectElement = gameObjectsElement.CreateElementAndAppend("GameObject");
            gameObjectElement.CreateAttributeAndAppend("name", "");
            gameObjectElement.CreateAttributeAndAppend("position", "0,0,0");
            gameObjectElement.CreateElementAndAppend("Components");

            document.Save(FileInfo.FullName);
        }

        #endregion
    }
}
