#pragma once

#include "XML/tinyxml2_ext.h"
#include "CelesteDllExport.h"
#include "XML/Attributes/DataAttribute.h"
#include "XML/Elements/ListElement.h"
#include "XML/Elements/DataElement.h"
#include "XML/Elements/DataConverterListElement.h"
#include "XML/XMLObjectFactory.h"
#include "Memory/ObserverPtr.h"

#include <string>
#include <vector>


namespace Celeste
{
  namespace Bindings
  {
    class BindingsGenerator;
  }

  class DataConverter
  {
    public:
      CelesteDllExport DataConverter(const std::string& elementName);
      CelesteDllExport DataConverter(const DataConverter& dataConverter);
      CelesteDllExport DataConverter(DataConverter&& rhs) noexcept;
      CelesteDllExport DataConverter& operator=(const DataConverter& dataConverter);
      CelesteDllExport virtual ~DataConverter();

      inline const std::string& getElementName() const { return m_elementName; }
      inline bool isDataLoadedCorrectly() const { return m_dataLoadedCorrectly; }

      CelesteDllExport bool convertFromXML(const XMLElement* objectElement);
      CelesteDllExport bool convertFromXML(const Path& fullFilePath);
      CelesteDllExport bool convertFromXML(const std::string& fullFilePath);

      CelesteDllExport observer_ptr<const XML::Attribute> getAttribute(size_t index) const { return const_cast<DataConverter*>(this)->getAttribute(index); }
      CelesteDllExport observer_ptr<const XML::Attribute> findAttribute(const std::string& name) const { return const_cast<DataConverter*>(this)->findAttribute(name); }
      inline size_t getAttributesSize() const { return m_attributes.size(); }

      CelesteDllExport observer_ptr<const XML::Element> getElement(size_t index) const { return const_cast<DataConverter*>(this)->getElement(index); }
      CelesteDllExport observer_ptr<const XML::Element> findElement(const std::string& name) const { return const_cast<DataConverter*>(this)->findElement(name); }
      inline size_t getElementsSize() const { return m_elements.size(); }

      CelesteDllExport void cleanupData();

    protected:
      template <typename T>
      typename XML::ValueAttribute<T>& createValueAttribute(
        const std::string& name,
        T defaultValue = T(),
        DeserializationRequirement isRequired = DeserializationRequirement::kNotRequired) 
      { 
        return createData<XML::ValueAttribute, T>(name, defaultValue, isRequired);
      }

      template <typename T>
      typename XML::ReferenceAttribute<T>& createReferenceAttribute(
        const std::string& name,
        const T& defaultValue = T(),
        DeserializationRequirement isRequired = DeserializationRequirement::kNotRequired)
      {
        return createData<XML::ReferenceAttribute, T>(name, defaultValue, isRequired);
      }

      template <typename T>
      typename XML::ValueElement<T>& createValueElement(
        const std::string& name,
        T defaultValue = T(),
        DeserializationRequirement isRequired = DeserializationRequirement::kNotRequired)
      {
        return createData<XML::ValueElement, T>(name, defaultValue, isRequired);
      }

      template <typename T>
      typename XML::ReferenceElement<T>& createReferenceElement(
        const std::string& name,
        const T& defaultValue = T(),
        DeserializationRequirement isRequired = DeserializationRequirement::kNotRequired)
      {
        return createData<XML::ReferenceElement, T>(name, defaultValue, isRequired);
      }

      template <typename T>
      typename XML::ListElement<T>& createListElement(
        const std::string& name, 
        DeserializationRequirement isRequired = DeserializationRequirement::kNotRequired)
      {
        return createData<XML::ListElement, T>(name, isRequired);
      }

      template <typename T>
      typename XML::ListElement<T>& createListElement(
        const std::string& name,
        const XML::ChildElementName& childElementName,
        DeserializationRequirement isRequired = DeserializationRequirement::kNotRequired)
      {
        return createData<XML::ListElement, T>(name, childElementName, isRequired);
      }

      template <typename T>
      typename XML::DataConverterListElement<T>& createDataConverterListElement(
        const std::string& name,
        DeserializationRequirement isRequired = DeserializationRequirement::kNotRequired)
      {
        return createData<XML::DataConverterListElement, T>(name, isRequired);
      }

      template <typename T>
      typename XML::DataConverterListElement<T>& createDataConverterListElement(
        const std::string& name,
        const XML::ChildElementName& childElementName,
        DeserializationRequirement isRequired = DeserializationRequirement::kNotRequired)
      {
        return createData<XML::DataConverterListElement, T>(name, childElementName, isRequired);
      }

      inline void addData(XML::Attribute* attribute) { m_attributes.push_back(attribute); }
      inline void addData(XML::Element* element) { m_elements.push_back(element); }

      CelesteDllExport observer_ptr<XML::Attribute> getAttribute(size_t index);
      CelesteDllExport observer_ptr<XML::Attribute> findAttribute(const std::string& name);
      CelesteDllExport observer_ptr<XML::Element> getElement(size_t index);
      CelesteDllExport observer_ptr<XML::Element> findElement(const std::string& name);

      virtual bool doConvertFromXML(const XMLElement* /*objectElement*/) { return true; }

    private:
      template <template<typename> class T, typename K>
      typename T<K>& createData(
        const std::string& name,
        typename choose_class<XML::is_reference<T, K>::value, const K&, K>::type defaultValue,
        DeserializationRequirement isRequired);

      template <template<typename> class T, typename K>
      typename T<K>& createData(
        const std::string& name,
        DeserializationRequirement isRequired);

      template <template<typename> class T, typename K>
      typename T<K>& createData(
        const std::string& name,
        const XML::ChildElementName& childElementName,
        DeserializationRequirement isRequired);

      void copyDataFrom(const DataConverter& rhs);

      std::vector<XML::Attribute*> m_attributes;
      std::vector<XML::Element*> m_elements;

      std::string m_elementName;
      bool m_dataLoadedCorrectly;

      friend class Celeste::Bindings::BindingsGenerator;
  };

  //------------------------------------------------------------------------------------------------
  template <template<typename> class T, typename K>
  typename T<K>& DataConverter::createData(
    const std::string& name,
    typename choose_class<XML::is_reference<T, K>::value, const K&, K>::type defaultValue,
    DeserializationRequirement isRequired)
  {
    auto data = XML::XMLObjectFactory::create<T, K>(name, defaultValue, isRequired).release();
    addData(data);

    return *data;
  }

  //------------------------------------------------------------------------------------------------
  template <template<typename> class T, typename K>
  typename T<K>& DataConverter::createData(
    const std::string& name,
    DeserializationRequirement isRequired)
  {
    auto* data = XML::XMLObjectFactory::create<T, K>(name, isRequired).release();
    addData(data);

    return *data;
  }

  //------------------------------------------------------------------------------------------------
  template <template<typename> class T, typename K>
  typename T<K>& DataConverter::createData(
    const std::string& name,
    const XML::ChildElementName& childElementName,
    DeserializationRequirement isRequired)
  {
    auto* data = XML::XMLObjectFactory::create<T, K>(name, childElementName, isRequired).release();
    addData(data);

    return *data;
  }
}