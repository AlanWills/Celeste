#include "Testing/TestDiscoverer.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Resources/ResourceManager.h"
#include "Screens/ScreenManager.h"
#include "Screens/Screen.h"
#include "Physics/RectangleCollider.h"
#include "Rendering/TextRenderer.h"
#include "Rendering/SpriteRenderer.h"
#include "Resources/TestResources.h"

#include "Input/InputUtils.h"
#include "Input/Mouse.h"
#include "Input/Keyboard.h"
#include "Input/KeyboardTransformer.h"
#include "Input/MouseInteractionHandler.h"

#include "UI/StackPanel.h"
#include "UI/Button.h"

using namespace Celeste::Resources;
using namespace Celeste::UI;
using namespace Celeste::Physics;
using namespace Celeste::Rendering;
using namespace Celeste::Input;


namespace TestCelesteRuntime
{
  namespace Testing
  {
    REGISTER_SCRIPT(TestDiscoverer, 1)

    //------------------------------------------------------------------------------------------------
    TestDiscoverer::TestDiscoverer() :
      m_testClassesContainer(),
      m_testsContainer()
    {
    }

    //------------------------------------------------------------------------------------------------
    void TestDiscoverer::onSetGameObject(const Handle<GameObject>& gameObject)
    {
      Inherited::onSetGameObject(gameObject);

      Directory testDirectory(Path(getResourcesDirectory(), "Scripts", "Tests"));
      std::vector<File> testLuaFiles;
      testDirectory.findFiles(testLuaFiles, ".lua", true);

      Handle<Screen> screen = gameObject->getScreen();
      Handle<GameObject> canvasGameObject = screen->findGameObject("Canvas");
      m_testClassesContainer = screen->findGameObject("TestClassesContainer");
      m_testsContainer = screen->findGameObject("TestsContainer");

      for (const File& testLuaFile : testLuaFiles)
      {
        sol::protected_function_result result = Lua::LuaState::scriptFile(testLuaFile.getFilePath());
        if (result.valid())
        {
          sol::table testClass = result.get<sol::table>();
          std::string testClassName = testClass.get_or("name", testLuaFile.getExtensionlessFileName());

          Handle<GameObject> testClassGameObject = createTestClass(testClass, testClassName, m_testClassesContainer);
          m_testClassesContainer->findComponent<StackPanel>()->addChildren(testClassGameObject);

          Handle<GameObject> unitTestsGameObject = createUnitTestsContainer(testClass, testClassName, m_testsContainer);
        }
      }
    }

    //------------------------------------------------------------------------------------------------
    void TestDiscoverer::onDeath()
    {
      Inherited::onDeath();

      m_testClassesContainer.reset();
      m_testsContainer.reset();
    }

    //------------------------------------------------------------------------------------------------
    Handle<GameObject> TestDiscoverer::createTestClassesContainer(const Handle<GameObject>& parent)
    {
      Handle<GameObject> testClassesContainerGameObject = parent->getScreen()->allocateGameObject(parent->getTransform());
      testClassesContainerGameObject->getTransform()->setTranslation(getViewportDimensions().x * 0.25f, getViewportDimensions().y * 0.5f);

      Handle<StackPanel> stackPanel = testClassesContainerGameObject->addComponent<StackPanel>();
      stackPanel->setOrientation(Orientation::kVertical);
      stackPanel->setVerticalAlignment(VerticalAlignment::kTop);

      return testClassesContainerGameObject;
    }

