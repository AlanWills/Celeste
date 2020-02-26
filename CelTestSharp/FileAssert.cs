using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace CelTestSharp
{
    public static class FileAssert
    {
        /// <summary>
        /// Will cause an assertion fail if the inputted filepath does not exist.
        /// </summary>
        /// <param name="filePath"></param>
        public static void FileExists(string filePath)
        {
            Assert.IsTrue(File.Exists(filePath));
        }

        /// <summary>
        /// Will cause an assertion fail if the inputted filepath does exist.
        /// </summary>
        /// <param name="filePath"></param>
        public static void FileDoesNotExist(string filePath)
        {
            Assert.IsFalse(File.Exists(filePath));
        }
    }
}
