using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace BindingsKernel
{
    public class IntVector4
    {
        #region Properties and Fields

        /// <summary>
        /// The X component of this vector.
        /// </summary>
        public int X { get; set; }

        /// <summary>
        /// The Y component of this vector.
        /// </summary>
        public int Y { get; set; }

        /// <summary>
        /// The Z component of this vector.
        /// </summary>
        public int Z { get; set; }

        /// <summary>
        /// The W component of this vector.
        /// </summary>
        public int W { get; set; }

        #endregion

        #region Constructors

        public IntVector4() : this(0, 0, 0, 0)
        {
            // Needed for deserialization so don't delete
        }

        public IntVector4(int x, int y, int z, int w)
        {
            X = x;
            Y = y;
            Z = z;
            W = w;
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

                    int x = 0;
                    int.TryParse(text.Substring(startIndex, indexOfComma), out x);

                    X = x;
                }

                // Y
                {
                    startIndex = indexOfComma + 1;
                    indexOfComma = text.IndexOf(',', startIndex);

                    int y = 0;
                    int.TryParse(text.Substring(indexOfComma + 1), out y);

                    Y = y;
                }

                // Z
                {
                    startIndex = indexOfComma + 1;
                    indexOfComma = text.IndexOf(',', startIndex);

                    int z = 0;
                    int.TryParse(text.Substring(indexOfComma + 1), out z);

                    Z = z;
                }

                // W
                {
                    startIndex = indexOfComma + 1;
                    indexOfComma = text.IndexOf(',', startIndex);

                    int w = 0;
                    int.TryParse(text.Substring(indexOfComma + 1), out w);

                    W = w;
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
                   .Append(Z)
                   .Append(',')
                   .Append(W);

            writer.WriteAttributeString(name, builder.ToString());
        }

        #endregion
    }
}
