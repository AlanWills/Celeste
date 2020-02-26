#pragma once

#include "Objects/Entity.h"


namespace CelesteTestUtils
{
  template <typename T>
  class AutoKiller
  {
    public:
      AutoKiller(observer_ptr<T> object) : m_object(object)
      {
        STATIC_ASSERT((std::is_base_of<Celeste::Entity, T>::value), "Inputted type for auto killer does not derive from Entity");
      }

      ~AutoKiller()
      {
        if (m_object != nullptr && m_object->isAlive())
        {
          m_object->die();
        }
      }

      observer_ptr<T> operator->() const
      {
        return m_object;
      }

      observer_ptr<T> get() const { return m_object; }

    private:
      observer_ptr<T> m_object;
  };
}