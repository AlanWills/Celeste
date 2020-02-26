using BindingsKernel;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Serialization;
using System.Xml.Schema;
using System.Reflection;
using CelesteEngineEditor.Extensibility;
using BindingsKernel.Serialization;
using System.Collections;
using CelesteEngineEditor.Core;
using BindingsKernel.Objects;
using DynamicData;

namespace CelesteEngineEditor.Assets
{
    public class ScriptableObjectAsset : Asset<ScriptableObject>
    {
        #region Properties and Fields

        private DeserializationContext DeserializationContext { get; set; }

        #endregion

        public ScriptableObjectAsset(
            FileInfo fileInfo,
            ScriptableObject scriptableObject) :
            base(fileInfo, scriptableObject)
        {
        }

        #region Abstract Overrides

        public void ReadXml(XmlReader reader)
        {
            DeserializationContext = new DeserializationContext();

            if (AssetObject is ICustomDeserialization)
            {
                // We have specified custom deserialization behaviour for this scriptable object so we perform that here
                (AssetObject as ICustomDeserialization).Deserialize(GetType().Name, reader);
            }
            else
            {
                foreach (PropertyInfo property in AssetObject.GetType().GetProperties(BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.SetProperty | BindingFlags.GetProperty))
                {
                    // For every instance property with a getter and setter
                    // We get the name we should deserialize the property as
                    XmlAttributeAttribute xmlAttribute = property.GetCustomAttribute<XmlAttributeAttribute>();
                    string serializedName = xmlAttribute != null ? xmlAttribute.AttributeName : property.Name;

                    // Check it should be deserialized
                    if (property.GetCustomAttribute<SerializeAttribute>() != null)
                    {
                        DeserializeObject(reader, DeserializationContext, serializedName, property);
                    }
                }

                // Use this when we start thinking about ownership of SOs, but for now they should all be project assets

                //int thisObjectDepth = deserializationContext.Reader.Depth;

                //// Now, we go through all the children, and use name to find the object's guid
                //deserializationContext.Reader.Read();
                //while (deserializationContext.Reader.IsStartElement() && (deserializationContext.Reader.Depth > thisObjectDepth))
                //{
                //    // Cache this value here as the ReadElementContentAsString method will advance the reader onwards
                //    string elementName = deserializationContext.Reader.LocalName;
                //    if (nameToPropertyLookup.ContainsKey(elementName))
                //    {
                //        // We have a scriptable object reference which needs hooking up later
                //        string guidString = deserializationContext.Reader.ReadElementContentAsString();
                //        deserializationContext.AddScriptableObjectReference(new Guid(guidString), nameToPropertyLookup[elementName]);
                //    }
                //    else if (nameToListLookup.ContainsKey(elementName))
                //    {
                //        // We have a list of objects which we need to deserialize
                //        deserializationContext.Reader.Read();
                //        string elementName2 = deserializationContext.Reader.LocalName;
                //    }
                //}
            }
        }

