#include "DataConverters/DataConverter.h"


namespace Celeste::XML
{
  namespace detail
  {
    //------------------------------------------------------------------------------------------------
    XMLValueError getElementDataAsText(const XMLElement* element, const char** output)
    {
      if (element == nullptr)
      {
        ASSERT_FAIL();
        return XMLValueError::kError;
      }

      *output = element->GetText();
      return *output != nullptr ? XMLValueError::kSuccess : XMLValueError::kDoesNotExist;
    }

    //------------------------------------------------------------------------------------------------
    XMLValueError getElementDataAsText(const XMLElement* element, std::string& output)
    {
      if (element == nullptr)
      {
        ASSERT_FAIL();
        return XMLValueError::kError;
      }

      const char* charT = element->GetText();
      if (charT != nullptr)
      {
        output.append(charT);
      }
      return charT != nullptr ? XMLValueError::kSuccess : XMLValueError::kDoesNotExist;
    }

    //------------------------------------------------------------------------------------------------
    XMLValueError getElementDataAsFloat(const XMLElement* element, float& output)
    {
      if (element == nullptr)
      {
        ASSERT_FAIL();
        return XMLValueError::kError;
      }

      return element->QueryFloatText(&output) == XMLError::XML_SUCCESS ? XMLValueError::kSuccess : XMLValueError::kError;
    }

    //------------------------------------------------------------------------------------------------
    XMLValueError getChildElementDataAsText(const XMLElement* element, const std::string& childElementName, const char** output)
    {
      if (element == nullptr)
      {
        ASSERT_FAIL();
        return XMLValueError::kError;
      }

      if (!hasChildElement(element, childElementName))
      {
        ASSERT_FAIL();
        return XMLValueError::kDoesNotExist;
      }

      return getElementDataAsText(element->FirstChildElement(childElementName.c_str()), output);
    }

    //------------------------------------------------------------------------------------------------
    XMLValueError getChildElementDataAsText(const XMLElement* element, const std::string& childElementName, std::string& output)
    {
      if (element == nullptr)
      {
        ASSERT_FAIL();
        return XMLValueError::kError;
      }

      if (!hasChildElement(element, childElementName))
      {
        ASSERT_FAIL();
        return XMLValueError::kDoesNotExist;
      }

      return getElementDataAsText(element->FirstChildElement(childElementName.c_str()), output);
    }

    //------------------------------------------------------------------------------------------------
    XMLValueError getChildElementDataAsFloat(const XMLElement* element, const std::string& childElementName, float& output)
    {
      if (element == nullptr)
      {
        ASSERT_FAIL();
        return XMLValueError::kError;
      }

      if (!hasChildElement(element, childElementName))
      {
        ASSERT_FAIL();
        return XMLValueError::kDoesNotExist;
      }

      return getElementDataAsFloat(element->FirstChildElement(childElementName.c_str()), output);
    }

    //------------------------------------------------------------------------------------------------
    XMLValueError checkElementAndAttribute(const XMLElement* element, const std::string& attributeName)
    {
      if (element == nullptr)
      {
        ASSERT_FAIL();
        return XMLValueError::kError;
      }

      const XMLAttribute* attribute = element->FindAttribute(attributeName.c_str());
      if (attribute == nullptr)
      {
        return XMLValueError::kDoesNotExist;
      }

      return XMLValueError::kSuccess;
    }
  }

  //------------------------------------------------------------------------------------------------
  size_t getChildElementCount(const XMLElement* element)
  {
    if (element == nullptr || element->NoChildren())
    {
      return 0;
    }

    size_t count = 0;
    for (const XMLElement* child : children(element))
    {
      ++count;
    }

    return count;
  }

  //------------------------------------------------------------------------------------------------
  bool hasChildElement(const XMLElement* element, const std::string& childElementName)
  {
    return (element != nullptr) && (element->FirstChildElement(childElementName.c_str()) != nullptr);
  }

  //------------------------------------------------------------------------------------------------
  template <>
  XMLValueError getElementData(const XMLElement* element, float& output)
  {
    return detail::getElementDataAsFloat(element, output);
  }

  //------------------------------------------------------------------------------------------------
  template <>
  XMLValueError getElementData(const XMLElement* element, std::string& output)
  {
    return detail::getElementDataAsText(element, output);
  }

  //------------------------------------------------------------------------------------------------
  template <>
  XMLValueError getChildElementData(const XMLElement* element, const std::string& childElementName, float& output)
  {
    return detail::getChildElementDataAsFloat(element, childElementName, output);
  }

  //------------------------------------------------------------------------------------------------
  template <>
  XMLValueError getChildElementData(const XMLElement* element, const std::string& childElementName, std::string& output)
  {
    return detail::getChildElementDataAsText(element, childElementName, output);
  }

