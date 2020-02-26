using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BindingsKernel
{
    public class XmlChildElementNameAttribute : Attribute
    {
        #region Properties and Fields

        public string XmlChildElementName { get; set; }

        #endregion

        public XmlChildElementNameAttribute(string xmlChildElementName)
        {
            XmlChildElementName = xmlChildElementName;
        }
    }
}
