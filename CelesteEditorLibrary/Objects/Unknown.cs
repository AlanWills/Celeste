using BindingsKernel.Objects;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEditor.Objects
{
    public class Unknown : IReference
    {
        #region Properties and Fields

        public string UniqueIdentifier { get; } = Guid.NewGuid().ToString();

        /// <summary>
        /// The object that was loaded, but we could not process into an available project asset.
        /// </summary>
        public object Object { get; private set; }

        #endregion

        public Unknown(object unknownObject)
        {
            // Might need parameterless constructor in which case we may need to re-think this.
            Object = unknownObject;
        }
    }
}