    //------------------------------------------------------------------------------------------------
    Handle<GameObject> TestDiscoverer::createTestClass(sol::table testClass, const std::string& testClassName, const Handle<GameObject>& parent)
    {
      Handle<GameObject> testClassGameObject = parent->getScreen()->allocateGameObject(parent->getTransform());
      Handle<SpriteRenderer> testClassSpriteRenderer = testClassGameObject->addComponent<SpriteRenderer>();
      testClassGameObject->addComponent<RectangleCollider>();
      testClassGameObject->addComponent<MouseInteractionHandler>();

      Handle<GameObject> testClassGameObjectLabelGameObject = testClassGameObject->getScreen()->allocateGameObject(testClassGameObject->getTransform());
      Handle<TextRenderer> textRenderer = testClassGameObjectLabelGameObject->addComponent<TextRenderer>();
      textRenderer->addLine(testClassName);

      Handle<Button> runAllTestsButton = testClassGameObject->addComponent<Button>();
      runAllTestsButton->subscribeLeftClickCallback([testClass, this](EventArgs& e, const Handle<GameObject>& gameObject) -> void
      {
        // Clear Log
        Handle<TextRenderer> logRenderer = gameObject->getScreen()->findGameObject("LogText")->findComponent<TextRenderer>();
        logRenderer->clearLines();

        // Find the game object for this class
        Handle<GameObject> testClassGameObject = m_testsContainer->findChildGameObject(testClass.get<std::string>("name"));

        // Disable all other game objects except for those involved with this test class
        for (size_t i = 0; i < m_testsContainer->getChildCount(); ++i)
        {
          Handle<GameObject> child = m_testsContainer->getChildGameObject(i);
          child->setActive(child == testClassGameObject);
          child->setShouldRender(child == testClassGameObject);
        }

        // Test Class Initialize
        testClassInitialize();

        // Then create UI and run tests in alphabetical order
        for (size_t i = 0; i < testClassGameObject->getChildCount(); ++i)
        {
          Handle<GameObject> unitTestGameObject = testClassGameObject->getChildGameObject(i);
          std::string testName = deinternString(unitTestGameObject->getName());

          bool testPassed = true;

          // Test Initialize
          testInitialize(testClass);

          Handle<Screen> screen = Screen::allocate();
          const_cast<sol::table&>(testClass)["Screen"] = screen;

          // Run Test
          sol::protected_function_result unitTestResult = testClass[testName].get<sol::protected_function>().call();

          screen->deallocate();
          testPassed &= unitTestResult.valid();

          // Test Cleanup
          testCleanup(testClass);

          // Set label colour based on result
          unitTestGameObject->findComponent<TextRenderer>()->setColour(testPassed ? glm::vec4(0, 1, 0, 1) : glm::vec4(1, 0, 0, 1));

          if (!testPassed)
          {
            // Add log entry
			      sol::error err = unitTestResult;
			      std::string result = err.what();
            logRenderer->addLine(result);
			      LOG(result);
          }
        }

        // Test Class Cleanup
        testClassCleanup();
      });

      return testClassGameObject;
    }

    //------------------------------------------------------------------------------------------------
    Handle<GameObject> TestDiscoverer::createUnitTestsContainer(sol::table testClass, const std::string& testClassName, const Handle<GameObject>& parent)
    {
      Handle<GameObject> unitTestsContainerGameObject = parent->getScreen()->allocateGameObject(parent->getTransform());
      unitTestsContainerGameObject->getTransform()->setTranslation(0, getViewportDimensions().y * 0.45f);
      unitTestsContainerGameObject->setName(testClassName);

      Handle<StackPanel> stackPanel = unitTestsContainerGameObject->addComponent<StackPanel>();
      stackPanel->setOrientation(Orientation::kVertical);
      stackPanel->setVerticalAlignment(VerticalAlignment::kTop);

      Handle<KeyboardTransformer> keyboardTransformer = unitTestsContainerGameObject->addComponent<KeyboardTransformer>();
      keyboardTransformer->setTranslateUpKey(GLFW_KEY_UP);
      keyboardTransformer->setTranslateDownKey(GLFW_KEY_DOWN);
      keyboardTransformer->setTranslationSpeed(500);

      // Extract the test names
      std::vector<std::string> testNames;
      testClass.for_each([&](sol::object key, sol::object value) -> void
      {
        std::string testName = key.as<std::string>();

        if (value.is<sol::protected_function>() &&
          testName != "testInitialize" &&
          testName != "testCleanup")
        {
          testNames.push_back(testName);
        }
      });

      // Sort them alphabetically
      std::sort(testNames.begin(), testNames.end());

      for (const std::string& testName : testNames)
      {
        Handle<GameObject> unitTestGameObject = createUnitTest(testName, unitTestsContainerGameObject);
        stackPanel->addChildren(unitTestGameObject);
      }

      unitTestsContainerGameObject->setActive(false);
      unitTestsContainerGameObject->setShouldRender(false);

      return unitTestsContainerGameObject;
    }

    //------------------------------------------------------------------------------------------------
    Handle<GameObject> TestDiscoverer::createUnitTest(const std::string& testName, const Handle<GameObject>& parent)
    {
      Handle<GameObject> unitTestGameObject = parent->getScreen()->allocateGameObject(parent->getTransform());
      unitTestGameObject->setName(testName);

      Handle<TextRenderer> unitTestTextRenderer = unitTestGameObject->addComponent<TextRenderer>();
      unitTestTextRenderer->setHorizontalAlignment(HorizontalAlignment::kLeft);
      unitTestTextRenderer->addLine(testName);

      return unitTestGameObject;
    }

    //------------------------------------------------------------------------------------------------
    void TestDiscoverer::testClassInitialize()
    {
    }

    //------------------------------------------------------------------------------------------------
    void TestDiscoverer::testClassCleanup()
    {
    }

