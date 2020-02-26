#pragma once

#include "Templates/ChooseClass.h"
#include "DataConverters/Enums/ConverterEnums.h"
#include "Templates/XMLObjectTypeTraits.h"

#include <string>


namespace Celeste::XML
{
  struct ChildElementName
  {
    ChildElementName(const std::string& childElementName) : m_childElementName(childElementName) { }

    std::string m_childElementName;
  };

  class XMLObjectFactory
  {
  public:
    XMLObjectFactory() = delete;
    ~XMLObjectFactory() = delete;
    XMLObjectFactory(const XMLObjectFactory&) = delete;
    XMLObjectFactory& operator=(const XMLObjectFactory&) = delete;
    
    template <template<typename> class T, typename K>
    static std::unique_ptr<T<K>> create(
      const std::string& name,
      typename choose_class<is_reference<T, K>::value, const K&, K>::type defaultValue,
      DeserializationRequirement isRequired);

    template <template<typename> class T, typename K>
    static std::unique_ptr<T<K>> create(
      const std::string& name,
      DeserializationRequirement isRequired);

    template <template<typename> class T, typename K>
    static std::unique_ptr<T<K>> create(
      const std::string& name,
      const ChildElementName& childElementName,
      DeserializationRequirement isRequired);
  };

  //------------------------------------------------------------------------------------------------
  template <template<typename> class T, typename K>
  std::unique_ptr<T<K>> XMLObjectFactory::create(
    const std::string& name,
    typename choose_class<is_reference<T, K>::value, const K&, K>::type defaultValue,
    DeserializationRequirement isRequired)
  {
    return std::unique_ptr<T<K>>(new T<K>(name, defaultValue, isRequired));
  }

  //------------------------------------------------------------------------------------------------
  template <template<typename> class T, typename K>
  std::unique_ptr<T<K>> XMLObjectFactory::create(
    const std::string& name,
    DeserializationRequirement isRequired)
  {
    return std::unique_ptr<T<K>>(new T<K>(name, isRequired));
  }

  //------------------------------------------------------------------------------------------------
  template <template<typename> class T, typename K>
  std::unique_ptr<T<K>> XMLObjectFactory::create(
    const std::string& name,
    const ChildElementName& childElementName,
    DeserializationRequirement isRequired)
  {
    return std::unique_ptr<T<K>>(new T<K>(name, childElementName.m_childElementName, isRequired));
  }
}