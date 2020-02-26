#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/DataConverters/Objects/MockComponentDataConverter.h"
#include "Utils/ObjectUtils.h"
#include "AssertCel.h"

using namespace Celeste;
using namespace Celeste::Resources;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestComponentDataConverter)

#pragma region Instantiation Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverter_Instantiate_SetsInputtedPointer_ToNewComponentDataConverterInstance)
  {
    std::unique_ptr<ComponentDataConverter> ptr(nullptr);

    ComponentDataConverter converter("");
    converter.instantiate(ptr);

    Assert::IsNotNull(dynamic_cast<ComponentDataConverter*>(ptr.get()));
  }

#pragma endregion

#pragma region Constructor Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverter_Constructor_SetsIsDataLoadedCorrectly_ToFalse)
  {
    ComponentDataConverter converter("Component");

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverter_Constructor_SetsIsActive_ToTrue)
  {
    ComponentDataConverter converter("Component");

    Assert::IsTrue(converter.getIsActive());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverter_Constructor_SetsElementName_ToInput)
  {
    ComponentDataConverter converter("Component");

    Assert::AreEqual("Component", converter.getElementName().c_str());
  }

#pragma endregion

#pragma region Set Values Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverter_SetValues_GameObjectNull_SetsComponentToConverterActiveState)
  {
    MockComponent component;
    component.setActive(false);
    MockComponentDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Component");
    element->SetAttribute(ComponentDataConverter::IS_ACTIVE_ATTRIBUTE_NAME, true);

    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getIsActive());
    Assert::IsNull(component.getGameObject());
    AssertCel::IsNotActive(component);

    converter.setValues(component);

    AssertCel::IsActive(component);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverter_SetValues_GameObjectNotActive_ComponentActive_SetsComponentToActive)
  {
    GAMEOBJECT(gameObject);
    gameObject.setActive(false);
    MockComponentDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Component");
    element->SetAttribute(ComponentDataConverter::IS_ACTIVE_ATTRIBUTE_NAME, true);

    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getIsActive());
    AssertCel::IsNotActive(gameObject);

    AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();

    Assert::IsNotNull(component->getGameObject());
    AssertCel::IsActive(component.get());

    converter.setValues(*component);
    
    AssertCel::IsActive(component.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverter_SetValues_GameObjectNotActive_ComponentNotActive_KeepsComponentAsNotActive)
  {
    GAMEOBJECT(gameObject);
    gameObject.setActive(false);
    MockComponentDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Component");
    element->SetAttribute(ComponentDataConverter::IS_ACTIVE_ATTRIBUTE_NAME, false);

    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsFalse(converter.getIsActive());
    AssertCel::IsNotActive(gameObject);

    AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();
    component->setActive(false);

    Assert::IsNotNull(component->getGameObject());
    AssertCel::IsNotActive(component.get());

    converter.setValues(*component);

    AssertCel::IsNotActive(component.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverter_SetValues_GameObjectActive_ComponentNotActive_KeepsComponentAsNotActive)
  {
    GAMEOBJECT(gameObject);
    MockComponentDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Component");
    element->SetAttribute(ComponentDataConverter::IS_ACTIVE_ATTRIBUTE_NAME, false);

    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsFalse(converter.getIsActive());
    AssertCel::IsActive(gameObject);

    AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();
    component->setActive(false);

    AssertCel::IsNotActive(component.get());

    converter.setValues(*component);

    AssertCel::IsNotActive(component.get());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverter_SetValues_GameObjectActive_ComponentActive_KeepsComponentAsActive)
  {
    GAMEOBJECT(gameObject);
    MockComponentDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Component");
    element->SetAttribute(ComponentDataConverter::IS_ACTIVE_ATTRIBUTE_NAME, true);

    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getIsActive());
    AssertCel::IsActive(gameObject);

    AutoDeallocator<MockComponent> component = gameObject.addComponent<MockComponent>();

    AssertCel::IsActive(component.get());

    converter.setValues(*component);

    AssertCel::IsActive(component.get());
  }

#pragma endregion

  };
}