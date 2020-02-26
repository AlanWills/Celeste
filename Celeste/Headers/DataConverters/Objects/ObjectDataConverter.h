#pragma once

#include "DataConverters/DataConverter.h"
#include "XML/Attributes/DataAttribute.h"


namespace Celeste
{
  template <typename T>
  class ObjectDataConverter : public DataConverter
  {
    public:
      ObjectDataConverter(const std::string& name);
      ObjectDataConverter(const ObjectDataConverter<T>&);
      ObjectDataConverter& operator=(const ObjectDataConverter<T>&);
      ObjectDataConverter(ObjectDataConverter<T>&& rhs);
    
      void setValues(T& object) const;

    protected:
      virtual void doSetValues(T& object) const { }

    private:
      using Inherited = DataConverter;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  ObjectDataConverter<T>::ObjectDataConverter(const std::string& elementName) :
    Inherited(elementName)
  {
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  ObjectDataConverter<T>::ObjectDataConverter(const ObjectDataConverter<T>& rhs) :
    Inherited(rhs)
  {
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  ObjectDataConverter<T>::ObjectDataConverter(ObjectDataConverter<T>&& rhs) :
    Inherited(std::move(rhs))
  {
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  ObjectDataConverter<T>& ObjectDataConverter<T>::operator=(const ObjectDataConverter<T>& rhs)
  {
    if (this == &rhs)
    {
      // Self assignment guard
      return *this;
    }

    Inherited::operator=(rhs);

    return *this;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void ObjectDataConverter<T>::setValues(T& object) const
  {
    if (!isDataLoadedCorrectly())
    {
      ASSERT_FAIL();
      return;
    }

    doSetValues(object);
  }
}