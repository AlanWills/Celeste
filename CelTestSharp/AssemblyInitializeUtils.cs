using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;

namespace CelTestSharp
{
    public static class AssemblyInitializeUtils
    {
        public static void DisableAssertions()
        {
            Trace.Listeners.Clear();
        }
    }
}
