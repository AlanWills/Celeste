using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace CelesteEditor
{
    /// <summary>
    ///  Provides utility functions for handling XmlElements and XmlDocuments
    /// </summary>
    public static class XmlExtensions
    {
        /// <summary>
        /// Attempts to load the file with the inputted path into this XmlDocument.
        /// Returns true and populates the document if this process was a success.
        /// Returns false if this process was a failure.
        /// </summary>
        /// <param name="document"></param>
        /// <param name="filePath"></param>
        /// <returns></returns>
        public static bool TryLoad(this XmlDocument document, string filePath)
        {
            if (document == null)
            {
                return false;
            }
 
            if (!File.Exists(filePath))
            {
                return false;
            }
 
            try
            {
                document.Load(filePath);
                return true;
            }
            catch
            {
                return false;
            }
        }

        /// <summary>
        /// Attempts to find a child element underneath the inputted element with the inputted tag name.
        /// If more than one is found, the first is returned.
        /// If none are found, null is returned.
        /// </summary>
        /// <param name="element"></param>
        /// <param name="elementTagName"></param>
        /// <returns></returns>
        public static XmlElement FirstChildOrNull(this XmlElement element, string elementTagName)
        {
            XmlNodeList elements = element.GetElementsByTagName(elementTagName);
            if (elements != null && elements.Count > 0)
            {
                return elements[0] as XmlElement;
            }

            return null;
        }

        #region CreateElementAndAppend Functions

        /// <summary>
        /// Creates an element with the inputted tag name and value and appends it to the document.
        /// </summary>
        /// <param name="document"></param>
        /// <param name="elementTagName"></param>
        /// <param name="elementValue"></param>
        /// <returns></returns>
        public static XmlElement CreateElementAndAppend(this XmlDocument document, string elementTagName, string innerText = "")
        {
            XmlElement element = document.CreateElement(elementTagName);
            element.InnerText = innerText;
            document.AppendChild(element);

            return element;
        }

        /// <summary>
        /// Creates an element with the inputted tag name and text and appends it to the inputted parent xml element.
        /// </summary>
        /// <param name="document"></param>
        /// <param name="parent"></param>
        /// <param name="elementTagName"></param>
        /// <param name="elementValue"></param>
        /// <returns></returns>
        public static XmlElement CreateElementAndAppend(this XmlElement parent, string elementTagName, string innerText = "")
        {
            XmlElement element = parent.OwnerDocument.CreateElement(elementTagName);
            element.InnerText = innerText;
            parent.AppendChild(element);

            return element;
        }

        #endregion

        #region Create CDataSectionAndAppend Functions
        
        /// <summary>
        /// Creates an element with the inputted tag name and text and appends it to the inputted parent xml element.
        /// </summary>
        /// <param name="document"></param>
        /// <param name="parent"></param>
        /// <param name="elementTagName"></param>
        /// <param name="elementValue"></param>
        /// <returns></returns>
        public static XmlCDataSection CreateCDataSectionAndAppend(this XmlElement parent, string data)
        {
            XmlCDataSection dataSection = parent.OwnerDocument.CreateCDataSection(data);
            parent.AppendChild(dataSection);

            return dataSection;
        }

        #endregion

        #region CreateAttributeAndAppend Functions

        /// <summary>
        /// Creates an attribute with the inputted name and value and appends it to the inputted parent element.
        /// </summary>
        /// <param name="document"></param>
        /// <param name="attributeName"></param>
        /// <param name="attributeValue"></param>
        /// <returns></returns>
        public static XmlAttribute CreateAttributeAndAppend(this XmlElement parent, string attributeName, string attributeValue)
        {
            XmlAttribute attribute = parent.OwnerDocument.CreateAttribute(attributeName);
            attribute.Value = attributeValue;
            parent?.Attributes.Append(attribute);

            return attribute;
        }

        #endregion
    }
}
