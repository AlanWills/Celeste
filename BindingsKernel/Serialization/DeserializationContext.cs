using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace BindingsKernel.Serialization
{
    public class DeserializationContext
    {
        #region Properties and Fields

        public Dictionary<string, PropertyInfo> References { get; } = new Dictionary<string, PropertyInfo>();
        public List<Tuple<IList, List<string>>> ListOfReferences { get; } = new List<Tuple<IList, List<string>>>();
        
        #endregion
    }
}
