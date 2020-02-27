using BindingsKernel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEditor.Editors
{
    public class HierarchyPrefabInstanceViewModel : HierarchyGameObjectViewModel
    {
        public HierarchyPrefabInstanceViewModel(PrefabInstance prefabInstance) :
            base(prefabInstance)
        {
        }
    }
}