  //------------------------------------------------------------------------------------------------
  XMLValueError getAttributeData(const XMLElement* element, const std::string& attributeName, bool& output)
  {
    XMLValueError result = detail::checkElementAndAttribute(element, attributeName);
    if (result != XMLValueError::kSuccess)
    {
      return result;
    }

    const XMLAttribute* attribute = element->FindAttribute(attributeName.c_str());
    const char* text = attribute->Value();
    if (text == nullptr)
    {
      ASSERT_FAIL();
      return XMLValueError::kError;
    }

    if (strcmp(text, "true") == 0)
    {
      output = true;
      return XMLValueError::kSuccess;
    }
    else if (strcmp(text, "false") == 0)
    {
      output = false;
      return XMLValueError::kSuccess;
    }

    ASSERT_FAIL();
    return XMLValueError::kError;
  }

  //------------------------------------------------------------------------------------------------
  XMLValueError getAttributeData(const XMLElement* element, const std::string& attributeName, int& output)
  {
    XMLValueError result = detail::checkElementAndAttribute(element, attributeName);
    if (result != XMLValueError::kSuccess)
    {
      return result;
    }

    return element->QueryIntAttribute(attributeName.c_str(), &output) == XML_SUCCESS ? XMLValueError::kSuccess : XMLValueError::kError;
  }

  //------------------------------------------------------------------------------------------------
  XMLValueError getAttributeData(const XMLElement* element, const std::string& attributeName, unsigned int& output)
  {
    XMLValueError result = detail::checkElementAndAttribute(element, attributeName);
    if (result != XMLValueError::kSuccess)
    {
      return result;
    }

    return element->QueryUnsignedAttribute(attributeName.c_str(), &output) == XML_SUCCESS ? XMLValueError::kSuccess : XMLValueError::kError;
  }

  //------------------------------------------------------------------------------------------------
  XMLValueError getAttributeData(const XMLElement* element, const std::string& attributeName, float& output)
  {
    XMLValueError result = detail::checkElementAndAttribute(element, attributeName);
    if (result != XMLValueError::kSuccess)
    {
      return result;
    }

    return element->QueryFloatAttribute(attributeName.c_str(), &output) == XML_SUCCESS ? XMLValueError::kSuccess : XMLValueError::kError;
  }

  //------------------------------------------------------------------------------------------------
  XMLValueError getAttributeData(const XMLElement* element, const std::string& attributeName, std::string& output)
  {
    XMLValueError result = detail::checkElementAndAttribute(element, attributeName);
    if (result != XMLValueError::kSuccess)
    {
      return result;
    }

    const XMLAttribute* attribute = element->FindAttribute(attributeName.c_str());
    const char* text = attribute->Value();
    if (text == nullptr)
    {
      ASSERT_FAIL();
      return XMLValueError::kError;
    }

    output.assign(text);
    return XMLValueError::kSuccess;
  }

  //------------------------------------------------------------------------------------------------
  XMLValueError getAttributeData(const XMLAttribute* attribute, bool& output)
  {
    if (attribute == nullptr)
    {
      ASSERT_FAIL();
      return XMLValueError::kError;
    }

    return attribute->QueryBoolValue(&output) == XML_SUCCESS ? XMLValueError::kSuccess : XMLValueError::kError;
  }

  //------------------------------------------------------------------------------------------------
  XMLValueError getAttributeData(const XMLAttribute* attribute, int& output)
  {
    if (attribute == nullptr)
    {
      ASSERT_FAIL();
      return XMLValueError::kError;
    }

    return attribute->QueryIntValue(&output) == XML_SUCCESS ? XMLValueError::kSuccess : XMLValueError::kError;
  }

  //------------------------------------------------------------------------------------------------
  XMLValueError getAttributeData(const XMLAttribute* attribute, unsigned int& output)
  {
    if (attribute == nullptr)
    {
      ASSERT_FAIL();
      return XMLValueError::kError;
    }

    return attribute->QueryUnsignedValue(&output) == XML_SUCCESS ? XMLValueError::kSuccess : XMLValueError::kError;
  }

  //------------------------------------------------------------------------------------------------
  XMLValueError getAttributeData(const XMLAttribute* attribute, float& output)
  {
    if (attribute == nullptr)
    {
      ASSERT_FAIL();
      return XMLValueError::kError;
    }

    return attribute->QueryFloatValue(&output) == XML_SUCCESS ? XMLValueError::kSuccess : XMLValueError::kError;
  }

  //------------------------------------------------------------------------------------------------
  XMLValueError getAttributeData(const XMLAttribute* attribute, std::string& output)
  {
    if (attribute == nullptr)
    {
      ASSERT_FAIL();
      return XMLValueError::kError;
    }

    if (attribute->Value() != nullptr)
    {
      output.assign(attribute->Value());
      return XMLValueError::kSuccess;
    }
    
    return XMLValueError::kError;
  }
}