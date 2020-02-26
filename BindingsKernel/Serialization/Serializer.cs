using BindingsKernel.Objects;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.Xml.Serialization;

namespace BindingsKernel.Serialization
{
    public static class Serializer
    {
        public static void SerializeProperties(this object obj, XmlWriter writer)
        {
            // Otherwise, we fall back on default serialization
            foreach (PropertyInfo property in obj.GetType().GetProperties(BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.SetProperty | BindingFlags.GetProperty))
            {
                // For every instance property with a getter and setter
                // We get the name we should serialize the property as
                if (property.GetCustomAttribute<SerializeAttribute>() != null)
                {
                    XmlAttributeAttribute xmlAttribute = property.GetCustomAttribute<XmlAttributeAttribute>();
                    string serializedName = xmlAttribute != null ? xmlAttribute.AttributeName : property.Name;

                    // Serialize the property value
                    SerializeProperty(obj, writer, serializedName, property.GetValue(obj), property.PropertyType);
                }
            }
        }

        //public void WriteXml(SerializationContext serializationContext)
        //{
        //    XmlWriter writer = serializationContext.Writer;
        //    writer.WriteStartElement(GetType().Name);

        //    if (this is ICustomSerialization)
        //    {
        //        // We have specified custom serialization behaviour for this scriptable object so we perform that here
        //        (this as ICustomSerialization).Serialize(GetType().Name, writer);
        //    }
        //    else
        //    {
        //        // Otherwise, we fall back on default serialization
        //        foreach (PropertyInfo property in GetType().GetProperties(BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.SetProperty | BindingFlags.GetProperty))
        //        {
        //            // For every instance property with a getter and setter
        //            // We get the name we should serialize the property as
        //            XmlAttributeAttribute xmlAttribute = property.GetCustomAttribute<XmlAttributeAttribute>();
        //            string serializedName = xmlAttribute != null ? xmlAttribute.AttributeName : property.Name;

        //            // Check it should be serialized
        //            if (property.GetCustomAttribute<SerializeAttribute>() != null)
        //            {
        //                // Serialize the property value
        //                SerializeObject(serializationContext, serializedName, property.GetValue(this), property.PropertyType);
        //            }
        //        }

        //        foreach (KeyValuePair<string, IList> listPair in serializationContext.ListReferences)
        //        {
        //            // We have a list, so perform another custom serialization step
        //            // Write outer element for list
        //            writer.WriteStartElement(listPair.Key);

        //            IList list = listPair.Value;
        //            if (list != null)
        //            {
        //                foreach (object item in list)
        //                {
        //                    if (item != null)
        //                    {
        //                        writer.WriteStartElement("Element");
        //                        SerializeObject(serializationContext, "uid", item, item.GetType());
        //                        writer.WriteEndElement();
        //                    }
        //                }
        //            }

        //            writer.WriteEndElement();
        //        }
        //    }

        //    writer.WriteEndElement();
        //}

        private static void SerializeProperty(object obj, XmlWriter writer, string serializedName, object value, Type objectType)
        {
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
                // content of ownership, in which case this object will need to serialize all it's children as siblings

                IReference childReference = value as IReference;
                if (childReference != null)
                {
                    // If we have a value set, we write the uid of the asset
                    writer.WriteAttributeString(serializedName, childReference.UniqueIdentifier.ToString());
                }
            }
            else if (objectType.IsGenericType && (objectType.GetGenericTypeDefinition() == typeof(List<>)))
            {
                // We have a list, but have to serialize this after our attributes
                //serializationContext.ListReferences.Add(serializedName, value as IList);
            }
            else
            {
                // Otherwise we have a normal attribute we need to save
                SerializeSimpleType(writer, serializedName, value, objectType);
            }
        }

        private static void SerializeSimpleType(XmlWriter writer, string serializedName, object value, Type objectType)
        {
            if (value != null)
            {
                writer.WriteAttributeString(serializedName, value.ToString());
            }
        }
    }
}
