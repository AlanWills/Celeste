#pragma once

#include "tinyxml2.h"
#include "Assert/Assert.h"

#include <string>


namespace Celeste
{
  class Field
  {
    public:
      virtual ~Field() = default;

      const std::string& getName() const { return m_name; }

      //------------------------------------------------------------------------------------------------
      bool deserialize(const tinyxml2::XMLElement* element)
      {
        if (element == nullptr)
        {
          ASSERT_FAIL();
          return false;
        }

        return doDeserialize(element);
      }

      //------------------------------------------------------------------------------------------------
      tinyxml2::XMLElement* serialize(tinyxml2::XMLElement* element) const
      {
        if (element == nullptr)
        {
          ASSERT_FAIL();
          return element;
        }

        doSerialize(element);
        return element;
      }

    protected:
      Field(const std::string& name) : m_name(name) { }
      Field(const Field&) = default;
      Field& operator=(const Field&) = default;

      virtual bool doDeserialize(const tinyxml2::XMLElement* element) = 0;
      virtual void doSerialize(tinyxml2::XMLElement* element) const = 0;

    private:
      std::string m_name;

      friend class ScriptableObject;
  };
}