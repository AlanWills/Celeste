using BindingsKernel.Serialization;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace BindingsKernel
{
    [Serializable]
    public class UnsignedIntVector3 : ICustomSerialization, ICustomDeserialization
    {
        #region Properties and Fields

        /// <summary>
        /// The X component of this vector.
        /// </summary>
        public uint X { get; set; }

        /// <summary>
        /// The Y component of this vector.
        /// </summary>
        public uint Y { get; set; }

        /// <summary>
        /// The Z component of this vector.
        /// </summary>
        public uint Z { get; set; }

        #endregion

        #region Constructors

        public UnsignedIntVector3() : this(0, 0, 0)
        {
            // Needed for deserialization so don't delete
        }

        public UnsignedIntVector3(uint x, uint y, uint z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        #endregion

        #region ICustomSerialization Implementation

        public void Deserialize(string name, XmlReader reader)
        {
            string text = reader.GetAttribute(name);
            if (!string.IsNullOrEmpty(text))
            {
                int startIndex = 0;
                int indexOfComma = 0;

                // X
                {
                    startIndex = 0;
                    indexOfComma = text.IndexOf(',', startIndex);

                    uint x = 0;
                    uint.TryParse(text.Substring(startIndex, indexOfComma), out x);

                    X = x;
                }

                // Y
                {
                    startIndex = indexOfComma + 1;
                    indexOfComma = text.IndexOf(',', startIndex);

                    uint y = 0;
                    uint.TryParse(text.Substring(indexOfComma + 1), out y);

                    Y = y;
                }

                // Z
                {
                    startIndex = indexOfComma + 1;
                    indexOfComma = text.IndexOf(',', startIndex);

                    uint z = 0;
                    uint.TryParse(text.Substring(indexOfComma + 1), out z);

                    Z = z;
                }
            }
        }

        public void Serialize(string name, XmlWriter writer)
        {
            StringBuilder builder = new StringBuilder(16);
            builder.Append(X)
                   .Append(',')
                   .Append(Y)
                   .Append(',')
                   .Append(Z);

            writer.WriteAttributeString(name, builder.ToString());
        }

        #endregion
    }
}