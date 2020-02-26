using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace BindingsKernel.Serialization
{
    public interface ICustomDeserialization
    {
        void Deserialize(string name, XmlReader reader);
    }
}
