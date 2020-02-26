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
    public class UnsignedVector4 : ICustomSerialization, ICustomDeserialization
    {
        #region Properties and Fields

        private float x = 0;
        /// <summary>
        /// The X component of this vector.
        /// </summary>
        public float X
        {
            get { return x; }
            set { x = value.Clamp(0, float.MaxValue); }
        }

        private float y = 0;
        /// <summary>
        /// The Y component of this vector.
        /// </summary>
        public float Y
        {
            get { return y; }
            set { y = value.Clamp(0, float.MaxValue); }
        }

        private float z = 0;
        /// <summary>
        /// The Z component of this vector.
        /// </summary>
        public float Z
        {
            get { return z; }
            set { z = value.Clamp(0, float.MaxValue); }
        }

        private float w = 0;
        /// <summary>
        /// The Z component of this vector.
        /// </summary>
        public float W
        {
            get { return w; }
            set { w = value.Clamp(0, float.MaxValue); }
        }

        #endregion

        #region Constructors

        public UnsignedVector4() : this(0, 0, 0, 0)
        {
            // Needed for deserialization so don't delete
        }

        public UnsignedVector4(float x, float y, float z, float w)
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

                    float x = 0;
                    float.TryParse(text.Substring(startIndex, indexOfComma), out x);

                    X = x;
                }

                // Y
                {
                    startIndex = indexOfComma + 1;
                    indexOfComma = text.IndexOf(',', startIndex);

                    float y = 0;
                    float.TryParse(text.Substring(indexOfComma + 1), out y);

                    Y = y;
                }

                // Z
                {
                    startIndex = indexOfComma + 1;
                    indexOfComma = text.IndexOf(',', startIndex);

                    float z = 0;
                    float.TryParse(text.Substring(indexOfComma + 1), out z);

                    Z = z;
                }

                // W
                {
                    startIndex = indexOfComma + 1;
                    indexOfComma = text.IndexOf(',', startIndex);

                    float w = 0;
                    float.TryParse(text.Substring(indexOfComma + 1), out w);

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