#pragma once

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Celeste
{
  class GameObject;
  class Path;
}

namespace CelesteTestUtils
{
  class AssertCel
  {
    public:
      //------------------------------------------------------------------------------------------------
      // HasComponent
      template <typename T>
      static inline void HasComponent(Celeste::GameObject const &gameObject) { Assert::IsTrue(gameObject.hasComponent<T>()); }

      template <typename T>
      static inline void HasComponent(Celeste::GameObject* const gameObject) { Assert::IsTrue(gameObject->hasComponent<T>()); }

      //------------------------------------------------------------------------------------------------
      // DoesNotHaveComponent
      template <typename T>
      static inline void DoesNotHaveComponent(Celeste::GameObject const &gameObject) { Assert::IsFalse(gameObject.hasComponent<T>()); }

      template <typename T>
      static inline void DoesNotHaveComponent(Celeste::GameObject* const gameObject) { Assert::IsFalse(gameObject->hasComponent<T>()); }

      //------------------------------------------------------------------------------------------------
      // IsActive
      template <typename T>
      static inline void IsActive(T const &entity) { Assert::IsTrue(entity.isActive()); }

      template <typename T>
      static inline void IsActive(T* const entity) { Assert::IsTrue(entity->isActive()); }
      
      //------------------------------------------------------------------------------------------------
      // IsNotActive
      template <typename T>
      static inline void IsNotActive(T const &entity) { Assert::IsFalse(entity.isActive()); }

      template <typename T>
      static inline void IsNotActive(T* const entity) { Assert::IsFalse(entity->isActive()); }
  };
}