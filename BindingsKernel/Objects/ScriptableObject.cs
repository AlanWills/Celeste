using BindingsKernel.Objects;
using BindingsKernel.Serialization;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Reflection;
using System.Xml;
using System.Xml.Schema;
using System.Xml.Serialization;

namespace BindingsKernel
{
    public class ScriptableObject : IReference
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

        /// <summary>
        /// The name of this scriptable object.
        /// </summary>
        [Serialize, DisplayName("Name"), XmlAttribute(NameXMLAttributeName), DisplayPriority(0)]
        public string Name { get; set; } = "";

        /// <summary>
        /// The guid of this scriptable object.
        /// </summary>
        [Serialize, DisplayName("Guid"), IsReadOnly, XmlAttribute(GuidXMLAttributeName), DisplayPriority(0)]
        private Guid Guid { get; set; } = Guid.NewGuid();

        #endregion

        #region Properties and Fields

        /// <summary>
        /// Returns the guid of this scriptable object.
        /// </summary>
        public string UniqueIdentifier { get { return Guid.ToString(); } }

        #endregion
    }
}