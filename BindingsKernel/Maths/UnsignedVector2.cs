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
    public class UnsignedVector2 : ICustomSerialization, ICustomDeserialization
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

        #endregion

        #region Constructors

        public UnsignedVector2() : this(0, 0)
        {
            // Needed for deserialization so don't delete
        }

        public UnsignedVector2(float x, float y)
        {
            X = x;
            Y = y;
        }

        #endregion

        #region ICustomSerialization Implementation

        public void Deserialize(string name, XmlReader reader)
        {
            string text = reader.GetAttribute(name);
            if (!string.IsNullOrEmpty(text))
            {
                int indexOfComma = text.IndexOf(',');

                float x = 0, y = 0;
                float.TryParse(text.Substring(0, indexOfComma), out x);
                float.TryParse(text.Substring(indexOfComma + 1), out y);

                X = x;
                Y = y;
            }
        }

        public void Serialize(string name, XmlWriter writer)
        {
            StringBuilder builder = new StringBuilder(16);
            builder.Append(X);
            builder.Append(',');
            builder.Append(Y);

            writer.WriteAttributeString(name, builder.ToString());
        }

        #endregion
    }
}