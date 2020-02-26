#pragma once

#include "tinyxml2.h"
#include "Debug/Assert.h"

#include <string>


namespace Celeste
{
  namespace Bindings
  {
    class BindingsGenerator;
  }

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

  #if _DEBUG
      virtual void generateBinding(std::string& output) const = 0;
  #endif

    private:
      std::string m_name;

      friend class ScriptableObject;
      friend class Bindings::BindingsGenerator;
  };
}