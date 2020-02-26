using BindingsKernel.Objects;
using BindingsKernel.Serialization;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace BindingsKernel
{
    public class Texture2D : IReference
    {
        #region Properties and Fields

        public string UniqueIdentifier { get; set; }

        #endregion
        
        #region Equality Overrides

        // NEED TO GENERALISE THIS FOR ALL REFERENCES
        // MAYBE TURN INTERFACE INTO BASE CLASS

        /// <summary>
        /// Override equality to perform checking on texture path.
        /// Because paths are unique this is a valid form of equality and is useful for avoiding referencing issues.
        /// Must override this function rather than operator because it is used by WPF UI.
        /// </summary>
        /// <param name="obj"></param>
        /// <returns></returns>
        public override bool Equals(object obj)
        {
            return (obj is Texture2D) ? UniqueIdentifier == (obj as Texture2D).UniqueIdentifier : base.Equals(obj);
        }

        public override int GetHashCode()
        {
            return UniqueIdentifier.GetHashCode();
        }

        #endregion
    }
}