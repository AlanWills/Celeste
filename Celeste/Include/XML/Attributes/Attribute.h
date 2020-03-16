#pragma once

#include "XML/XMLEnums.h"
#include "XML/XMLObject.h"
#include "Debug/Assert.h"

#include <string>


namespace Celeste
{
  namespace Bindings
  {
    class BindingsGenerator;
  }

  namespace XML
  {
    class Attribute : public XMLObject
    {
      public:
        virtual ~Attribute() { }
        virtual Attribute* clone() const = 0;

        bool convertFromXML(const tinyxml2::XMLAttribute* attribute)
        {
          if (attribute == nullptr)
          {
            ASSERT_FAIL();
            return false;
          }

          const char* text = attribute->Value();
          if (text == nullptr)
          {
            ASSERT_FAIL();
            return false;
          }

          m_usingDefaultValue = !doConvertFromXML(text);
          return !m_usingDefaultValue;
        }

        const std::string& getAttributeName() const { return m_attributeName; }

        /// A flag to indicate whether this attribute had a valid value that it converted
        /// or is using it's default value because it was missing or had an invalid value.
        bool isUsingDefaultValue() const { return m_usingDefaultValue; }

      protected:
        Attribute(const std::string& attributeName, DeserializationRequirement required = DeserializationRequirement::kNotRequired) :
          XMLObject(required),
          m_attributeName(attributeName),
          m_usingDefaultValue(true)
        {
        }

        virtual bool doConvertFromXML(const std::string& attributeText) = 0;

#if _DEBUG
        virtual void generateBinding(std::string& output) const = 0;
#endif

      private:
        std::string m_attributeName;
        bool m_usingDefaultValue;

        friend class Bindings::BindingsGenerator;
    };
  }
}