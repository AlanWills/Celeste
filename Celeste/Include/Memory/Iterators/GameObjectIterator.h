#pragma once

#include "Maths/Transform.h"

#include <iterator>
#include <vector>


namespace Celeste
{
  class GameObject;

  class GameObjectIterator : std::iterator<std::forward_iterator_tag, GameObject*>
  {
    public:
      GameObjectIterator(std::vector<Transform*>::const_iterator it) :
        m_it(it)
      {
      }

      inline GameObjectIterator& operator++() { ++m_it; return *this; }
      inline GameObjectIterator operator++(int) { return GameObjectIterator(++m_it); }

      inline bool operator==(const GameObjectIterator& other) const { return m_it == other.m_it; }
      inline bool operator!=(const GameObjectIterator& other) const { return !(*this == other); }

      inline GameObject* operator*() const { return (*m_it)->getGameObject(); }

    private:
      std::vector<Transform*>::const_iterator m_it;
  };
}