        private void DeserializeObject(XmlReader reader, DeserializationContext deserializationContext, string serializedName, PropertyInfo property)
        {
            Type customDeserialization = typeof(ICustomDeserialization);
            Type reference = typeof(IReference);

            object value = property.GetValue(AssetObject);

            // This property should be deserialized
            if (customDeserialization.IsAssignableFrom(property.PropertyType))
            {
                // We have dictated custom serialization behaviour for this propery so we perform that here
                if (value != null)
                {
                    // If we actually have a value set for this propery, we call through to the custom serialization here
                    (value as ICustomDeserialization).Deserialize(serializedName, reader);
                }
            }
            else if (reference.IsAssignableFrom(property.PropertyType))
            {
                // We have a reference property, so we add it's guid and property to our lookup of references that need resolving
                string guid = reader.GetAttribute(serializedName);
                if (!string.IsNullOrEmpty(guid))
                {
                    deserializationContext.References.Add(guid, property);
                }
            }
            else if (property.PropertyType.IsGenericType && (property.PropertyType.GetGenericTypeDefinition() == typeof(List<>)))
            {
                // We have a list, so add it for creation later
                IList list = Activator.CreateInstance(property.PropertyType) as IList;
                Type typeArgument = property.PropertyType.GenericTypeArguments[0];
                List<string> guids = new List<string>();

                int thisObjectDepth = reader.Depth;

                //reader.MoveToContent();
                reader.ReadStartElement();

                // Now, we go through all the children, and deserialize all the list elements
                while (reader.IsStartElement() && (reader.Depth > thisObjectDepth))
                {
                    reader.ReadStartElement();
                    reader.MoveToContent();

                    if (customDeserialization.IsAssignableFrom(typeArgument))
                    {
                        // We have a list of custom deserialized objects, so we create an instance and deserialize it
                        ICustomDeserialization element = Activator.CreateInstance(typeArgument) as ICustomDeserialization;
                        element.Deserialize(typeArgument.Name, reader);
                        list.Add(element);
                    }
                    else if (reference.IsAssignableFrom(typeArgument))
                    {
                        // We have a list of scriptable objects, so we add a reference for later to allow us to fix up references
                        string uid = reader.GetAttribute("uid");
                        if (!string.IsNullOrEmpty(uid))
                        {
                            guids.Add(uid);
                        }
                    }
                    else if (property.PropertyType.IsGenericType && (property.PropertyType.GetGenericTypeDefinition() == typeof(List<>)))
                    {
                        // Currently don't support nested list deserialization
                    }
                    else
                    {
                        // We have a simple type which we need to deserialize
                        list.Add(DeserializeSimpleType(reader, serializedName, property.PropertyType));
                    }

                    reader.Read();
                    reader.MoveToContent();
                }

                reader.ReadEndElement();

                if (reference.IsAssignableFrom(typeArgument))
                {
                    // This was a list of scriptable objects, so we need to add a reference
                    if (guids.Count > 0)
                    {
                        deserializationContext.ListOfReferences.Add(new Tuple<IList, List<string>>(list, guids));
                    }
                }

                // Set this list property to the newly created list
                property.SetValue(AssetObject, list);
            }
            else
            {
                // Otherwise we have a normal attribute which we must deserialize
                property.SetValue(AssetObject, DeserializeSimpleType(reader, serializedName, property.PropertyType));
            }
        }

        private object DeserializeSimpleType(XmlReader reader, string name, Type type)
        {
            if (type == typeof(string))
            {
                return reader.GetAttribute(name);
            }
            else if (type == typeof(float))
            {
                if (float.TryParse(reader.GetAttribute(name), out float f))
                {
                    return f;
                }

                return default(float);
            }
            else if (type == typeof(int))
            {
                if (int.TryParse(reader.GetAttribute(name), out int i))
                {
                    return i;
                }

                return default(int);
            }
            else if (type == typeof(bool))
            {
                if (bool.TryParse(reader.GetAttribute(name), out bool b))
                {
                    return b;
                }

                return default(bool);
            }
            else if (type == typeof(Guid))
            {
                if (Guid.TryParse(reader.GetAttribute(name), out Guid g))
                {
                    return g;
                }

                return Guid.Empty;
            }
            else if (type.IsEnum)
            {
                return Enum.Parse(type, reader.GetAttribute(name), false);
            }

            return null;
        }

