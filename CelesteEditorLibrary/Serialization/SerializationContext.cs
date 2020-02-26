using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEngineEditor.Serialization
{
    public class SerializationContext
    {
        #region Properties and Fields

        protected Dictionary<string, PropertyInfo> ScriptableObjectReferences { get; private set; } = new Dictionary<string, PropertyInfo>();

        protected Dictionary<string, PropertyInfo> ScriptableObjectListReferences { get; private set; } = new Dictionary<string, PropertyInfo>();

        #endregion
    }
}
