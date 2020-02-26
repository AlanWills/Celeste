using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;

namespace CelTestSharp
{
    public static class AssertExt
    {
        /// <summary>
        /// Will fail with a test exception if the inputted enumerator is not empty.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="enumerator"></param>
        public static void IsEmpty<T>(IEnumerable<T> enumerator)
        {
            Assert.AreEqual(0, enumerator.Count());
        }

        /// <summary>
        /// Will fail with a test exception if the inputted enumerator is empty.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="enumerator"></param>
        public static void IsNotEmpty<T>(IEnumerable<T> enumerator)
        {
            Assert.AreNotEqual(0, enumerator.Count());
        }

        /// <summary>
        /// Will fail with a test exception if the inputted object's type does not have the inputted attribute.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="obj"></param>
        public static void HasCustomAttribute<T>(object obj) where T : Attribute
        {
            HasCustomAttribute<T>(obj.GetType());
        }

        /// <summary>
        /// Will fail with a test exception if the inputted type does not have the inputted attribute.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="obj"></param>
        public static void HasCustomAttribute<T>(Type type) where T : Attribute
        {
            Assert.IsNull(type.GetCustomAttribute<T>());
        }
    }
}