        public override void Save()
        {
            if (AssetObject == null)
            {
                // Remove this - it should never be null
                return;
            }

            using (XmlTextWriter writer = new XmlTextWriter(FileInfo.FullName, Encoding.UTF8))
            {
                writer.Formatting = Formatting.Indented;
                writer.WriteStartDocument();

                try
                {
                    WriteXml(new SerializationContext(writer));
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

        public void WriteXml(SerializationContext serializationContext)
        {
            XmlWriter writer = serializationContext.Writer;
            writer.WriteStartElement(AssetObject.GetType().Name);

            if (AssetObject is ICustomSerialization)
            {
                // We have specified custom serialization behaviour for this scriptable object so we perform that here
                (AssetObject as ICustomSerialization).Serialize(GetType().Name, writer);
            }
            else
            {
                // Otherwise, we fall back on default serialization
                foreach (PropertyInfo property in AssetObject.GetType().GetProperties(BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.SetProperty | BindingFlags.GetProperty))
                {
                    // For every instance property with a getter and setter
                    // We get the name we should serialize the property as
                    XmlAttributeAttribute xmlAttribute = property.GetCustomAttribute<XmlAttributeAttribute>();
                    string serializedName = xmlAttribute != null ? xmlAttribute.AttributeName : property.Name;

                    // Check it should be serialized
                    if (property.GetCustomAttribute<SerializeAttribute>() != null)
                    {
                        // Serialize the property value
                        SerializeObject(serializationContext, serializedName, property.GetValue(AssetObject), property.PropertyType);
                    }
                }

                foreach (KeyValuePair<string, IList> listPair in serializationContext.ListReferences)
                {
                    // We have a list, so perform another custom serialization step
                    // Write outer element for list
                    writer.WriteStartElement(listPair.Key);

                    IList list = listPair.Value;
                    if (list != null)
                    {
                        foreach (object item in list)
                        {
                            if (item != null)
                            {
                                writer.WriteStartElement("Element");
                                SerializeObject(serializationContext, "uid", item, item.GetType());
                                writer.WriteEndElement();
                            }
                        }
                    }

                    writer.WriteEndElement();
                }
            }

            writer.WriteEndElement();
        }

        private void SerializeObject(SerializationContext serializationContext, string serializedName, object value, Type objectType)
        {
            XmlWriter writer = serializationContext.Writer;
            Type customSerialization = typeof(ICustomSerialization);
            Type reference = typeof(IReference);

            if (customSerialization.IsAssignableFrom(objectType))
            {
                // We have dictated custom serialization behaviour for this propery so we perform that here
                if (value != null)
                {
                    // If we actually have a value set for this propery, we call through to the custom serialization here
                    (value as ICustomSerialization).Serialize(serializedName, writer);
                }
            }
            else if (reference.IsAssignableFrom(objectType))
            {
                // We have a reference so we perform a custom serialization step here
                // We write it's uid, so that when we deserialize we can look to set up references when all assets have been loaded
                // This currently assumes that all assets are project assets - later on this will need to be expanded to understand the
                // concept of ownership, in which case this object will need to serialize all it's children as siblings

                IReference childReference = value as IReference;
                if (childReference != null)
                {
                    IAsset asset = Project.Current.ProjectAssets.First(x => x.AssetObjectInternal == childReference);

                    // If we have a value set, we write the uid of the asset
                    writer.WriteAttributeString(serializedName, asset.FileInfo.FullName.Remove(0, Project.Current.ProjectDirectory.FullName.Length));
                }
            }
            else if (objectType.IsGenericType && (objectType.GetGenericTypeDefinition() == typeof(List<>)))
            {
                // We have a list, but have to serialize this after our attributes
                serializationContext.ListReferences.Add(serializedName, value as IList);
            }
            else
            {
                // Otherwise we have a normal attribute we need to save
                SerializeSimpleType(serializationContext, serializedName, value, objectType);
            }
        }

        private void SerializeSimpleType(SerializationContext serializationContext, string serializedName, object value, Type objectType)
        {
            if (value != null)
            {
                serializationContext.Writer.WriteAttributeString(serializedName, value.ToString());
            }
        }

        #endregion

        #region Utility Functions

        public void ResolveReferences(Dictionary<string, IReference> referenceLookup)
        {
            if (DeserializationContext != null)
            {
                foreach (KeyValuePair<string, PropertyInfo> referenceProperty in DeserializationContext.References)
                {
                    // Resolve all single property references
                    if (referenceLookup.ContainsKey(referenceProperty.Key))
                    {
                        referenceProperty.Value.SetValue(AssetObject, referenceLookup[referenceProperty.Key]);
                    }
                }

                foreach (Tuple<IList, List<string>> listOfReferencesProperty in DeserializationContext.ListOfReferences)
                {
                    // Resolve all list references
                    foreach (string soGuid in listOfReferencesProperty.Item2)
                    {
                        if (referenceLookup.ContainsKey(soGuid))
                        {
                            listOfReferencesProperty.Item1.Add(referenceLookup[soGuid]);
                        }
                    }
                }

                DeserializationContext.References.Clear();
                DeserializationContext.ListOfReferences.Clear();
            }
        }

        #endregion
    }
}
