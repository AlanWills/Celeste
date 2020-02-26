using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BindingsKernel
{
    public class DisplayPriorityAttribute : Attribute
    {
        #region Properties and Fields

        public int Priority { get; set; }

        #endregion

        public DisplayPriorityAttribute(int priority)
        {
            Priority = priority;
        }
    }
}
