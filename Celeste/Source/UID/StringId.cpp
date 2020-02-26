#include "UID/StringId.h"


namespace Celeste
{
  static std::unordered_map<StringId, std::string> g_stringIdTable;
  static std::unordered_map<std::string, StringId> g_idStringTable;   // Used for quick interning

  //------------------------------------------------------------------------------------------------
  StringId internString(const std::string& str)
  {
    // Attempt a quick intern
    if (g_idStringTable.find(str) != g_idStringTable.end())
    {
      return g_idStringTable[str];
    }

    StringId strId = stringToStringId(str.c_str());

    if (g_stringIdTable.find(strId) == g_stringIdTable.end())
    {
      // If our string does not exist in the lookup table, we should add it
      g_stringIdTable.emplace(strId, str);

      // Add it to our reverse map too
      g_idStringTable.emplace(str, strId);
    }

    return strId;
  }

  //------------------------------------------------------------------------------------------------
  std::string deinternString(StringId strId)
  {
    return g_stringIdTable.find(strId) != g_stringIdTable.end() ? g_stringIdTable[strId] : "";
  }
}