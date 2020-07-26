#include "CelesteTestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/DataConverters/Objects/MockComponentDataConverter.h"
#include "Objects/GameObject.h"
#include "CelesteTestUtils/Assert/AssertCel.h"

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
    GameObject gameObject;
    MockComponent component(gameObject);
    component.setActive(false);

    MockComponentDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Component");
    element->SetAttribute(ComponentDataConverter::IS_ACTIVE_ATTRIBUTE_NAME, true);

    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getIsActive());
    AssertCel::IsNotActive(component);

    converter.setValues(component);

    AssertCel::IsActive(component);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverter_SetValues_GameObjectNotActive_ComponentActive_SetsComponentToActive)
  {
    GameObject gameObject;
    gameObject.setActive(false);
    MockComponentDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Component");
    element->SetAttribute(ComponentDataConverter::IS_ACTIVE_ATTRIBUTE_NAME, true);

    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getIsActive());
    AssertCel::IsNotActive(gameObject);

    observer_ptr<MockComponent> component = gameObject.addComponent<MockComponent>();

    AssertCel::IsActive(component);

    converter.setValues(*component);
    
    AssertCel::IsActive(component);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverter_SetValues_GameObjectNotActive_ComponentNotActive_KeepsComponentAsNotActive)
  {
    GameObject gameObject;
    gameObject.setActive(false);
    MockComponentDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Component");
    element->SetAttribute(ComponentDataConverter::IS_ACTIVE_ATTRIBUTE_NAME, false);

    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsFalse(converter.getIsActive());
    AssertCel::IsNotActive(gameObject);

    observer_ptr<MockComponent> component = gameObject.addComponent<MockComponent>();
    component->setActive(false);

    AssertCel::IsNotActive(component);

    converter.setValues(*component);

    AssertCel::IsNotActive(component);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverter_SetValues_GameObjectActive_ComponentNotActive_KeepsComponentAsNotActive)
  {
    GameObject gameObject;
    MockComponentDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Component");
    element->SetAttribute(ComponentDataConverter::IS_ACTIVE_ATTRIBUTE_NAME, false);

    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsFalse(converter.getIsActive());
    AssertCel::IsActive(gameObject);

    observer_ptr<MockComponent> component = gameObject.addComponent<MockComponent>();
    component->setActive(false);

    AssertCel::IsNotActive(component);

    converter.setValues(*component);

    AssertCel::IsNotActive(component);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ComponentDataConverter_SetValues_GameObjectActive_ComponentActive_KeepsComponentAsActive)
  {
    GameObject gameObject;
    MockComponentDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("Component");
    element->SetAttribute(ComponentDataConverter::IS_ACTIVE_ATTRIBUTE_NAME, true);

    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getIsActive());
    AssertCel::IsActive(gameObject);

    observer_ptr<MockComponent> component = gameObject.addComponent<MockComponent>();

    AssertCel::IsActive(component);

    converter.setValues(*component);

    AssertCel::IsActive(component);
  }

#pragma endregion

  };
}