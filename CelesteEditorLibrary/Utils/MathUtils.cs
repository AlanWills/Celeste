using BindingsKernel;
using System;

namespace CelesteEditor
{
    /// <summary>
    /// Provides extra maths utility functions missing from standard C# API.
    /// </summary>
    public static class MathUtils
    {
        /// <summary>
        /// Returns the inputted value clamped between the inputted min (inclusive) and the inputted max (inclusive).
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="input"></param>
        /// <param name="min"></param>
        /// <param name="max"></param>
        /// <returns></returns>
        public static T Clamp<T>(T input, T min, T max) where T : IComparable<T>
        {
            // Max should be greater than min
            CelDebug.Assert(min.CompareTo(max) < 0);

            if (input.CompareTo(min) < 0)
            {
                // Input less than min so set it to min
                input = min;
            }
            else if (input.CompareTo(max) > 0)
            {
                // Input greater than max so set it to max
                input = max;
            }

            return input;
        }

        /// <summary>
        /// Returns the inputted value's modulus (max - min) in the range min (inclusive) and max (exclusive).
        /// Useful for ensure rotation values are in the range [0, 360).
        /// </summary>
        /// <param name="input"></param>
        /// <param name="min"></param>
        /// <param name="max"></param>
        /// <returns></returns>
        public static float ModulusInRange(float input, float min, float max)
        {
            // Max should be greater than min
            CelDebug.Assert(min < max);

            float diff = max - min;
            input = input % diff;

            while (input < min)
            {
                input += diff;
            }

            while (input >= max)
            {
                input -= diff;
            }
            
            return input;
        }

        /// <summary>
        /// Returns the max value of an array of float values.
        /// </summary>
        /// <param name="values"></param>
        /// <returns></returns>
        public static float Max(params float[] values)
        {
            if (values == null || values.Length == 0)
            {
                return float.MinValue;
            }

            float currentMax = values[0];
            for (int i = 1; i < values.Length; ++i)
            {
                currentMax = Math.Max(currentMax, values[i]);
            }

            return currentMax;
        }
    }
}
