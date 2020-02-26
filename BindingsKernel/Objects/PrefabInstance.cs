using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.Xml.Serialization;

namespace BindingsKernel
{
    public class PrefabInstance : GameObject
    {
        #region Properties and Fields

        public Prefab Prefab { get; }

        #endregion

        public PrefabInstance(Prefab prefab)
        {
            Prefab = prefab;
        }
    }
}
