#pragma once

#include "BaseUnitTest.h"
#include "CppUnitTest.h"
#include "AssertSpecialization/glm.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


#define ARE_PTRS_EQUAL(Type) \
namespace Microsoft::VisualStudio::CppUnitTestFramework { \
  template<> \
  inline std::wstring ToString<Type>(Type* element) \
  { \
    return std::to_wstring(reinterpret_cast<size_t>(element)); \
  } \
  template<> \
  inline std::wstring ToString<Type>(const Type* element) \
  { \
    return std::to_wstring(reinterpret_cast<size_t>(element)); \
  } \
  template<> \
  inline std::wstring ToString<Type>(const Type& element) \
  { \
    return std::to_wstring(reinterpret_cast<size_t>(&element)); \
  } \
}

namespace Celeste
{
  class GameObject;
  class Transform;
  class Component;
  class Screen;

  namespace Resources
  {
    class Texture2D;
    class Prefab;
    class Sound;
  }

  namespace Input
  {
    class MouseInteractionHandler;
  }
}

ARE_PTRS_EQUAL(Celeste::GameObject);
ARE_PTRS_EQUAL(Celeste::Transform);
ARE_PTRS_EQUAL(Celeste::Component);
ARE_PTRS_EQUAL(Celeste::Screen);
ARE_PTRS_EQUAL(Celeste::Resources::Texture2D);
ARE_PTRS_EQUAL(Celeste::Resources::Prefab);
ARE_PTRS_EQUAL(Celeste::Resources::Sound);
ARE_PTRS_EQUAL(Celeste::Input::MouseInteractionHandler);

namespace CelesteTestUtils
{
  class CelesteUnitTest : public TestUtils::BaseUnitTest
  {
    public:
      CelesteUnitTest() { }
      virtual ~CelesteUnitTest() noexcept(false) { }

  #define CELESTE_TEST_CLASS(ClassName) \
    TEST_CLASS(ClassName), public CelesteUnitTest \
    { \
      public:\
      \
      TEST_CLASS_INITIALIZE(ClassName##_TestClassInitialize) \
      { \
        celesteTestClassInitialize(); \
        ClassName::testClassInitialize(); \
      } \
      TEST_CLASS_CLEANUP(ClassName##_TestClassCleanup) \
      { \
        celesteTestClassCleanup(); \
        ClassName::testClassCleanup(); \
      } \
      TEST_METHOD_INITIALIZE(ClassName##_TestMethodInitialize) \
      { \
        resetState(); \
        testInitializeCaller(); \
      } \
      TEST_METHOD_CLEANUP(ClassName##_TestMethodCleanup) \
      { \
        resetState(); \
        testCleanupCaller(); \
      }

    protected:
      static void celesteTestClassInitialize();
      static void celesteTestClassCleanup();

      void resetState();
      void resetResources();
      void resetMouse();
      void resetKeyboard();
      void resetLuaGlobals();
  };
}