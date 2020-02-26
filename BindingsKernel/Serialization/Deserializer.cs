using BindingsKernel.Objects;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.Xml.Serialization;

namespace BindingsKernel.Serialization
{
    public static class Deserializer
    {
        public static void DeserializeProperties(this object obj, XmlReader reader)
        {
            foreach (PropertyInfo property in obj.GetType().GetProperties(BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.SetProperty | BindingFlags.GetProperty))
            {
                // For every instance property with a getter and setter
                // We get the name we should deserialize the property as
                if (property.GetCustomAttribute<SerializeAttribute>() != null)
                {
                    XmlAttributeAttribute xmlAttribute = property.GetCustomAttribute<XmlAttributeAttribute>();
                    string serializedName = xmlAttribute != null ? xmlAttribute.AttributeName : property.Name;

                    DeserializeProperty(obj, reader, serializedName, property);
                }
            }
        }

        //public void Deserialize()
        //{
        //    if (this is ICustomDeserialization)
        //    {
        //        // We have specified custom deserialization behaviour for this scriptable object so we perform that here
        //        (this as ICustomDeserialization).Deserialize(GetType().Name, reader);
        //    }
        //    else
        //    {
        //        foreach (PropertyInfo property in GetType().GetProperties(BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.SetProperty | BindingFlags.GetProperty))
        //        {
        //            // For every instance property with a getter and setter
        //            // We get the name we should deserialize the property as
        //            XmlAttributeAttribute xmlAttribute = property.GetCustomAttribute<XmlAttributeAttribute>();
        //            string serializedName = xmlAttribute != null ? xmlAttribute.AttributeName : property.Name;

        //            // Check it should be deserialized
        //            if (property.GetCustomAttribute<SerializeAttribute>() != null)
        //            {
        //                DeserializeObject(deserializationContext, serializedName, property);
        //            }
        //        }

        //        // Use this when we start thinking about ownership of SOs, but for now they should all be project assets

        //        //int thisObjectDepth = deserializationContext.Reader.Depth;

        //        //// Now, we go through all the children, and use name to find the object's guid
        //        //deserializationContext.Reader.Read();
        //        //while (deserializationContext.Reader.IsStartElement() && (deserializationContext.Reader.Depth > thisObjectDepth))
        //        //{
        //        //    // Cache this value here as the ReadElementContentAsString method will advance the reader onwards
        //        //    string elementName = deserializationContext.Reader.LocalName;
        //        //    if (nameToPropertyLookup.ContainsKey(elementName))
        //        //    {
        //        //        // We have a scriptable object reference which needs hooking up later
        //        //        string guidString = deserializationContext.Reader.ReadElementContentAsString();
        //        //        deserializationContext.AddScriptableObjectReference(new Guid(guidString), nameToPropertyLookup[elementName]);
        //        //    }
        //        //    else if (nameToListLookup.ContainsKey(elementName))
        //        //    {
        //        //        // We have a list of objects which we need to deserialize
        //        //        deserializationContext.Reader.Read();
        //        //        string elementName2 = deserializationContext.Reader.LocalName;
        //        //    }
        //        //}
        //    }
        //}

        private static void DeserializeProperty(object obj, XmlReader reader, string serializedName, PropertyInfo property)
        {
            Type customDeserialization = typeof(ICustomDeserialization);
            Type reference = typeof(IReference);

            object value = property.GetValue(obj);

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
                    //deserializationContext.References.Add(guid, property);
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
                        //deserializationContext.ListOfReferences.Add(new Tuple<IList, List<string>>(list, guids));
                    }
                }

                // Set this list property to the newly created list
                property.SetValue(obj, list);
            }
            else
            {
                // Otherwise we have a normal attribute which we must deserialize
                property.SetValue(obj, DeserializeSimpleType(reader, serializedName, property.PropertyType));
            }
        }

        private static object DeserializeSimpleType(XmlReader reader, string name, Type type)
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

            return null;
        }
    }
}
