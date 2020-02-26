using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace BindingsKernel.Serialization
{
    public interface ICustomSerialization
    {
        void Serialize(string name, XmlWriter writer);
    }
}
