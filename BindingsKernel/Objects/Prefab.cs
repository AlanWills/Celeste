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
    public class Prefab : IReference
    {
        #region Serialized Properties

        public const string PathXmlAttributeName = "path";

        [Serialize, XmlAttribute(PathXmlAttributeName)]
        public string Path { get; set; }

        #endregion

        #region Properties and Fields

        /// <summary>
        /// Returns the guid of this prefab.
        /// </summary>
        public string UniqueIdentifier { get { return Guid.ToString(); } }

        private Guid Guid { get; set; } = Guid.NewGuid();

        #endregion

        #region Saving and Loading

        public static Prefab Deserialize(XmlReader reader, IEnumerable<Type> componentTypes)
        {
            Prefab prefab = new Prefab();
            prefab.ReadXml(reader, componentTypes);

            return prefab;
        }

        public PrefabInstance Instantiate(IEnumerable<Type> componentTypes)
        {
            using (XmlTextReader reader = new XmlTextReader(Path))
            {
                try
                {
                    PrefabInstance prefabInstance = new PrefabInstance(this);
                    prefabInstance.ReadXml(reader, componentTypes);

                    return prefabInstance;
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
            this.DeserializeProperties(reader);

            reader.ReadStartElement();
            reader.Read();

            if (reader.NodeType == XmlNodeType.EndElement)
            {
                reader.ReadEndElement();
            }
        }

        public void WriteXml(XmlWriter writer)
        {
            throw new NotImplementedException();
        }

        #endregion
    }
}