using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace BindingsKernel.Serialization
{
    public class SerializationContext
    {
        #region Properties and Fields

        public XmlWriter Writer { get; private set; }

        public Dictionary<string, IList> ListReferences { get; private set; } = new Dictionary<string, IList>();

        #endregion

        public SerializationContext(XmlWriter writer)
        {
            Writer = writer;
        }
    }
}
