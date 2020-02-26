#pragma once


namespace Celeste
{
  class Component;
  class GameObject;
}

namespace CelesteTestUtils
{
  template <typename T>
  class AutoDeallocator
  {
    public:
      AutoDeallocator(T* object) :
        m_object(object)
      {
      }

      ~AutoDeallocator();

      T* operator->() const
      {
        return m_object;
      }

      T& operator*() const
      {
        return *m_object;
      }

      T* get() const { return m_object; }

    private:
      T* m_object;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  AutoDeallocator<T>::~AutoDeallocator()
  {
    if (m_object != nullptr)
    {
      T::deallocate(*m_object);
    }
  }

  //------------------------------------------------------------------------------------------------
  template <>
  class AutoDeallocator<Celeste::Component>
  {
    public:
      AutoDeallocator(Celeste::Component* component) :
        m_object(component)
      {
      }

      ~AutoDeallocator();

      Celeste::Component* operator->() const
      {
        return m_object;
      }

      Celeste::Component& operator*() const
      {
        return *m_object;
      }

      Celeste::Component* get() const { return m_object; }

    private:
      Celeste::Component* m_object;
  };

  //------------------------------------------------------------------------------------------------
  template <>
  class AutoDeallocator<Celeste::GameObject>
  {
    public:
      AutoDeallocator(Celeste::GameObject* gameObject) :
        m_object(gameObject)
      {
      }

      ~AutoDeallocator();

      Celeste::GameObject* operator->() const
      {
        return m_object;
      }

      Celeste::GameObject& operator*() const
      {
        return *m_object;
      }

      Celeste::GameObject* get() const { return m_object; }

    private:
      Celeste::GameObject* m_object;
  };
}