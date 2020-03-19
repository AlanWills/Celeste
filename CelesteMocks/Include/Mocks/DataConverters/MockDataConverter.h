#pragma once

#include "DataConverters/DataConverter.h"


namespace CelesteMocks
{
  class MockDataConverter : public Celeste::DataConverter
  {
    public:
      MockDataConverter(const std::string& elementName = "MockDataConverter") : 
        Celeste::DataConverter(elementName), 
        m_isDoConvertFromXMLCalled(false) 
      { 
      }
      
      MockDataConverter(const MockDataConverter& rhs) :
        Celeste::DataConverter(rhs),
        m_isDoConvertFromXMLCalled(rhs.m_isDoConvertFromXMLCalled)
      {
      }

      MockDataConverter(MockDataConverter&& rhs) :
        Celeste::DataConverter(std::move(rhs)),
        m_isDoConvertFromXMLCalled(std::move(rhs.m_isDoConvertFromXMLCalled))
      {
      }

      MockDataConverter& operator=(const MockDataConverter& rhs)
      {
        Celeste::DataConverter::operator=(rhs);
        return *this;
      }

      bool isDoConvertFromXMLCalled() const { return m_isDoConvertFromXMLCalled; }

      template <typename T>
      Celeste::XML::ValueAttribute<T>& createValueAttribute_Public(
        const std::string& name,
        T defaultValue = T(),
        Celeste::DeserializationRequirement isRequired = Celeste::DeserializationRequirement::kNotRequired)
      {
        return createValueAttribute<T>(name, defaultValue, isRequired);
      }

      template <typename T>
      Celeste::XML::ReferenceAttribute<T>& createReferenceAttribute_Public(
        const std::string& name,
        const T& defaultValue = T(),
        Celeste::DeserializationRequirement isRequired = Celeste::DeserializationRequirement::kNotRequired)
      { 
        return createReferenceAttribute<T>(name, defaultValue, isRequired); 
      }

      template <typename T>
      Celeste::XML::ValueElement<T>& createValueElement_Public(
        const std::string& name,
        T defaultValue = T(),
        Celeste::DeserializationRequirement isRequired = Celeste::DeserializationRequirement::kNotRequired)
      {
        return createValueElement<T>(name, defaultValue, isRequired);
      }

      template <typename T>
      Celeste::XML::ReferenceElement<T>& createReferenceElement_Public(
        const std::string& name,
        const T& defaultValue = T(),
        Celeste::DeserializationRequirement isRequired = Celeste::DeserializationRequirement::kNotRequired)
      {
        return createReferenceElement<T>(name, defaultValue, isRequired);
      }

      template <typename T>
      typename Celeste::XML::ListElement<T>& createListElement_Public(
        const std::string& name,
        Celeste::DeserializationRequirement isRequired = Celeste::DeserializationRequirement::kNotRequired)
      {
        return createListElement<T>(name, isRequired);
      }

      template <typename T>
      typename Celeste::XML::ListElement<T>& createListElement_Public(
        const std::string& name,
        const std::string& childElementName,
        Celeste::DeserializationRequirement isRequired = Celeste::DeserializationRequirement::kNotRequired)
      {
        return createListElement<T>(name, childElementName, isRequired);
      }

      template <typename T>
      typename Celeste::XML::DataConverterListElement<T>& createDataConverterListElement_Public(
        const std::string& name,
        Celeste::DeserializationRequirement isRequired = Celeste::DeserializationRequirement::kNotRequired)
      {
        return createDataConverterListElement<T>(name, isRequired);
      }

      template <typename T>
      typename Celeste::XML::DataConverterListElement<T>& createDataConverterListElement_Public(
        const std::string& name,
        const std::string& childElementName,
        Celeste::DeserializationRequirement isRequired = Celeste::DeserializationRequirement::kNotRequired)
      {
        return createDataConverterListElement<T>(name, childElementName, isRequired);
      }

      void addData_Public(Celeste::XML::Attribute* attribute) { addData(attribute); }
      void addData_Public(Celeste::XML::Element* element) { addData(element); }

    protected:
      bool doConvertFromXML(const XMLElement* /*objectElement*/) override
      { 
        m_isDoConvertFromXMLCalled = true;
        return true;
      }

    private:
      bool m_isDoConvertFromXMLCalled;
  };
}