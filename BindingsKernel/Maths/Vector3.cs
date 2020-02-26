using BindingsKernel.Serialization;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace BindingsKernel
{
    public class Vector3 : ICustomSerialization, ICustomDeserialization
    {
        #region Properties and Fields

        /// <summary>
        /// The X component of this vector.
        /// </summary>
        public float X { get; set; }

        /// <summary>
        /// The Y component of this vector
        /// </summary>
        public float Y { get; set; }

        /// <summary>
        /// The Z component of this vector
        /// </summary>
        public float Z { get; set; }

        #endregion

        #region Constructors

        public Vector3() : this(0, 0, 0)
        {
            // Needed for deserialization so don't delete
        }

        public Vector3(float x, float y, float z)
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
                int indexOfFirstComma = text.IndexOf(',');
                int indexOfSecondComma = text.IndexOf(',', indexOfFirstComma + 1);

                float x = 0, y = 0, z = 0;
                float.TryParse(text.Substring(0, indexOfFirstComma), out x);
                float.TryParse(text.Substring(indexOfFirstComma + 1, indexOfSecondComma - indexOfFirstComma), out y);
                float.TryParse(text.Substring(indexOfSecondComma + 1), out z);

                X = x;
                Y = y;
                Z = z;
            }
        }

        public void Serialize(string name, XmlWriter writer)
        {
            StringBuilder builder = new StringBuilder(32);
            builder.Append(X);
            builder.Append(',');
            builder.Append(Y);
            builder.Append(',');
            builder.Append(Z);

            writer.WriteAttributeString(name, builder.ToString());
        }

        #endregion
    }
}
