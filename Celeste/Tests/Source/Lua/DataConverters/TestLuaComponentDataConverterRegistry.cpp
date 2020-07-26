#include "Lua/DataConverters/LuaComponentDataConverterRegistry.h"
#include "Lua/LuaState.h"

#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"
#include "TestUtils/Assert/AssertExt.h"

using namespace Celeste;
using namespace Celeste::Lua;


namespace TestCeleste::Lua
{
  CELESTE_TEST_CLASS(TestLuaComponentDataConverterRegistry)

    //------------------------------------------------------------------------------------------------
    void testInitialize()
  {
    LuaComponentDataConverterRegistry::clear();
  }

  //------------------------------------------------------------------------------------------------
  void testCleanup()
  {
    LuaComponentDataConverterRegistry::clear();
  }

#pragma region Register Converter Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverterRegistry_RegisterConverter_InputtingNonExistentName_ValidTable_AddsComponentToRegistry)
  {
    Assert::AreEqual(static_cast<size_t>(0), LuaComponentDataConverterRegistry::registeredConvertersSize());

    LuaComponentDataConverterRegistry::registerConverter("Test", LuaState::instance().create_table());

    Assert::AreEqual(static_cast<size_t>(1), LuaComponentDataConverterRegistry::registeredConvertersSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverterRegistry_RegisterConverter_InputtingExistentName_ValidTable_DoesNothing)
  {
    Assert::AreEqual(static_cast<size_t>(0), LuaComponentDataConverterRegistry::registeredConvertersSize());

    LuaComponentDataConverterRegistry::registerConverter("Test", LuaState::instance().create_table());

    Assert::AreEqual(static_cast<size_t>(1), LuaComponentDataConverterRegistry::registeredConvertersSize());

    LuaComponentDataConverterRegistry::registerConverter("Test", sol::table());

    Assert::AreEqual(static_cast<size_t>(1), LuaComponentDataConverterRegistry::registeredConvertersSize());
  }

#pragma endregion

#pragma region Deregister Converter Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverterRegistry_DeregisterConverter_InputtingNonExistentName_DoesNothing)
  {
    Assert::AreEqual(static_cast<size_t>(0), LuaComponentDataConverterRegistry::registeredConvertersSize());

    LuaComponentDataConverterRegistry::deregisterConverter("Test");

    Assert::AreEqual(static_cast<size_t>(0), LuaComponentDataConverterRegistry::registeredConvertersSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverterRegistry_DeregisterConverter_InputtingExistentName_RemovesFromRegistry)
  {
    Assert::AreEqual(static_cast<size_t>(0), LuaComponentDataConverterRegistry::registeredConvertersSize());

    LuaComponentDataConverterRegistry::registerConverter("Test", LuaState::instance().create_table());

    Assert::AreEqual(static_cast<size_t>(1), LuaComponentDataConverterRegistry::registeredConvertersSize());

    LuaComponentDataConverterRegistry::deregisterConverter("Test");

    Assert::AreEqual(static_cast<size_t>(0), LuaComponentDataConverterRegistry::registeredConvertersSize());
  }

#pragma endregion

#pragma region Clear Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverterRegistry_Clear_NoRegisteredComponents_DoesNothing)
  {
    Assert::AreEqual(static_cast<size_t>(0), LuaComponentDataConverterRegistry::registeredConvertersSize());

    LuaComponentDataConverterRegistry::clear();

    Assert::AreEqual(static_cast<size_t>(0), LuaComponentDataConverterRegistry::registeredConvertersSize());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverterRegistry_Clear_WithRegisteredComponents_RemovesAllRegisteredComponents)
  {
    Assert::AreEqual(static_cast<size_t>(0), LuaComponentDataConverterRegistry::registeredConvertersSize());

    LuaComponentDataConverterRegistry::registerConverter("Test", LuaState::instance().create_table());
    LuaComponentDataConverterRegistry::registerConverter("Test2", LuaState::instance().create_table());

    Assert::AreEqual(static_cast<size_t>(2), LuaComponentDataConverterRegistry::registeredConvertersSize());

    LuaComponentDataConverterRegistry::clear();

    Assert::AreEqual(static_cast<size_t>(0), LuaComponentDataConverterRegistry::registeredConvertersSize());
  }

#pragma endregion

#pragma region Has Converter Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverterRegistry_HasConverter_InputtingExistentName_ReturnsTrue)
  {
    Assert::AreEqual(static_cast<size_t>(0), LuaComponentDataConverterRegistry::registeredConvertersSize());

    LuaComponentDataConverterRegistry::registerConverter("Test", LuaState::instance().create_table());

    Assert::AreEqual(static_cast<size_t>(1), LuaComponentDataConverterRegistry::registeredConvertersSize());
    Assert::IsTrue(LuaComponentDataConverterRegistry::hasConverter("Test"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverterRegistry_HasConverter_InputtingNonExistentName_ReturnsFalse)
  {
    Assert::AreEqual(static_cast<size_t>(0), LuaComponentDataConverterRegistry::registeredConvertersSize());
    Assert::IsFalse(LuaComponentDataConverterRegistry::hasConverter("Test"));
  }

#pragma endregion

#pragma region Get Converter Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverterRegistry_GetConverter_InputtingExistentName_CreatesInstanceOfConverter)
  {
    Assert::AreEqual(static_cast<size_t>(0), LuaComponentDataConverterRegistry::registeredConvertersSize());

    LuaComponentDataConverterRegistry::registerConverter("Test", LuaState::instance().create_table());

    Assert::IsTrue(LuaComponentDataConverterRegistry::hasConverter("Test"));

    std::unique_ptr<ComponentDataConverter> converter;
    LuaComponentDataConverterRegistry::getConverter("Test", converter);

    AssertExt::IsNotNull(converter);
    Assert::AreEqual("Test", converter->getElementName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LuaComponentDataConverterRegistry_GetConverter_InputtingNonExistentName_DoesNothing)
  {
    Assert::AreEqual(static_cast<size_t>(0), LuaComponentDataConverterRegistry::registeredConvertersSize());
    Assert::IsFalse(LuaComponentDataConverterRegistry::hasConverter("Test"));

    std::unique_ptr<ComponentDataConverter> converter;
    LuaComponentDataConverterRegistry::getConverter("Test", converter);

    AssertExt::IsNull(converter);
  }

#pragma endregion

  };
}