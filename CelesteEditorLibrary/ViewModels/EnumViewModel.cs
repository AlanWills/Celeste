using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEngineEditor.ViewModels
{
    public class EnumViewModel
    {
        #region Properties and Fields

        public Enum Value { get; set; }

        public string Description { get; set; }

        #endregion

        public EnumViewModel(Enum value, string description)
        {
            Value = value;
            Description = description;
        }
    }
}
