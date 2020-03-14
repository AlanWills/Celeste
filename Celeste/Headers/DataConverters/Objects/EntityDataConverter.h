#pragma once

#include "DataConverters/Objects/ObjectDataConverter.h"
#include "XML/Attributes/DataAttribute.h"


namespace Celeste
{
  template <typename T>
  class EntityDataConverter : public ObjectDataConverter<T>
  {
    public:
      EntityDataConverter(const std::string& name);
      EntityDataConverter(const EntityDataConverter<T>&);
      EntityDataConverter& operator=(const EntityDataConverter<T>&);
      EntityDataConverter(EntityDataConverter<T>&& rhs);

      inline bool getIsActive() const { return m_isActive->getValue(); }

      static const char* const IS_ACTIVE_ATTRIBUTE_NAME;

    protected:
      void doSetValues(T& entity) const override;

    private:
      using Inherited = ObjectDataConverter<T>;

      observer_ptr<XML::ValueAttribute<bool>> m_isActive;
  };

  template <typename T>
  const char* const EntityDataConverter<T>::IS_ACTIVE_ATTRIBUTE_NAME("active");

  //------------------------------------------------------------------------------------------------
  template <typename T>
  EntityDataConverter<T>::EntityDataConverter(const std::string& elementName) :
    Inherited(elementName),
    m_isActive(&Inherited::createValueAttribute(IS_ACTIVE_ATTRIBUTE_NAME, true))
  {
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  EntityDataConverter<T>::EntityDataConverter(const EntityDataConverter<T>& rhs) :
    Inherited(rhs),
    m_isActive(reinterpret_cast<XML::ValueAttribute<bool>*>(Inherited::findAttribute(IS_ACTIVE_ATTRIBUTE_NAME)))
  {
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  EntityDataConverter<T>::EntityDataConverter(EntityDataConverter<T>&& rhs) :
    Inherited(std::move(rhs)),
    m_isActive(std::move(rhs.m_isActive))
  {
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  EntityDataConverter<T>& EntityDataConverter<T>::operator=(const EntityDataConverter<T>& rhs)
  {
    if (this == &rhs)
    {
      // Self assignment guard
      return *this;
    }

    Inherited::operator=(rhs);
    auto attribute = Inherited::findAttribute(IS_ACTIVE_ATTRIBUTE_NAME);
    ASSERT_NOT_NULL(attribute);
    m_isActive = reinterpret_cast<XML::ValueAttribute<bool>*>(attribute);

    return *this;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void EntityDataConverter<T>::doSetValues(T& entity) const
  {
    entity.setActive(getIsActive());
  }
}