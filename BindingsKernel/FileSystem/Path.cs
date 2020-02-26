using BindingsKernel.Serialization;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.Xml.Schema;
using System.Xml.Serialization;

namespace BindingsKernel
{
    public class Path : ICustomDeserialization
    {
        #region Properties and Fields
        
        public string FullPath { get; set; }

        #endregion

        #region Constructors

        public Path() : this("")
        {
            // Need parameterless constructor for deserialization so don't delete
        }

        public Path(string fullPath = "")
        {
            FullPath = fullPath;
        }
        
        #endregion

        #region ICustomSerialization

        public void Deserialize(string name, XmlReader reader)
        {
            FullPath = reader.GetAttribute(name);
        }
        
        #endregion

        public override string ToString()
        {
            return FullPath;
        }
    }
}
