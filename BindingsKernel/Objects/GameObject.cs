using BindingsKernel.Serialization;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Xml;
using System.Xml.Schema;
using System.Xml.Serialization;

namespace BindingsKernel
{
    public class GameObject : Entity
    {
        #region Serialized Properties

        [Serialize, XmlAttribute("name")]
        public string Name { get; set; }

        #region Transform Information

        [Serialize]
        public Vector3 Translation { get; set; }

        [Serialize]
        public float Rotation { get; set; }

        [Serialize]
        public Vector3 Scale { get; set; }

        [Serialize]
        public Vector3 WorldTranslation { get; set; }

        [Serialize]
        public float WorldRotation { get; set; }

        [Serialize]
        public Vector3 WorldScale { get; set; }

        #endregion

        #endregion

        #region Properties and Fields

        public List<GameObject> ChildGameObjects { get; } = new List<GameObject>();

        public List<Component> Components { get; } = new List<Component>();

        #endregion

        #region Constructor

        public GameObject()
        {
        }

        public GameObject(string name)
        {
            Name = name;
        }

        #endregion

        #region Saving and Loading

        public static GameObject Deserialize(XmlReader reader, IEnumerable<Type> componentTypes)
        {
            // ...Deserialize GameObject Attributes...
            GameObject gameObject = new GameObject();
            gameObject.ReadXml(reader, componentTypes);

            return gameObject;
        }

        #endregion

        #region IXmlSerializable Implementation

        public XmlSchema GetSchema()
        {
            return null;
        }

        public void ReadXml(XmlReader reader, IEnumerable<Type> componentTypes)
        {
            // Load the properties into the game object
            this.DeserializeProperties(reader);

            int gameObjectDepth = reader.Depth;

            // Read GameObject Element
            reader.ReadStartElement();
            reader.Read();

            // Check for Components Element
            while (gameObjectDepth < reader.Depth)
            {
                if (reader.Name == "Components")
                {
                    int componentsDepth = reader.Depth;
                    reader.ReadStartElement();
                    reader.Read();

                    // Check for Component Element
                    while (componentsDepth < reader.Depth)
                    {
                        Type type = componentTypes.FirstOrDefault(x => x.Name == reader.Name);
                        if (type != null)
                        {
                            Component component = Activator.CreateInstance(type) as Component;
                            Components.Add(component);
                            
                            // ...Deserialize Component Attributes...
                        }

                        int componentDepth = reader.Depth;
                        reader.ReadStartElement();
                        reader.Read();  // Also, maybe only do this if it's not an EmptyElement?  Generally, need to check for that

                        if (componentDepth < reader.Depth)
                        {
                            // ...Deserialize Component Children...
                            while (componentDepth < reader.Depth)
                            {
                                reader.Read();
                            }

                            if (!reader.IsEmptyElement)
                            {
                                reader.ReadEndElement();
                                reader.MoveToContent();
                            }
                        }
                    }

                    if (!reader.IsEmptyElement)
                    {
                        reader.ReadEndElement();
                        reader.MoveToContent();
                    }
                }
                else if (reader.Name == "GameObjects")
                {
                    Dictionary<string, Prefab> prefabLookup = new Dictionary<string, Prefab>();

                    int gameObjectsDepth = reader.Depth;

                    // Read GameObjects Element
                    reader.ReadStartElement();

                    // Check for GameObject Element
                    while (gameObjectsDepth < reader.Depth)
                    {
                        reader.MoveToContent();

                        GameObject gameObject = null;

                        if (reader.Name == "GameObject")
                        {
                            gameObject = Deserialize(reader, componentTypes);
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
                        else
                        {
                            CelDebug.Fail();
                        }

                        CelDebug.AssertNotNull(gameObject);
                        ChildGameObjects.Add(gameObject);
                    }

                    if (!reader.IsEmptyElement)
                    {
                        reader.ReadEndElement();
                    }
                }

                reader.MoveToContent();
            }

            if (!reader.IsEmptyElement)
            {
                reader.ReadEndElement();
                reader.MoveToContent();
            }
        }

        public void WriteXml(XmlWriter writer)
        {
            writer.WriteStartElement("GameObject");
            writer.WriteAttributeString("name", Name);

            if (ChildGameObjects.Count > 0)
            {
                writer.WriteStartElement("Components");

                foreach (Component component in Components)
                {
                    writer.WriteStartElement(component.GetType().Name);

                    writer.WriteEndElement();
                }

                writer.WriteEndElement();

                writer.WriteStartElement("GameObjects");

                foreach (GameObject gameObject in ChildGameObjects)
                {
                    gameObject.WriteXml(writer);
                }

                writer.WriteEndElement();
            }

            writer.WriteEndElement();
        }

        #endregion
    }
}