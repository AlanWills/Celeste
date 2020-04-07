#pragma once

#include "XMLEnums.h"
#include "tinyxml2.h"
#include "ChildXMLElementWalker.h"
#include "Assert/Assert.h"

#include <string>
#include <vector>

using namespace tinyxml2;


namespace Celeste::XML
{
  //------------------------------------------------------------------------------------------------
    // getChildElementCount
    //------------------------------------------------------------------------------------------------
  CelesteDllExport size_t getChildElementCount(const XMLElement* element);

  //------------------------------------------------------------------------------------------------
  // hasChildElement
  //------------------------------------------------------------------------------------------------
  CelesteDllExport bool hasChildElement(const XMLElement* element, const std::string& childElementName);

  //------------------------------------------------------------------------------------------------
  // getElementData<T>
  //------------------------------------------------------------------------------------------------
  template <typename T>
  XMLValueError getElementData(const XMLElement* element, T& output)
  {
    STATIC_ASSERT_FAIL("getElementData specialization not implemented for inputted type");
    return XMLValueError::kError;
  }

  //------------------------------------------------------------------------------------------------
  template <>
  CelesteDllExport XMLValueError getElementData(const XMLElement* element, float& output);

  //------------------------------------------------------------------------------------------------
  template <>
  CelesteDllExport XMLValueError getElementData(const XMLElement* element, std::string& output);

  //------------------------------------------------------------------------------------------------
  template <typename T>
  XMLValueError getElementDataAsVector(
    const XMLElement* element,
    const std::string& childItemElementName,
    std::vector<T>& output,
    bool allowEmptyElements = false)
  {
    if (element == nullptr)
    {
      ASSERT_FAIL();
      return XMLValueError::kError;
    }

    if (!childItemElementName.empty() && !hasChildElement(element, childItemElementName))
    {
      return XMLValueError::kDoesNotExist;
    }

    // We allow empty names through - they correspond to all children
    for (const XMLElement* itemElement : children(element, childItemElementName.c_str()))
    {
      T t;
      XMLValueError result = getElementData<T>(itemElement, t);
      if (result == XMLValueError::kError)
      {
        ASSERT_FAIL();
        return XMLValueError::kError;
      }
      else if (result == XMLValueError::kSuccess || allowEmptyElements)
      {
        output.push_back(t);
      }
    }

    return XMLValueError::kSuccess;
  }

  //------------------------------------------------------------------------------------------------
  // getChildElementData<T>
  //------------------------------------------------------------------------------------------------
  template <typename T>
  XMLValueError getChildElementData(const XMLElement* element, const std::string& childElementName, T& output)
  {
    STATIC_ASSERT_FAIL("getChildElementDataAs specialization not implemented for inputted type");
    return false;
  }

  //------------------------------------------------------------------------------------------------
  template <>
  CelesteDllExport XMLValueError getChildElementData(const XMLElement* element, const std::string& childElementName, float& output);

  //------------------------------------------------------------------------------------------------
  template <>
  CelesteDllExport XMLValueError getChildElementData(const XMLElement* element, const std::string& childElementName, std::string& output);

  //------------------------------------------------------------------------------------------------
  template <typename T>
  XMLValueError getChildElementDataAsVector(
    const XMLElement* element,
    const std::string& childElementName,
    const std::string& childItemElementName,
    std::vector<T>& output,
    bool allowEmptyElements = false)
  {
    if (element == nullptr)
    {
      ASSERT_FAIL();
      return XMLValueError::kError;
    }

    if (!hasChildElement(element, childElementName))
    {
      return XMLValueError::kDoesNotExist;
    }

    const XMLElement* childElement = element->FirstChildElement(childElementName.c_str());
    if (!hasChildElement(childElement, childItemElementName))
    {
      return XMLValueError::kDoesNotExist;
    }

    for (const XMLElement* itemElement : children(childElement, childItemElementName.c_str()))
    {
      T t;
      XMLValueError result = getElementData<T>(itemElement, t);
      if (result == XMLValueError::kError)
      {
        ASSERT_FAIL();
        return XMLValueError::kError;
      }
      else if (result == XMLValueError::kSuccess || allowEmptyElements)
      {
        output.push_back(t);
      }
    }

    return XMLValueError::kSuccess;
  }

  //------------------------------------------------------------------------------------------------
  // getAttributeData
  //------------------------------------------------------------------------------------------------
  CelesteDllExport XMLValueError getAttributeData(const XMLElement* element, const std::string& attributeName, bool& output);
  CelesteDllExport XMLValueError getAttributeData(const XMLElement* element, const std::string& attributeName, int& output);
  CelesteDllExport XMLValueError getAttributeData(const XMLElement* element, const std::string& attributeName, unsigned int& output);
  CelesteDllExport XMLValueError getAttributeData(const XMLElement* element, const std::string& attributeName, float& output);
  CelesteDllExport XMLValueError getAttributeData(const XMLElement* element, const std::string& attributeName, std::string& output);

  CelesteDllExport XMLValueError getAttributeData(const XMLAttribute* attribute, bool& output);
  CelesteDllExport XMLValueError getAttributeData(const XMLAttribute* attribute, int& output);
  CelesteDllExport XMLValueError getAttributeData(const XMLAttribute* attribute, unsigned int& output);
  CelesteDllExport XMLValueError getAttributeData(const XMLAttribute* attribute, float& output);
  CelesteDllExport XMLValueError getAttributeData(const XMLAttribute* attribute, std::string& output);
}