#pragma once

#include "TestCERuntimeDllExport.h"
#include "Objects/Script.h"
#include "Lua/LuaState.h"

#include <memory>


namespace tinyxml2
{
  class XMLDocument;
}

namespace Celeste
{
  class GameObject;
}

namespace TestCelesteRuntime
{
  namespace Testing
  {
    class TestDiscoverer : public Celeste::Script
    {
      DECLARE_SCRIPT(TestDiscoverer, TestCERuntimeDllExport)

      public:
        std::unique_ptr<tinyxml2::XMLDocument> executeTests();

      protected:
        void onSetGameObject(Celeste::GameObject& gameObject) override;

      private:
        using Inherited = Celeste::Script;

        observer_ptr<Celeste::GameObject> createTestClassesContainer(Celeste::GameObject& parent);
        observer_ptr<Celeste::GameObject> createTestClass(sol::table testClass, const std::string& testClassName, Celeste::GameObject& parent);
        observer_ptr<Celeste::GameObject> createUnitTestsContainer(sol::table testClass, const std::string& testClassName, Celeste::GameObject& parent);
        observer_ptr<Celeste::GameObject> createUnitTest(const std::string& testName, Celeste::GameObject& parent);

        void testClassInitialize();
        void testClassCleanup();
        void testInitialize(const sol::table& testClass);
        void testCleanup(const sol::table& testClass);
        void resetState();

        observer_ptr<Celeste::GameObject> m_testClassesContainer;
        observer_ptr<Celeste::GameObject> m_testsContainer;
    };
  }
}