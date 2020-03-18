#include "Bindings/BindingUtils.h"
#include "Utils/StringUtils.h"

#include <cctype>
#include <algorithm>


namespace Celeste::Bindings
{
  //------------------------------------------------------------------------------------------------
  std::string displayNameToVariableName(const std::string& displayName)
  {
    std::string output(displayName);
    trim(output);

    if (output.empty())
    {
      return output;
    }

    output[0] = static_cast<char>(std::toupper(output[0]));
    auto it = std::find_if(output.begin(), output.end(), [](char c) -> bool { return c == ' '; });

    while (it != output.end())
    {
      ++it;
      *it = static_cast<char>(std::toupper(*it));
      it = std::find_if(it, output.end(), [](char c) -> bool { return c == ' '; });
    }

    output.erase(std::remove_if(output.begin(), output.end(), [](char c) -> bool { return c == ' '; }), output.end());
    return output;
  }

  //------------------------------------------------------------------------------------------------
  std::string xmlAttributeNameToVariableName(const std::string& xmlAttributeName)
  {
    std::string output(xmlAttributeName);
    trim(output);

    if (output.empty())
    {
      return output;
    }

    output[0] = static_cast<char>(std::toupper(output[0]));
    auto it = std::find_if(output.begin(), output.end(), [](char c) -> bool { return c == '_'; });

    while (it != output.end())
    {
      ++it;
      *it = static_cast<char>(std::toupper(*it));
      it = std::find_if(it, output.end(), [](char c) -> bool { return c == '_'; });
    }

    output.erase(std::remove_if(output.begin(), output.end(), [](char c) -> bool { return c == '_'; }), output.end());
    return output;
  }

  //------------------------------------------------------------------------------------------------
  std::string xmlAttributeNameToDisplayName(const std::string& xmlAttributeName)
  {
    std::string output(xmlAttributeName);
    trim(output);

    if (output.empty())
    {
      return output;
    }

    output[0] = static_cast<char>(std::toupper(output[0]));
    auto it = std::find_if(output.begin(), output.end(), [](char c) -> bool { return c == '_'; });

    while (it != output.end())
    {
      *it = ' ';
      ++it;
      *it = static_cast<char>(std::toupper(*it));
      it = std::find_if(it, output.end(), [](char c) -> bool { return c == '_'; });
    }

    return output;
  }

  //------------------------------------------------------------------------------------------------
  std::string variableNameToDisplayName(const std::string& variableName)
  {
    std::string output(variableName);
    trim(output);

    if (output.empty())
    {
      return output;
    }

    auto it = std::find_if(output.begin() + 1, output.end(), [](char c) -> bool { return std::isupper(c); });
    while (it != output.end())
    {
      size_t index = it - output.begin();
      if (*(it - 1) != ' ')
      {
        output.insert(it, ' ');
        ++index;
      }
      it = std::find_if(output.begin() + index + 1, output.end(), [](char c) -> bool { return std::isupper(c); });
    }

    return output;
  }

  //------------------------------------------------------------------------------------------------
  std::string cppNamespaceToCsNamespace(const std::string& cppNamespaceName)
  {
    std::string namespaceName(cppNamespaceName);

    // Replace '::' with '.'
    size_t index = namespaceName.find("::");
    while (index < namespaceName.size())
    {
      namespaceName.replace(index, 2, ".");
      index = namespaceName.find("::", index);
    }

    return namespaceName;
  }
}