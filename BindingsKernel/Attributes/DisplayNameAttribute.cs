using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BindingsKernel
{
    public class DisplayNameAttribute : Attribute
    {
        #region Properties and Fields

        public string DisplayName { get; set; }

        #endregion

        public DisplayNameAttribute(string displayName)
        {
            DisplayName = displayName;
        }
    }
}