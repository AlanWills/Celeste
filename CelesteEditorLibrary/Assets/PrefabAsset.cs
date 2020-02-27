using BindingsKernel;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace CelesteEditor.Assets
{
    public class PrefabAsset : Asset<Prefab>
    {
        public PrefabAsset(FileInfo fileInfo, Prefab prefab) :
               base(fileInfo, prefab)
        {
        }

        #region Saving Overrides

        public override void Save()
        {
            if (FileInfo.Length == 0)
            {
                WriteDefaultPrefabFile();
            }
        }

        private void WriteDefaultPrefabFile()
        {
            XmlDocument document = new XmlDocument();
            document.AppendChild(document.CreateXmlDeclaration("1.0", "utf-8", ""));

            XmlElement prefabElement = document.CreateElementAndAppend("Prefab");
            XmlElement gameObjectsElement = prefabElement.CreateElementAndAppend("GameObjects");
            XmlElement gameObjectElement = gameObjectsElement.CreateElementAndAppend("GameObject");
            gameObjectElement.CreateAttributeAndAppend("name", "");
            gameObjectElement.CreateAttributeAndAppend("position", "0,0,0");
            gameObjectElement.CreateElementAndAppend("Components");

            document.Save(FileInfo.FullName);
        }

        #endregion
    }
}