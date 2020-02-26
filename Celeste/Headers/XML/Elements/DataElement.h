#pragma once

#include "Element.h"
#include "XML/tinyxml2_ext.h"
#include "Templates/ChooseClass.h"
#include "Bindings/DataBindingGenerators.h"


namespace Celeste
{
  namespace XML
  {
    class XMLObjectFactory;

    template <typename T, bool is_reference>
    class DataElement : public Element
    {
      public:
        typedef typename choose_class<static_cast<bool>(is_reference), const T&, T>::type element_type;
        
        DataElement<T, is_reference>* clone() const override;

        element_type getValue() const { return m_value; }

        static constexpr bool isReference() { return is_reference; }

      protected:
        bool doConvertFromXML(const tinyxml2::XMLElement* element) override 
        { 
          XMLValueError result = getElementData<T>(element, m_value);
          return result == XML::XMLValueError::kSuccess || (result == XML::XMLValueError::kDoesNotExist && !isRequired());
        }

  #if _DEBUG
        void generateBinding(std::string& output) const override 
        { 
          Bindings::DataBindingGenerator<T, is_reference>::generateBinding(getElementName(), getValue(), output);
        }
  #endif

      private:
        DataElement(const std::string& attributeName, element_type defaultValue = T(), DeserializationRequirement required = DeserializationRequirement::kNotRequired) :
          Element(attributeName, required),
          m_value(defaultValue)
        {
        }

        T m_value;

        friend class Celeste::XML::XMLObjectFactory;
    };

    //------------------------------------------------------------------------------------------------
    template <typename T, bool is_reference>
    DataElement<T, is_reference>* DataElement<T, is_reference>::clone() const
    {
      DataElement<T, is_reference>* clone = new DataElement<T, is_reference>(
        getElementName(), m_value, isRequired() ? DeserializationRequirement::kRequired : DeserializationRequirement::kNotRequired);

      return clone;
    }

    //------------------------------------------------------------------------------------------------
    // Alias templates for shorthand
    //------------------------------------------------------------------------------------------------
    template <typename T>
    using ValueElement = DataElement<T, false>;

    //------------------------------------------------------------------------------------------------
    template <typename T>
    using ReferenceElement = DataElement<T, true>;
  }
}