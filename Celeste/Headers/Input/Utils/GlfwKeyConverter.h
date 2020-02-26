#pragma once

#include "CelesteDllExport.h"

#include <unordered_map>


namespace Celeste
{
  namespace Input
  {
    class GlfwKeyConverter
    {
      public:
        // Force through our static interface by ensuring no instances can be created
        GlfwKeyConverter() = delete;
        ~GlfwKeyConverter() = delete;
        GlfwKeyConverter(const GlfwKeyConverter&) = delete;
        GlfwKeyConverter& operator=(const GlfwKeyConverter&) = delete;

        CelesteDllExport static int getGlfwKeyFromName(const std::string& keyName);
        CelesteDllExport static std::string getNameFromGlfwKey(int glfwKey);

      private:
        // Most of the keys will be characters so we store them in two maps to avoid wasting lots of space
        // with std::strings of length 1
        static std::unordered_map<char, int> m_charToNumberLookup;
        static std::unordered_map<std::string, int> m_stringToNumberLookup;

        // A reverse map for mapping GLFW keys to names
        static std::unordered_map<int, const char*> m_intToNameLookup;
    };
  }
}