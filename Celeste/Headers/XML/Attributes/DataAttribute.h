#pragma once

#include "Attribute.h"
#include "Deserialization/Deserializers.h"
#include "Templates/ChooseClass.h"
#include "Bindings/DataBindingGenerators.h"


namespace Celeste
{
  namespace XML
  {
    class XMLObjectFactory;

    template <typename T, bool is_reference = false>
    class DataAttribute : public Attribute
    {
      public:
        typedef typename choose_class<static_cast<bool>(is_reference), const T&, T>::type attribute_type;
        attribute_type getValue() const { return m_value; }

        DataAttribute<T, is_reference>* clone() const override;

        static constexpr bool isReference() { return is_reference; }

      protected:
        bool doConvertFromXML(const std::string& attributeText) override { return Celeste::deserialize<T>(attributeText, m_value); }

#if _DEBUG
        void generateBinding(std::string& output) const override;
#endif

      private:
        DataAttribute(const std::string& attributeName, attribute_type defaultValue = T(), DeserializationRequirement required = DeserializationRequirement::kNotRequired) :
          Attribute(attributeName, required),
          m_value(defaultValue)
        {
        }

        T m_value;

        friend class Celeste::XML::XMLObjectFactory;
    };

    //------------------------------------------------------------------------------------------------
    template <typename T, bool is_reference>
    DataAttribute<T, is_reference>* DataAttribute<T, is_reference>::clone() const
    {
      DataAttribute<T, is_reference>* clone = new DataAttribute<T, is_reference>(
        getAttributeName(), m_value, isRequired() ? DeserializationRequirement::kRequired : DeserializationRequirement::kNotRequired);

      return clone;
    }

#if _DEBUG
    //------------------------------------------------------------------------------------------------
    template <typename T, bool is_reference>
    void DataAttribute<T, is_reference>::generateBinding(std::string& output) const
    {
      Bindings::DataBindingGenerator<T, is_reference>::generateBinding(getAttributeName(), getValue(), output);
    }
#endif

    //------------------------------------------------------------------------------------------------
    // Alias templates for shorthand
    //------------------------------------------------------------------------------------------------
    template <typename T>
    using ValueAttribute = DataAttribute<T, false>;

    //------------------------------------------------------------------------------------------------
    template <typename T>
    using ReferenceAttribute = DataAttribute<T, true>;
  }
}