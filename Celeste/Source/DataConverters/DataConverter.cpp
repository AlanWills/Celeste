#include "DataConverters/DataConverter.h"
#include "Resources/ResourceManager.h"
#include "Resources/ResourceUtils.h"

#include <cstddef>


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  DataConverter::DataConverter(const std::string& elementName) :
    m_elementName(elementName),
    m_dataLoadedCorrectly(false),
    m_attributes(),
    m_elements()
  {
  }

  //------------------------------------------------------------------------------------------------
  DataConverter::~DataConverter()
  {
    for (XML::Attribute* attribute : m_attributes)
    {
      delete attribute;
    }

    for (XML::Element* element : m_elements)
    {
      delete element;
    }
  }

  //------------------------------------------------------------------------------------------------
  DataConverter::DataConverter(const DataConverter& rhs) :
    m_elementName(rhs.m_elementName),
    m_dataLoadedCorrectly(rhs.m_dataLoadedCorrectly),
    m_attributes(),
    m_elements()
  {
    copyDataFrom(rhs);
  }

  //------------------------------------------------------------------------------------------------
  DataConverter::DataConverter(DataConverter&& rhs) noexcept :
    m_elementName(std::move(rhs.m_elementName)),
    m_dataLoadedCorrectly(std::move(rhs.m_dataLoadedCorrectly)),
    m_attributes(std::move(rhs.m_attributes)),
    m_elements(std::move(rhs.m_elements))
  {
  }

  //------------------------------------------------------------------------------------------------
  DataConverter& DataConverter::operator=(const DataConverter& rhs)
  {
    if (this == &rhs)
    {
      // Self assignment guard
      return *this;
    }

    m_elementName = rhs.m_elementName;
    m_dataLoadedCorrectly = rhs.m_dataLoadedCorrectly;
    cleanupData();
    copyDataFrom(rhs);

    return *this;
  }

  //------------------------------------------------------------------------------------------------
  bool DataConverter::convertFromXML(const XMLElement* element)
  {
    if (element == nullptr)
    {
      ASSERT_FAIL();
      m_dataLoadedCorrectly = false;
      return m_dataLoadedCorrectly;
    }

    for (XML::Attribute* attribute : m_attributes)
    {
      const tinyxml2::XMLAttribute* attr = element->FindAttribute(attribute->getAttributeName().c_str());
      if (attr == nullptr)
      {
        if (attribute->isRequired())
        {
          ASSERT_FAIL();
          return false;
        }
      }
      else if (!attribute->convertFromXML(attr))
      {
        ASSERT_FAIL();
        m_dataLoadedCorrectly = false;
        return m_dataLoadedCorrectly;
      }
    }

    for (XML::Element* e : m_elements)
    {
      const tinyxml2::XMLElement* ele = element->FirstChildElement(e->getElementName().c_str());
      if (ele == nullptr)
      {
        if (e->isRequired())
        {
          ASSERT_FAIL();
          return false;
        }
      }
      else if (!e->convertFromXML(ele))
      {
        ASSERT_FAIL();
        m_dataLoadedCorrectly = false;
        return m_dataLoadedCorrectly;
      }
    }

    m_dataLoadedCorrectly = doConvertFromXML(element);
    return m_dataLoadedCorrectly;
  }

  //------------------------------------------------------------------------------------------------
  bool DataConverter::convertFromXML(const Path& fullFilePath)
  {
    return convertFromXML(fullFilePath.as_string());
  }

  //------------------------------------------------------------------------------------------------
  bool DataConverter::convertFromXML(const std::string& fullFilePath)
  {
    if (!File::exists(fullFilePath))
    {
      ASSERT_FAIL();
      return false;
    }

    using namespace Celeste::Resources;

    observer_ptr<Resources::Data> data = getResourceManager().load<Data>(fullFilePath);
    if (data == nullptr)
    {
      ASSERT_FAIL();
      return false;
    }

    auto element = data->getDocument().FirstChildElement();

    if (data->getDocumentRoot() == nullptr)
    {
      ASSERT_FAIL();
      return false;
    }

    return convertFromXML(data->getDocumentRoot());
  }

  //------------------------------------------------------------------------------------------------
  observer_ptr<XML::Attribute> DataConverter::getAttribute(size_t index)
  {
    return index < getAttributesSize() ? m_attributes[index] : nullptr;
  }

  //------------------------------------------------------------------------------------------------
  observer_ptr<XML::Attribute> DataConverter::findAttribute(const std::string& name)
  {
    auto it = std::find_if(m_attributes.begin(), m_attributes.end(), [&name](XML::Attribute* data) -> bool
    {
      return data->getAttributeName() == name;
    });

    return it == m_attributes.end() ? nullptr : *it;
  }

  //------------------------------------------------------------------------------------------------
  observer_ptr<XML::Element> DataConverter::getElement(size_t index)
  {
    return index < getElementsSize() ? m_elements[index] : nullptr;
  }

  //------------------------------------------------------------------------------------------------
  observer_ptr<XML::Element> DataConverter::findElement(const std::string& name)
  {
    auto it = std::find_if(m_elements.begin(), m_elements.end(), [&name](XML::Element* element) -> bool
    {
      return element->getElementName() == name;
    });

    return it == m_elements.end() ? nullptr : *it;
  }

  //------------------------------------------------------------------------------------------------
  void DataConverter::copyDataFrom(const DataConverter& rhs)
  {
    for (size_t i = 0; i < rhs.getAttributesSize(); ++i)
    {
      addData(rhs.getAttribute(i)->clone());
    }

    for (size_t i = 0; i < rhs.getElementsSize(); ++i)
    {
      addData(rhs.getElement(i)->clone());
    }
  }

  //------------------------------------------------------------------------------------------------
  void DataConverter::cleanupData()
  {
    for (size_t i = 0; i < m_attributes.size(); ++i)
    {
      delete m_attributes[i];
    }
    m_attributes.clear();

    for (size_t i = 0; i < m_elements.size(); ++i)
    {
      delete m_elements[i];
    }
    m_elements.clear();
  }
}