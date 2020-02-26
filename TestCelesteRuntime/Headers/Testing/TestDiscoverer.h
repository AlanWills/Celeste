#pragma once

#include "TestCERuntimeDllExport.h"
#include "Objects/Script.h"
#include "Memory/Handle.h"
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
        void onSetGameObject(const Celeste::Handle<Celeste::GameObject>& gameObject) override;
        void onDeath() override;

      private:
        using Inherited = Celeste::Script;

        Celeste::Handle<Celeste::GameObject> createTestClassesContainer(const Celeste::Handle<Celeste::GameObject>& parent);
        Celeste::Handle<Celeste::GameObject> createTestClass(sol::table testClass, const std::string& testClassName, const Celeste::Handle<Celeste::GameObject>& parent);
        Celeste::Handle<Celeste::GameObject> createUnitTestsContainer(sol::table testClass, const std::string& testClassName, const Celeste::Handle<Celeste::GameObject>& parent);
        Celeste::Handle<Celeste::GameObject> createUnitTest(const std::string& testName, const Celeste::Handle<Celeste::GameObject>& parent);

        void testClassInitialize();
        void testClassCleanup();
        void testInitialize(const sol::table& testClass);
        void testCleanup(const sol::table& testClass);
        void resetState();

        Celeste::Handle<Celeste::GameObject> m_testClassesContainer;
        Celeste::Handle<Celeste::GameObject> m_testsContainer;
    };
  }
}