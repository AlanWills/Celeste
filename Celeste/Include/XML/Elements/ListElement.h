#pragma once

#include "Element.h"
#include "XML/ChildXMLElementWalker.h"
#include "XML/tinyxml2_ext.h"

#include <vector>


namespace Celeste::XML
{
  class XMLObjectFactory;

  //------------------------------------------------------------------------------------------------
  template <typename T>
  class ListElement : public Element
  {
  public:
    const std::string& getChildElementName() const { return m_childElementName; }
    const std::vector<T>& getChildren() const { return m_children; }

    void clear() { m_children.clear(); }

    typename std::vector<T>::const_iterator begin() const { return m_children.begin(); }
    typename std::vector<T>::const_iterator end() const { return m_children.end(); }

    ListElement<T>* clone() const override;

    static constexpr bool isReference() { return false; }

  protected:
    bool doConvertFromXML(const tinyxml2::XMLElement* element)
    {
      XMLValueError result = getElementDataAsVector<T>(element, getChildElementName(), m_children, !isRequired());
      return result == XML::XMLValueError::kSuccess || (result == XML::XMLValueError::kDoesNotExist && !isRequired());
    }

  private:
    using Inherited = Element;

    // Need both of these constructors explicitly for templates
    ListElement(const std::string& elementName, DeserializationRequirement required = DeserializationRequirement::kNotRequired);
    ListElement(
      const std::string& elementName,
      const std::string& childElementName,
      DeserializationRequirement required = DeserializationRequirement::kNotRequired);

    std::string m_childElementName;
    std::vector<T> m_children;

    friend class Celeste::XML::XMLObjectFactory;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  ListElement<T>::ListElement(const std::string& elementName, DeserializationRequirement required) :
    ListElement<T>(elementName, "", required)
  {
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  ListElement<T>::ListElement(
    const std::string& elementName,
    const std::string& childElementName,
    DeserializationRequirement required) :
    Inherited(elementName, required),
    m_childElementName(childElementName),
    m_children()
  {
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  ListElement<T>* ListElement<T>::clone() const
  {
    ListElement<T>* clone = new ListElement<T>(
      getElementName(), getChildElementName(), isRequired() ? DeserializationRequirement::kRequired : DeserializationRequirement::kNotRequired);

    clone->m_children.assign(m_children.begin(), m_children.end());
    return clone;
  }
}