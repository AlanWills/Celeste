using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Text;

namespace CelTestSharp
{
    [TestClass]
    public class UnitTest
    {
        #region Setup/Teardown

        [TestInitialize]
        public void UnitTest_Setup()
        {
            Resources.CleanTempDir();
        }

        [TestCleanup]
        public void UnitTest_Cleanup()
        {
            Resources.CleanTempDir();
        }

        #endregion
    }
}
