#pragma once

#include "Maths/Transform.h"

#include <vector>
#include <iterator>


namespace Celeste
{
  class GameObject;

  class GameObjectIterator
  {
    public:
      using iterator_category = std::forward_iterator_tag;
      using value_type = GameObject*;
      using difference_type = ptrdiff_t;
      using pointer = value_type*;
      using reference = value_type&;

      GameObjectIterator(std::vector<Transform*>::const_iterator it) :
        m_it(it)
      {
      }

      inline GameObjectIterator& operator++() { ++m_it; return *this; }
      inline GameObjectIterator operator++(int) { return GameObjectIterator(++m_it); }

      inline bool operator==(const GameObjectIterator& other) const { return m_it == other.m_it; }
      inline bool operator!=(const GameObjectIterator& other) const { return !(*this == other); }

      inline value_type operator*() const { return (*m_it)->getGameObject(); }

    private:
      std::vector<Transform*>::const_iterator m_it;
  };
}