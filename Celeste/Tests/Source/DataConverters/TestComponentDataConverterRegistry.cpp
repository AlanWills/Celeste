#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Objects/GameObject.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Mocks/DataConverters/Objects/MockComponentDataConverter.h"
#include "Registries/ComponentRegistry.h"
#include "CelesteTestUtils/Assert/AssertCel.h"

using namespace Celeste;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestComponentDataConverterRegistry)

  //------------------------------------------------------------------------------------------------
  void testInitialize()
  {
    ComponentDataConverterRegistry::removeConverter<MockComponentDataConverter>();
  }

#pragma region Has Converter Tests

#pragma region Templated Parameter

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterRegistry_HasConverter_InputtingRegisteredType_ShouldReturnTrue)
  {
    Assert::IsTrue(ComponentDataConverterRegistry::addConverter<MockComponentDataConverter>());
    Assert::IsTrue(ComponentDataConverterRegistry::hasCustomConverter<MockComponentDataConverter>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterRegistry_HasConverter_InputtingUnregisteredType_ShouldReturnFalse)
  {
    Assert::IsFalse(ComponentDataConverterRegistry::hasCustomConverter<MockComponentDataConverter>());
  }

#pragma endregion

#pragma region String Parameter

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterRegistry_HasConverter_InputtingRegisteredTypeName_ShouldReturnTrue)
  {
    Assert::IsTrue(ComponentDataConverterRegistry::addConverter<MockComponentDataConverter>());
    Assert::IsTrue(ComponentDataConverterRegistry::hasCustomConverter(MockComponentDataConverter::ComponentType::type_name()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterRegistry_HasConverter_InputtingUnregisteredTypeName_ShouldReturnFalse)
  {
    Assert::IsFalse(ComponentDataConverterRegistry::hasCustomConverter("WubbaLubbaDubDub"));
  }

#pragma endregion

#pragma endregion

#pragma region Add Converter Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterRegistry_AddConverter_ConverterNotRegistered_AddsConverterToRegistry)
  {
    Assert::IsFalse(ComponentDataConverterRegistry::hasCustomConverter<MockComponentDataConverter>());
    
    ComponentDataConverterRegistry::addConverter<MockComponentDataConverter>();

    Assert::IsTrue(ComponentDataConverterRegistry::hasCustomConverter<MockComponentDataConverter>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterRegistry_AddConverter_ConverterNotRegistered_ReturnsTrue)
  {
    Assert::IsFalse(ComponentDataConverterRegistry::hasCustomConverter<MockComponentDataConverter>());
    Assert::IsTrue(ComponentDataConverterRegistry::addConverter<MockComponentDataConverter>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterRegistry_AddConverter_ConverterRegistered_DoesNothing)
  {
    ComponentDataConverterRegistry::addConverter<MockComponentDataConverter>();

    Assert::IsTrue(ComponentDataConverterRegistry::hasCustomConverter<MockComponentDataConverter>());

    ComponentDataConverterRegistry::addConverter<MockComponentDataConverter>();

    Assert::IsTrue(ComponentDataConverterRegistry::hasCustomConverter<MockComponentDataConverter>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterRegistry_AddConverter_ConverterRegistered_ReturnsFalse)
  {
    ComponentDataConverterRegistry::addConverter<MockComponentDataConverter>();

    Assert::IsTrue(ComponentDataConverterRegistry::hasCustomConverter<MockComponentDataConverter>());
    Assert::IsFalse(ComponentDataConverterRegistry::addConverter<MockComponentDataConverter>());
  }

#pragma endregion

#pragma region Remove Converter Tests

#pragma region Templated Parameter

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterRegistry_RemoveComponent_ConverterRegistered_RemovesConverterFromRegistry)
  {
    ComponentDataConverterRegistry::addConverter<MockComponentDataConverter>();

    Assert::IsTrue(ComponentDataConverterRegistry::hasCustomConverter<MockComponentDataConverter>());

    ComponentDataConverterRegistry::removeConverter<MockComponentDataConverter>();

    Assert::IsFalse(ComponentDataConverterRegistry::hasCustomConverter<MockComponentDataConverter>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterRegistry_RemoveComponent_ConverterNotRegistered_DoesNothing)
  {
    Assert::IsFalse(ComponentDataConverterRegistry::hasCustomConverter<MockComponentDataConverter>());

    ComponentDataConverterRegistry::removeConverter<MockComponentDataConverter>();

    Assert::IsFalse(ComponentDataConverterRegistry::hasCustomConverter<MockComponentDataConverter>());
  }

#pragma endregion

#pragma region String Parameter

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterRegistry_RemoveComponent_ConverterNameRegistered_RemovesConverterFromRegistry)
  {
    ComponentDataConverterRegistry::addConverter<MockComponentDataConverter>();

    Assert::IsTrue(ComponentDataConverterRegistry::hasCustomConverter<MockComponentDataConverter>());

    ComponentDataConverterRegistry::removeConverter(MockComponentDataConverter::ComponentType::type_name());

    Assert::IsFalse(ComponentDataConverterRegistry::hasCustomConverter<MockComponentDataConverter>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterRegistry_RemoveComponent_ConverterNameNotRegistered_DoesNothing)
  {
    Assert::IsFalse(ComponentDataConverterRegistry::hasCustomConverter<MockComponentDataConverter>());

    ComponentDataConverterRegistry::removeConverter(MockComponentDataConverter::ComponentType::type_name());

    Assert::IsFalse(ComponentDataConverterRegistry::hasCustomConverter<MockComponentDataConverter>());
  }

#pragma endregion

#pragma endregion

#pragma region Get Converter Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterRegistry_GetConverter_InputtingComponentName_WithNoRegisteredConverter_ReturnsNewInstanceOfComponentDataConverter)
  {
    Assert::IsFalse(ComponentDataConverterRegistry::hasCustomConverter("WubbaLubbaDubDub"));

    std::unique_ptr<ComponentDataConverter> converter(nullptr);
    ComponentDataConverterRegistry::getConverter("WubbaLubbdaDubDub", converter);

    Assert::IsNotNull(converter.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterRegistry_GetConverter_InputtingComponentName_WithRegisteredConverter_ReturnsNewInstanceOfRegisteredDataConverter)
  {
    Assert::IsTrue(ComponentDataConverterRegistry::addConverter<MockComponentDataConverter>());
    Assert::IsTrue(ComponentDataConverterRegistry::hasCustomConverter(MockComponent::type_name()));

    std::unique_ptr<ComponentDataConverter> converter(nullptr);
    ComponentDataConverterRegistry::getConverter(MockComponent::type_name(), converter);

    Assert::IsNotNull(converter.get());
    Assert::IsNotNull(dynamic_cast<MockComponentDataConverter*>(converter.get()));
  }

#pragma endregion

#pragma region Convert Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterRegistry_Convert_InputtingNullXMLElement_ReturnsNullComponentHandle)
  {
    GameObject gameObject;

    observer_ptr<Component> component = ComponentDataConverterRegistry::convert(nullptr, gameObject);

    Assert::IsNull(component);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterRegistry_Convert_InputtingXMLElement_WithUnregisteredComponentName_ReturnsNullComponentHandle)
  {
    GameObject gameObject;
    XMLDocument document;
    XMLElement* element = document.NewElement("WubbaLubbaDubDub");

    Assert::IsFalse(ComponentRegistry::hasComponent("WubbaLubbaDubDub"));

    observer_ptr<Component> component = ComponentDataConverterRegistry::convert(element, gameObject);

    Assert::IsNull(component);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterRegistry_Convert_InputtingXMLElement_WithNonCustomDataConverter_AddsComponentToGameObject_WithCorrectData)
  {
    GameObject gameObject;
    MockComponentDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement(MockComponentDataConverter::ComponentType::type_name());
    element->SetAttribute(ComponentDataConverter::IS_ACTIVE_ATTRIBUTE_NAME, false);

    Assert::IsFalse(ComponentDataConverterRegistry::hasCustomConverter<MockComponentDataConverter>());
    AssertCel::DoesNotHaveComponent<MockComponent>(gameObject);

    observer_ptr<Component> component = ComponentDataConverterRegistry::convert(element, gameObject);

    Assert::IsNotNull(component);
    AssertCel::HasComponent<MockComponent>(gameObject);
    Assert::AreSame(gameObject, component->getGameObject());
    AssertCel::IsNotActive(*component);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverterRegistry_Convert_InputtingXMLElement_WithCustomDataConverter_AddsComponentToGameObject_WithCorrectData)
  {
    GameObject gameObject;
    MockComponentDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement(MockComponentDataConverter::ComponentType::type_name());
    element->SetAttribute(ComponentDataConverter::IS_ACTIVE_ATTRIBUTE_NAME, false);

    Assert::IsTrue(ComponentDataConverterRegistry::addConverter<MockComponentDataConverter>());
    Assert::IsTrue(ComponentDataConverterRegistry::hasCustomConverter<MockComponentDataConverter>());
    AssertCel::DoesNotHaveComponent<MockComponent>(gameObject);

    observer_ptr<Component> component = ComponentDataConverterRegistry::convert(element, gameObject);

    Assert::IsNotNull(component);
    AssertCel::HasComponent<MockComponent>(gameObject);
    Assert::AreSame(gameObject, component->getGameObject());
    AssertCel::IsNotActive(*component);
  }

#pragma endregion

  };
}