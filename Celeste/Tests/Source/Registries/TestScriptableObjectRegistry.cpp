#include "UtilityHeaders/UnitTestHeaders.h"

#include "Registries/ScriptableObjectRegistry.h"
#include "Mocks/Objects/MockScriptableObject.h"
#include "TestResources/Objects/MockScriptableObjectLoadingResources.h"
#include "AssertExt.h"
#include "FileAssert.h"


namespace TestCeleste
{
  namespace Registries
  {

    CELESTE_TEST_CLASS(TestScriptableObjectRegistry)

    //------------------------------------------------------------------------------------------------
    void TestScriptableObjectRegistry::testInitialize()
    {
      ScriptableObjectRegistry::removeScriptableObject<MockScriptableObject>();
    }

#pragma region Add Scriptable Object Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScriptableObjectRegistry_AddScriptableObject_ScriptableObjectDoesntExist_ReturnsTrue)
    {
      Assert::IsFalse(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());
      Assert::IsTrue(ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScriptableObjectRegistry_AddScriptableObject_ScriptableObjectDoesntExist_AddsToRegistry)
    {
      Assert::IsFalse(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());
      Assert::IsTrue(ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>());
      Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScriptableObjectRegistry_AddScriptableObject_ScriptableObjectExists_ReturnsFalse)
    {
      Assert::IsFalse(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());
      
      ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();
      
      Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());
      Assert::IsFalse(ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>());
    }

#pragma endregion

#pragma region Has Scriptable Object Tests
    
    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScriptableObjectRegistry_HasScriptableObject_InputtingType_NotRegistered_ReturnsFalse)
    {
      Assert::IsFalse(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScriptableObjectRegistry_HasScriptableObject_InputtingType_IsRegistered_ReturnsTrue)
    {
      Assert::IsFalse(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

      ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();

      Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScriptableObjectRegistry_HasScriptableObject_InputtingTypeName_NotRegistered_ReturnsFalse)
    {
      Assert::IsFalse(ScriptableObjectRegistry::hasScriptableObject(MockScriptableObject::type_name()));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScriptableObjectRegistry_HasScriptableObject_InputtingTypeName_IsRegistered_ReturnsTrue)
    {
      Assert::IsFalse(ScriptableObjectRegistry::hasScriptableObject(MockScriptableObject::type_name()));

      ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();

      Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject(MockScriptableObject::type_name()));
    }

#pragma endregion

#pragma region Remove Scriptable Object Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScriptableObjectRegistry_RemoveScriptableObject_InputtingType_NotRegistered_DoesNothing)
    {
      Assert::IsFalse(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

      ScriptableObjectRegistry::removeScriptableObject<MockScriptableObject>();

      Assert::IsFalse(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScriptableObjectRegistry_RemoveScriptableObject_InputtingType_Registered_DoesRemovesFromRegistry)
    {
      ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();

      Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

      ScriptableObjectRegistry::removeScriptableObject<MockScriptableObject>();

      Assert::IsFalse(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScriptableObjectRegistry_RemoveScriptableObject_InputtingTypeName_NotRegistered_DoesNothing)
    {
      Assert::IsFalse(ScriptableObjectRegistry::hasScriptableObject(MockScriptableObject::type_name()));

      ScriptableObjectRegistry::removeScriptableObject(MockScriptableObject::type_name());

      Assert::IsFalse(ScriptableObjectRegistry::hasScriptableObject(MockScriptableObject::type_name()));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScriptableObjectRegistry_RemoveScriptableObject_InputtingTypeName_Registered_DoesRemovesFromRegistry)
    {
      ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();

      Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject(MockScriptableObject::type_name()));

      ScriptableObjectRegistry::removeScriptableObject(MockScriptableObject::type_name());

      Assert::IsFalse(ScriptableObjectRegistry::hasScriptableObject(MockScriptableObject::type_name()));
    }

#pragma endregion

#pragma region Create Scriptable Object Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScriptableObjectRegistry_CreateScriptableObject_InputtingNonRegisteredType_DoesNothing)
    {
      Assert::IsFalse(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

      std::unique_ptr<MockScriptableObject> scriptableObject = ScriptableObjectRegistry::createScriptableObject<MockScriptableObject>("Test");

      AssertExt::IsNull(scriptableObject);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScriptableObjectRegistry_CreateScriptableObject_InputtingRegisteredType_CreatesNewScriptableObjectInstance)
    {
      ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();

      Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

      std::unique_ptr<MockScriptableObject> scriptableObject = ScriptableObjectRegistry::createScriptableObject<MockScriptableObject>("Test");

      AssertExt::IsNotNull(scriptableObject);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScriptableObjectRegistry_CreateScriptableObject_InputtingRegisteredType_SetsNewInstanceToInputtedName)
    {
      ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();

      Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

      std::unique_ptr<MockScriptableObject> scriptableObject = ScriptableObjectRegistry::createScriptableObject<MockScriptableObject>("Test");

      Assert::AreEqual("Test", scriptableObject->getName().c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScriptableObjectRegistry_CreateScriptableObject_InputtingNonRegisteredTypeName_DoesNothing)
    {
      Assert::IsFalse(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

      std::unique_ptr<ScriptableObject> scriptableObject = ScriptableObjectRegistry::createScriptableObject(MockScriptableObject::type_name(), "Test");

      AssertExt::IsNull(scriptableObject);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScriptableObjectRegistry_CreateScriptableObject_InputtingRegisteredTypeName_CreatesNewScriptableObjectInstance)
    {
      ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();

      Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

      std::unique_ptr<ScriptableObject> scriptableObject = ScriptableObjectRegistry::createScriptableObject(MockScriptableObject::type_name(), "Test");

      AssertExt::IsNotNull(scriptableObject);
      Assert::IsNotNull(dynamic_cast<MockScriptableObject*>(scriptableObject.get()));
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScriptableObjectRegistry_CreateScriptableObject_InputtingRegisteredTypeName_SetsNewInstanceToInputtedName)
    {
      ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();

      Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

      std::unique_ptr<ScriptableObject> scriptableObject = ScriptableObjectRegistry::createScriptableObject(MockScriptableObject::type_name(), "Test");

      Assert::AreEqual("Test", scriptableObject->getName().c_str());
    }

#pragma endregion

#pragma region Load Scriptable Object Tests

#pragma region Template Overload

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScriptableObjectRegistry_LoadScriptableObject_TemplateOverload_InputtingInvalidPath_ReturnsNullptr)
    {
      ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();

      Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

      std::unique_ptr<MockScriptableObject> scriptableObject = 
        ScriptableObjectRegistry::loadScriptableObject<MockScriptableObject>(Path("WubbaLubbaDubDub"));

      AssertExt::IsNull(scriptableObject);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScriptableObjectRegistry_LoadScriptableObject_TemplateOverload_InputtingValidPathToNonRegisteredScriptableObject_ReturnsNullptr)
    {
      Assert::IsFalse(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

      std::unique_ptr<MockScriptableObject> scriptableObject = ScriptableObjectRegistry::loadScriptableObject
        <MockScriptableObject>(MockScriptableObjectLoadingResources::getValidFullPath());

      AssertExt::IsNull(scriptableObject);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScriptableObjectRegistry_LoadScriptableObject_TemplateOverload_InputtingValidPathToRegisteredInvalidScriptableObject_ReturnsNullptr)
    {
      ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();

      Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

      std::unique_ptr<MockScriptableObject> scriptableObject = ScriptableObjectRegistry::loadScriptableObject
        <MockScriptableObject>(MockScriptableObjectLoadingResources::getInvalidFullPath());

      AssertExt::IsNull(scriptableObject);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScriptableObjectRegistry_LoadScriptableObject_TemplateOverload_InputtingValidPathToRegisteredValidScriptableObject_CreatesNewScriptableObjectInstance)
    {
      ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();

      Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

      std::unique_ptr<MockScriptableObject> scriptableObject = ScriptableObjectRegistry::loadScriptableObject
        <MockScriptableObject>(MockScriptableObjectLoadingResources::getValidFullPath());

      AssertExt::IsNotNull(scriptableObject);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScriptableObjectRegistry_LoadScriptableObject_TemplateOverload_InputtingValidPathToRegisteredValidScriptableObject_SetsNewScriptableObjectInstanceValues)
    {
      ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();

      Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

      std::unique_ptr<MockScriptableObject> scriptableObject = ScriptableObjectRegistry::loadScriptableObject
        <MockScriptableObject>(MockScriptableObjectLoadingResources::getValidFullPath());

      Assert::AreEqual("Valid", scriptableObject->getName().c_str());
      Assert::AreEqual("34b0d489-8485-4391-b3b9-b3f062e90c4a", scriptableObject->getGuid().str().c_str());
    }

#pragma endregion

#pragma region Non Template Overload

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScriptableObjectRegistry_LoadScriptableObject_NonTemplateOverload_InputtingInvalidPath_ReturnsNullptr)
    {
      ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();

      Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

      std::unique_ptr<ScriptableObject> scriptableObject = ScriptableObjectRegistry::loadScriptableObject(Path("WubbaLubbaDubDub"));

      AssertExt::IsNull(scriptableObject);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScriptableObjectRegistry_LoadScriptableObject_NonTemplateOverload_InputtingValidPathToNonRegisteredType_ReturnsNullptr)
    {
      Assert::IsFalse(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

      std::unique_ptr<ScriptableObject> scriptableObject = ScriptableObjectRegistry::loadScriptableObject
        (MockScriptableObjectLoadingResources::getInvalidFullPath());

      AssertExt::IsNull(scriptableObject);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScriptableObjectRegistry_LoadScriptableObject_NonTemplateOverload_InputtingValidPathToRegisteredInvalidScriptableObject_ReturnsNullptr)
    {
      ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();

      Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

      std::unique_ptr<ScriptableObject> scriptableObject = ScriptableObjectRegistry::loadScriptableObject
        (MockScriptableObjectLoadingResources::getInvalidFullPath());

      AssertExt::IsNull(scriptableObject);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScriptableObjectRegistry_LoadScriptableObject_NonTemplateOverload_InputtingValidPathToRegisteredValidScriptableObject_CreatesNewScriptableObjectInstance)
    {
      ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();

      Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

      std::unique_ptr<ScriptableObject> scriptableObject = ScriptableObjectRegistry::loadScriptableObject
        (MockScriptableObjectLoadingResources::getValidFullPath());

      AssertExt::IsNotNull(scriptableObject);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(ScriptableObjectRegistry_LoadScriptableObject_NonTemplateOverload_InputtingValidPathToRegisteredValidScriptableObject_SetsNewScriptableObjectInstanceValues)
    {
      ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();

      Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

      std::unique_ptr<ScriptableObject> scriptableObject = ScriptableObjectRegistry::loadScriptableObject
        (MockScriptableObjectLoadingResources::getValidFullPath());

      Assert::IsNotNull(dynamic_cast<MockScriptableObject*>(scriptableObject.get()));
      Assert::AreEqual("Valid", scriptableObject->getName().c_str());
      Assert::AreEqual("34b0d489-8485-4391-b3b9-b3f062e90c4a", scriptableObject->getGuid().str().c_str());
    }

#pragma endregion

#pragma endregion

#pragma region Generate All Bindings Tests
//
//    //------------------------------------------------------------------------------------------------
//    TEST_METHOD(ScriptableObjectRegistry_GenerateAllBindings_GeneratesBindingsForClasses)
//    {
//      Directory directory(Path(TempDirectory::getFullPath(), "Bindings"));
//      ScriptableObjectRegistry::generateAllBindings(directory);
//
//      std::vector<File> output;
//      directory.findFiles(output, ".", true);
//
//      Assert::AreEqual(ScriptableObjectRegistry::getBindingsMapConst().size(), output.size());
//    }
//
//    //------------------------------------------------------------------------------------------------
//    TEST_METHOD(ScriptableObjectRegistry_GenerateAllBindings_DoesntGenerateBindingsForClassesThatAlreadyHaveFiles)
//    {
//      Directory directory(Path(TempDirectory::getFullPath(), "Bindings"));
//
//      for (const std::pair<std::string, std::pair<std::string, ScriptableObjectRegistry::BindingsFactoryFunction>>& object : ScriptableObjectRegistry::getBindingsMapConst())
//      {
//        File file(Path(directory.getDirectoryPath(), object.first + ".cs"));
//        file.append("Test");
//      }
//
//      ScriptableObjectRegistry::generateAllBindings(directory);
//
//      std::vector<File> output;
//      directory.findFiles(output, ".", true);
//
//      Assert::AreEqual(ScriptableObjectRegistry::getBindingsMapConst().size(), output.size());
//
//      for (const File& file : output)
//      {
//        FileAssert::FileContentsEqual(file.getFilePath().as_string(), "Test");
//      }
//    }
//
//    //------------------------------------------------------------------------------------------------
//    TEST_METHOD(ScriptableObjectRegistry_GenerateAllBindings_InvokesCallbackForEachClass)
//    {
//      size_t counter = 0;
//      Directory directory(Path(TempDirectory::getFullPath(), "Bindings"));
//      ScriptableObjectRegistry::generateAllBindings(directory, [&counter](const std::string&, const Path&) -> void
//      {
//        ++counter;
//      });
//
//      std::vector<File> output;
//      directory.findFiles(output, ".", true);
//
//      Assert::AreEqual(ScriptableObjectRegistry::getBindingsMapConst().size(), output.size());
//      Assert::AreEqual(ScriptableObjectRegistry::getBindingsMapConst().size(), counter);
//    }
//
//#pragma endregion
//
//#pragma region Generate Bindings For Assembly Tests
//
//    //------------------------------------------------------------------------------------------------
//    TEST_METHOD(ScriptableObjectRegistry_GenerateBindingsForAssembly_GeneratesBindingsForClassesInNamespace)
//    {
//      Directory directory(Path(TempDirectory::getFullPath(), "Bindings"));
//      ScriptableObjectRegistry::generateBindingsForAssembly("Celeste", directory);
//
//      std::vector<File> output;
//      directory.findFiles(output, ".", true);
//
//      Assert::AreEqual(ScriptableObjectRegistry::getBindingsMapConst().size(), output.size());
//    }
//
//    //------------------------------------------------------------------------------------------------
//    TEST_METHOD(ScriptableObjectRegistry_GenerateBindingsForAssembly_DoesntGenerateBindingsForClassesNotInNamespace)
//    {
//      Directory directory(Path(TempDirectory::getFullPath(), "Bindings"));
//      ScriptableObjectRegistry::generateBindingsForAssembly("FakeAssembly", directory);
//
//      std::vector<File> output;
//      directory.findFiles(output, ".", true);
//
//      Assert::AreEqual(static_cast<size_t>(0), output.size());
//    }
//
//    //------------------------------------------------------------------------------------------------
//    TEST_METHOD(ScriptableObjectRegistry_GenerateBindingsForAssembly_DoesntGenerateBindingsForClassesThatAlreadyHaveFiles)
//    {
//      Directory directory(Path(TempDirectory::getFullPath(), "Bindings"));
//
//      for (const auto& pair : ScriptableObjectRegistry::getBindingsMapConst())
//      {
//        File file(Path(directory.getDirectoryPath(), pair.first + ".cs"));
//        file.append("Test");
//      }
//      
//      ScriptableObjectRegistry::generateBindingsForAssembly("Celeste", directory);
//
//      std::vector<File> output;
//      directory.findFiles(output, ".", true);
//
//      Assert::AreEqual(ScriptableObjectRegistry::getBindingsMapConst().size(), output.size());
//
//      for (const File& file : output)
//      {
//        FileAssert::FileContentsEqual(file.getFilePath().as_string(), "Test");
//      }
//    }
//
//    //------------------------------------------------------------------------------------------------
//    TEST_METHOD(ScriptableObjectRegistry_GenerateBindingsForAssembly_InvokesCallbackForEachClassInNamespace)
//    {
//      size_t counter = 0;
//      Directory directory(Path(TempDirectory::getFullPath(), "Bindings"));
//      ScriptableObjectRegistry::generateBindingsForAssembly("Celeste", directory, [&counter](const std::string&, const Path&) -> void
//      {
//        ++counter;
//      });
//
//      Assert::AreNotEqual(static_cast<size_t>(0), counter);
//      Assert::AreEqual(ScriptableObjectRegistry::getBindingsMapConst().size(), counter);
//
//      counter = 0;
//      directory.remove();
//      ScriptableObjectRegistry::generateBindingsForAssembly("FakeAssembly", directory, [&counter](const std::string&, const Path&) -> void
//      {
//        ++counter;
//      });
//
//      Assert::AreEqual(static_cast<size_t>(0), counter);
//    }

#pragma endregion

    };
  }
}