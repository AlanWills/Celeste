using System.Diagnostics;

namespace BindingsKernel
{
    public static class CelDebug
    {
        #region Properties and Fields

        /// <summary>
        /// Set this to true to avoid asserts being fired, even in Debug.  Useful in unit tests to stop blocking assert dialogs.
        /// </summary>
        public static bool SuppressAsserts { get; set; } = false;

        #endregion

        /// <summary>
        /// Checks that the inputted condition is true and if not will raise a Debug Assertion.
        /// </summary>
        /// <param name="objectToTest"></param>
        /// <param name="message"></param>
        [Conditional("DEBUG")]
        public static void Assert(bool condition, string message = "")
        {
            if (!SuppressAsserts)
            {
                Debug.Assert(condition, message);
            }
        }

        /// <summary>
        /// Checks that the inputted value is not null and will raise a Debug Assertion if it is.
        /// </summary>
        /// <param name="objectToTest"></param>
        /// <param name="message"></param>
        [Conditional("DEBUG")]
        public static void AssertNotNull(object objectToTest, string message = "")
        {
            Assert(objectToTest != null, message);
        }

        /// <summary>
        /// Raises a Debug Assertion with the inputted message.
        /// </summary>
        /// <param name="objectToTest"></param>
        /// <param name="message"></param>
        [Conditional("DEBUG")]
        public static void Fail(string message = "")
        {
            Assert(false, message);
        }
    }
}