using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CelesteEngineEditor.Comparer
{
    public class DirectoryInfoEqualityComparer : IEqualityComparer<DirectoryInfo>
    {
        /// <summary>
        /// Returns true if the two directories have the same full name.
        /// </summary>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <returns></returns>
        public bool Equals(DirectoryInfo x, DirectoryInfo y)
        {
            return x.FullName == y.FullName;
        }

        /// <summary>
        /// Returns the hash code of the directory full name.
        /// </summary>
        /// <param name="obj"></param>
        /// <returns></returns>
        public int GetHashCode(DirectoryInfo obj)
        {
            return obj.FullName.GetHashCode();
        }
    }
}