    //------------------------------------------------------------------------------------------------
    void TestDiscoverer::testInitialize(const sol::table& testClass)
    {
      resetState();

      sol::object testInitialize = testClass["testInitialize"];
      if (testInitialize.valid() && testInitialize.is<sol::protected_function>())
      {
        testInitialize.as<sol::protected_function>().call();
      }
    }

    //------------------------------------------------------------------------------------------------
    void TestDiscoverer::testCleanup(const sol::table& testClass)
    {
      resetState();

      sol::object testCleanup = testClass["testCleanup"];
      if (testCleanup.valid() && testCleanup.is<sol::protected_function>())
      {
        testCleanup.as<sol::protected_function>().call();
      }
    }

    //------------------------------------------------------------------------------------------------
    void TestDiscoverer::resetState()
    {
      Directory temp(CelesteTestUtils::TestResources::getTempDirectory());
      temp.remove();
      temp.create();

      getMouse().flush();
      getMouse().getTransform()->setTranslation(glm::vec3());
      
      getKeyboard().flush();
    }

    //------------------------------------------------------------------------------------------------
    std::unique_ptr<tinyxml2::XMLDocument> TestDiscoverer::executeTests()
    {
      std::unique_ptr<tinyxml2::XMLDocument> resultsDocument(new tinyxml2::XMLDocument());
      tinyxml2::XMLElement* testResultsElement = resultsDocument->NewElement("Results");
      resultsDocument->InsertFirstChild(testResultsElement);

      Directory testDirectory(Path(getResourcesDirectory(), "Scripts", "Tests"));
      std::vector<File> testLuaFiles;
      testDirectory.findFiles(testLuaFiles, ".lua", true);

      size_t totalPassed = 0;
      size_t totalFailed = 0;
      std::vector<std::string> passedTests;
      std::vector<std::string> failedTests;

      for (const File& testLuaFile : testLuaFiles)
      {
        sol::protected_function_result result = Lua::LuaState::scriptFile(testLuaFile.getFilePath());
        if (result.valid())
        {
          sol::table testClass = result.get<sol::table>();
          std::string testClassName = testClass.get_or("name", testLuaFile.getExtensionlessFileName());

          tinyxml2::XMLElement* testClassElement = resultsDocument->NewElement("TestClass");
          testClassElement->SetAttribute("name", testClassName.c_str());
          testResultsElement->InsertEndChild(testClassElement);

          // Set up containers for test names
          passedTests.clear();
          failedTests.clear();

          // Test Class Initialize
          testClassInitialize();

          // Obtain all the unit test names from the class
          testClass.for_each([&](sol::object key, sol::object value) -> void
          {
            std::string testName = key.as<std::string>();

            if (value.is<sol::protected_function>() &&
              testName != "testInitialize" &&
              testName != "testCleanup")
            {
              tinyxml2::XMLElement* testElement = resultsDocument->NewElement("Test");
              testElement->SetAttribute("name", testName.c_str());
              testClassElement->InsertEndChild(testElement);

              bool testPassed = true;

              // Test Initialize
              testInitialize(testClass);

              Handle<Screen> screen = Screen::allocate();
              const_cast<sol::table&>(testClass)["Screen"] = screen;

              // Run Test
              sol::protected_function_result unitTestResult = testClass[testName].get<sol::protected_function>().call();

              screen->deallocate();
              testPassed &= unitTestResult.valid();

              // Test Cleanup
              testCleanup(testClass);

              testElement->SetAttribute("passed", testPassed);

              // Add the test name to the appropriate list of names
              if (!testPassed)
              {
                // Add log entry
                sol::error err = unitTestResult;
                LOG(err.what());

                failedTests.push_back(testName);
                testElement->SetAttribute("error", err.what());
              }
              else
              {
                passedTests.push_back(testName);
              }
            }
          });

          // Test Class Cleanup
          testClassCleanup();

          // Now write the results of the class & update the running counts
          size_t passedTestsCount = passedTests.size();
          size_t failedTestsCount = failedTests.size();

          testClassElement->SetAttribute("total", static_cast<int>(passedTestsCount + failedTestsCount));
          testClassElement->SetAttribute("passed", static_cast<int>(passedTestsCount));
          testClassElement->SetAttribute("failed", static_cast<int>(failedTestsCount));

          totalPassed += passedTestsCount;
          totalFailed += failedTestsCount;
        }
      }

      testResultsElement->SetAttribute("total", static_cast<int>(totalPassed + totalFailed));
      testResultsElement->SetAttribute("passed", static_cast<int>(totalPassed));
      testResultsElement->SetAttribute("failed", static_cast<int>(totalFailed));

      return std::move(resultsDocument);
    }
  }
}