#pragma once

#include "XML/XMLObject.h"
#include "XML/XMLEnums.h"
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
    //------------------------------------------------------------------------------------------------
    class Element : public XMLObject
    {
      public:
        virtual ~Element() { }
        virtual Element* clone() const = 0;

        bool convertFromXML(const tinyxml2::XMLElement* element)
        {
          if (element == nullptr)
          {
            ASSERT_FAIL();
            return false;
          }

          m_usingDefaultValue = !doConvertFromXML(element);
          return !m_usingDefaultValue;
        }

        const std::string& getElementName() const { return m_elementName; }

        /// A flag to indicate whether this element has a value that was converted or
        /// is using it's default value because it was missing or invalid.
        bool isUsingDefaultValue() const { return m_usingDefaultValue; }

      protected:
        Element(const std::string& elementName, DeserializationRequirement required = DeserializationRequirement::kNotRequired) :
          XMLObject(required),
          m_elementName(elementName),
          m_usingDefaultValue(true)
        {
        }

        virtual bool doConvertFromXML(const tinyxml2::XMLElement* childElement) = 0;

#if _DEBUG
        virtual void generateBinding(std::string& output) const = 0;
#endif

      private:
        std::string m_elementName;
        bool m_usingDefaultValue;

        friend class Bindings::BindingsGenerator;
    };
  }
}