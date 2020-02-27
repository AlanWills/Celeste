using System.Net;

namespace CelesteEditor
{
    public class InternetUtils
    {
        /// <summary>
        /// Attempts to establish a connection with google.com and returns true if the attempt was successful.
        /// </summary>
        /// <returns></returns>
        public static bool CheckInternetConnection()
        {
            return CheckURLValid("http://www.google.com");
        }

        /// <summary>
        /// Attempts to establish a connection to the inputted url and returns true if the attempt was successful.
        /// </summary>
        /// <param name="url"></param>
        /// <returns></returns>
        public static bool CheckURLValid(string url)
        {
            try
            {
                using (var client = new WebClient())
                {
                    using (var stream = client.OpenRead(url))
                    {
                        return true;
                    }
                }
            }
            catch
            {
                return false;
            }
        }
    }
}
