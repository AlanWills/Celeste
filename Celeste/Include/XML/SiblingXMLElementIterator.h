#pragma once

#include "tinyxml2.h"
#include "CelesteDllExport.h"
#include "Templates/ChooseClass.h"

#include <string>
#include <iterator>


namespace Celeste::XML
{
  template <bool is_const>
  class SiblingXMLElementIterator
  {
    public:
      using iterator_category = std::forward_iterator_tag;
      using value_type = tinyxml2::XMLElement;
      using difference_type = ptrdiff_t;
      using pointer = typename choose_class<is_const, const tinyxml2::XMLElement*, tinyxml2::XMLElement*>::type;
      using reference = typename choose_class<is_const, const tinyxml2::XMLElement&, tinyxml2::XMLElement&>::type;

      SiblingXMLElementIterator(pointer element, const std::string& name = "") :
        m_ptr(element),
        m_name(name)
      {
        if (element && !m_name.empty() && (name != element->Name()))
        {
          impl();
        }
      }

      ~SiblingXMLElementIterator() { }

      SiblingXMLElementIterator<is_const>& operator++()
      {
        impl();
        return *this;
      }

      SiblingXMLElementIterator<is_const> operator++(int)
      {
        impl();

        return SiblingXMLElementIterator<is_const>(m_ptr);
      }

      bool operator==(const SiblingXMLElementIterator<is_const>& other) const { return m_ptr == *other; }
      bool operator!=(const SiblingXMLElementIterator<is_const>& other) const { return !(*this == other); }

      pointer operator*() const { return m_ptr; }

    private:
      void impl()
      {
        m_ptr = m_ptr ? m_ptr->NextSiblingElement(m_name.empty() ? nullptr : m_name.c_str()) : nullptr;
      }

      pointer m_ptr;
      std::string m_name;
  };
}