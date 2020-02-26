using BindingsKernel.Objects;
using BindingsKernel.Serialization;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.Xml.Schema;
using System.Xml.Serialization;

namespace BindingsKernel
{
    public class Screen : Entity, IReference
    {
        #region Serialized Properties

        /// <summary>
        /// The name of the attribute containing the information about the object's name.
        /// </summary>
        private const string NameXMLAttributeName = "name";

        /// <summary>
        /// The name of the attribute containing the informatino about the object's guid.
        /// </summary>
        private const string GuidXMLAttributeName = "guid";

        [Serialize, XmlAttribute(NameXMLAttributeName)]
        public string Name { get; set; } = "";

        [Serialize, XmlAttribute(GuidXMLAttributeName)]
        private Guid Guid { get; set; } = Guid.NewGuid();

        #endregion

        #region Properties and Fields

        /// <summary>
        /// Returns the guid of this screen.
        /// </summary>
        public string UniqueIdentifier { get { return Guid.ToString(); } }

        public List<GameObject> GameObjects { get; } = new List<GameObject>();

        #endregion

        #region Constructors

        public Screen()
        {
        }

        public Screen(string name)
        {
            Name = name;
        }

        #endregion

        #region Saving and Loading

        public static Screen Load(FileInfo file, IEnumerable<Type> componentTypes)
        {
            return Load(file.FullName, componentTypes);
        }

        public static Screen Load(string filePath, IEnumerable<Type> componentTypes)
        {
            using (XmlTextReader reader = new XmlTextReader(filePath))
            {
                try
                {
                    Screen screen = new Screen();
                    screen.ReadXml(reader, componentTypes);
                    return screen;
                }
                catch (Exception e)
                {
                    CelDebug.Fail(e.Message);
                    return null;
                }
            }
        }

        #endregion

        #region IXmlSerializable Implementation

        public XmlSchema GetSchema()
        {
            return null;
        }

        public void ReadXml(XmlReader reader, IEnumerable<Type> componentTypes)
        {
            reader.Read();
            reader.Read();
            reader.Read();

            Dictionary<string, Prefab> prefabLookup = new Dictionary<string, Prefab>();

            Name = reader.GetAttribute(NameXMLAttributeName);
            Guid = Guid.Parse(reader.GetAttribute(GuidXMLAttributeName));

            // Read Screen Element
            reader.ReadStartElement();

            while (reader.IsStartElement())
            {
                if (reader.Name == "Resources")
                {
                    // TODO HANDLE READING RESOURCES
                    reader.ReadToNextSibling("GameObjects");
                    //reader.ReadStartElement();
                }
                else if (reader.Name == "GameObjects")
                {
                    // Read GameObjects Element
                    reader.ReadStartElement();

                    // Check for GameObject Element
                    while (reader.IsStartElement())
                    {
                        GameObject gameObject = null;

                        if (reader.Name == "GameObject")
                        {
                            gameObject = GameObject.Deserialize(reader, componentTypes);
                        }
                        else if (reader.Name == "Prefab")
                        {
                            string path = reader.GetAttribute(Prefab.PathXmlAttributeName);
                            if (!string.IsNullOrEmpty(path))
                            {
                                Prefab prefab;

                                if (prefabLookup.ContainsKey(path))
                                {
                                    prefab = prefabLookup[path];
                                }
                                else
                                {
                                    prefab = Prefab.Deserialize(reader, componentTypes);
                                    prefabLookup.Add(prefab.Path, prefab);
                                }

                                // Re-enable this and remove current uncommented code when
                                // prefab instance deserialization has been resolved
                                //prefab.Instantiate();
                                gameObject = new PrefabInstance(prefab);
                                gameObject.Name = "PREFAB " + Guid.NewGuid().ToString();
                            }
                        }

                        CelDebug.AssertNotNull(gameObject);
                        GameObjects.Add(gameObject);
                    }
                }
            }
        }

        public void WriteXml(XmlWriter writer)
        {
            writer.WriteAttributeString(NameXMLAttributeName, Name);
            writer.WriteAttributeString(GuidXMLAttributeName, Guid.ToString());

            writer.WriteStartElement("GameObjects");

            foreach (GameObject gameObject in GameObjects)
            {
                gameObject.WriteXml(writer);
            }

            writer.WriteEndElement();
        }

        #endregion
    }
}