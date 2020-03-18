#pragma once

#include "Element.h"

#include <vector>


namespace Celeste
{
  class ComponentDataConverter;
  class GameObjectDataConverter;

  namespace XML
  {
    class XMLObjectFactory;

    template <typename T>
    class DataConverterListElement : public Element
    {
      public:
        using Items = typename std::vector<T*>;

        // Cannot have copy constructor as we cannot create pointer vector
        DataConverterListElement(const DataConverterListElement&) = delete;
        DataConverterListElement& operator=(const DataConverterListElement&) = delete;
        ~DataConverterListElement() override;

        const Items& getItems() const { return m_items; }
        const std::string& getItemElementName() const { return m_itemElementName; }

        void clear() { m_items.clear(); }

        typename Items::const_iterator begin() const { return m_items.cbegin(); }
        typename Items::const_iterator end() const { return m_items.cend(); }

        DataConverterListElement<T>* clone() const override;

        static constexpr bool isReference() { return false; }

  #if _DEBUG
        void generateBinding(std::string& output) const override
        {
          output.append("\t\tpublic List<Component> ");
          output.append(getElementName());
          output.append(" { get; set; } = new List<Component>();");
        }
  #endif

      protected:
        bool doConvertFromXML(const tinyxml2::XMLElement* listElement) override;

      private:
        using Inherited = Element;

        // Need both these constructors explicitly for templated functions
        DataConverterListElement(
          const std::string& elementName,
          DeserializationRequirement required = DeserializationRequirement::kNotRequired) :
          DataConverterListElement(elementName, "", required) { }

        DataConverterListElement(
          const std::string& elementName,
          const std::string& childElementName,
          DeserializationRequirement required = DeserializationRequirement::kNotRequired) :
          Element(elementName, required),
          m_items(),
          m_itemElementName(childElementName)
        {
        }

        Items m_items;
        std::string m_itemElementName;

        friend class Celeste::XML::XMLObjectFactory;
    };

    //------------------------------------------------------------------------------------------------
    template <typename T>
    DataConverterListElement<T>::~DataConverterListElement()
    {
      for (T* converter : getItems())
      {
        delete converter;
      }
    }

    //------------------------------------------------------------------------------------------------
    template <typename T>
    DataConverterListElement<T>* DataConverterListElement<T>::clone() const
    {
      DataConverterListElement<T>* clone = new DataConverterListElement<T>(
        getElementName(), m_itemElementName, isRequired() ? DeserializationRequirement::kRequired : DeserializationRequirement::kNotRequired);

      // Need to copy child data converters somehow
      return clone;
    }

    //------------------------------------------------------------------------------------------------
    template <typename T>
    bool DataConverterListElement<T>::doConvertFromXML(const tinyxml2::XMLElement* element)
    {
      for (const tinyxml2::XMLElement* componentElement : children(element, getItemElementName()))
      {
        std::unique_ptr<T> converter(new T(componentElement->Name()));
        if (converter->convertFromXML(componentElement))
        {
          m_items.push_back(converter.release());
        }
        else
        {
          ASSERT_FAIL();
          return false;
        }
      }

      return !m_items.empty() || !isRequired();
    }

    //------------------------------------------------------------------------------------------------
    // Child GameObject/Prefab specialization
    template <>
    class DataConverterListElement<GameObjectDataConverter> : public Element
    {
      public:
        using Items = std::vector<GameObjectDataConverter*>;

        CelesteDllExport ~DataConverterListElement() override;

        const Items& getItems() const { return m_items; }

        void clear() { m_items.clear(); }

        typename Items::const_iterator begin() const { return m_items.cbegin(); }
        typename Items::const_iterator end() const { return m_items.cend(); }

        CelesteDllExport DataConverterListElement<GameObjectDataConverter>* clone() const override;

        static constexpr bool isReference() { return false; }

  #if _DEBUG
        void generateBinding(std::string& /*output*/) const override { }
  #endif

        CelesteDllExport static const char* const GAME_OBJECT_ELEMENT_NAME;
        CelesteDllExport static const char* const PREFAB_ELEMENT_NAME;

      protected:
        DataConverterListElement(const DataConverterListElement&) = delete;
        DataConverterListElement& operator=(const DataConverterListElement&) = delete;

        CelesteDllExport bool doConvertFromXML(const tinyxml2::XMLElement* element) override;

      private:
        using Inherited = Element;

        DataConverterListElement(
          const std::string& elementName,
          DeserializationRequirement required = DeserializationRequirement::kNotRequired) :
          Element(elementName, required),
          m_items()
        {
        }

        Items m_items;

        friend class Celeste::XML::XMLObjectFactory;
    };

    //------------------------------------------------------------------------------------------------
    // Component specialization
    template <>
    class DataConverterListElement<ComponentDataConverter> : public Element
    {
      public:
        using Items = std::vector<ComponentDataConverter*>;

        CelesteDllExport ~DataConverterListElement() override;

        const Items& getItems() const { return m_items; }

        void clear() { m_items.clear(); }

        typename Items::const_iterator begin() const { return m_items.cbegin(); }
        typename Items::const_iterator end() const { return m_items.cend(); }

        CelesteDllExport DataConverterListElement<ComponentDataConverter>* clone() const override;

        static constexpr bool isReference() { return false; }

  #if _DEBUG
        void generateBinding(std::string& /*output*/) const override { }
  #endif

      protected:
        DataConverterListElement(const DataConverterListElement&) = default;
        DataConverterListElement& operator=(const DataConverterListElement&) = default;

        CelesteDllExport bool doConvertFromXML(const tinyxml2::XMLElement* element) override;

      private:
        using Inherited = Element;

        DataConverterListElement(
          const std::string& elementName,
          DeserializationRequirement required = DeserializationRequirement::kNotRequired) :
          Element(elementName, required),
          m_items()
        {
        }

        Items m_items;

        friend class Celeste::XML::XMLObjectFactory;
    };
  }
}