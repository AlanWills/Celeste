#include "UtilityHeaders/UnitTestHeaders.h"

#include "Mocks/DataConverters/ObjectFX/MockLimitedLifeTimeDataConverter.h"
#include "Resources/ObjectFX/LimitedLifeTimeLoadingResources.h"
#include "Resources/ResourceManager.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "DataConverters/Callbacks/CallbackDataConverter.h"
#include "ObjectFX/LimitedLifeTime.h"
#include "AssertCel.h"

using namespace Celeste::Resources;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestLimitedLifeTimeDataConverter)

  //------------------------------------------------------------------------------------------------
  void TestLimitedLifeTimeDataConverter::testInitialize()
  {
    LimitedLifeTimeLoadingResources::unloadAllResources();
  }

#pragma region Registration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_CheckIsRegistered)
  {
    Assert::IsTrue(ComponentDataConverterRegistry::hasCustomConverter<LimitedLifeTimeDataConverter>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_CheckCanBeConvertedFromXML)
  {
    GameObject gameObject;
    observer_ptr<Data> data = getResourceManager().load<Data>(LimitedLifeTimeLoadingResources::getValidNoCallbacksFullPath());
    AutoDeallocator<Component> component = ComponentDataConverterRegistry::convert(data->getDocumentRoot(), gameObject);

    Assert::IsNotNull(component.get());
    Assert::IsNotNull(dynamic_cast<LimitedLifeTime*>(component.get()));
    Assert::IsTrue(&gameObject == component->getGameObject());
  }

#pragma endregion

#pragma region Instantiation Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_Instantiate_SetsInputtedPointer_ToNewLimitedLifeTimeDataConverterInstance)
  {
    std::unique_ptr<ComponentDataConverter> ptr(nullptr);

    LimitedLifeTimeDataConverter converter;
    converter.instantiate(ptr);

    Assert::IsNotNull(dynamic_cast<LimitedLifeTimeDataConverter*>(ptr.get()));
  }

#pragma endregion

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_Constructor_SetsIsDataLoadedCorrectly_ToFalse)
  {
    LimitedLifeTimeDataConverter converter;

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_Constructor_SetsIsActive_ToTrue)
  {
    LimitedLifeTimeDataConverter converter;

    Assert::IsTrue(converter.getIsActive());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_Constructor_SetsElementName_ToInput)
  {
    LimitedLifeTimeDataConverter converter;

    Assert::AreEqual("LimitedLifeTime", converter.getElementName().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_Constructor_SetsLifeTimeToZero)
  {
    LimitedLifeTimeDataConverter converter;

    Assert::AreEqual(0.0f, converter.getLifeTime());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_Constructor_SetsTriggerKeyTo_GLFW_KEY_UNKNOWN)
  {
    LimitedLifeTimeDataConverter converter;

    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getTriggerKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_Constructor_AddsLifeTimeAttribute)
  {
    const MockLimitedLifeTimeDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(LimitedLifeTimeDataConverter::LIFE_TIME_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_Constructor_AddsTriggerKeyAttribute)
  {
    const MockLimitedLifeTimeDataConverter converter;

    Assert::IsNotNull(converter.findAttribute(LimitedLifeTimeDataConverter::TRIGGER_KEY_ATTRIBUTE_NAME));
  }

#pragma endregion

#pragma region Convert From XML Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_ConvertFromXML_InputtingNullXMLElement_ReturnsFalse)
  {
    LimitedLifeTimeDataConverter converter;

    Assert::IsFalse(converter.convertFromXML(nullptr));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_ConvertFromXML_InputtingNullXMLElement_SetsIsDataLoadedCorrectly_ToFalse)
  {
    LimitedLifeTimeDataConverter converter;
    converter.convertFromXML(nullptr);

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_ConvertFromXML_InputtingInvalidXML_ReturnsFalse)
  {
    LimitedLifeTimeDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(LimitedLifeTimeLoadingResources::getInvalidFullPath());

    Assert::IsFalse(converter.convertFromXML(data->getDocumentRoot()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_ConvertFromXML_InputtingInvalidXML_SetsIsDataLoadedCorrectly_ToFalse)
  {
    LimitedLifeTimeDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(LimitedLifeTimeLoadingResources::getInvalidFullPath());
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_ConvertFromXML_InputtingValidXML_ReturnsTrue)
  {
    LimitedLifeTimeDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(LimitedLifeTimeLoadingResources::getValidNoCallbacksFullPath());

    Assert::IsTrue(converter.convertFromXML(data->getDocumentRoot()));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_ConvertFromXML_InputtingValidXML_SetsIsDataLoadedCorrectly_ToTrue)
  {
    LimitedLifeTimeDataConverter converter;
    observer_ptr<Data> data = getResourceManager().load<Data>(LimitedLifeTimeLoadingResources::getValidNoCallbacksFullPath());
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());
  }

#pragma endregion

#pragma region Convert LifeTime Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_ConvertFromXML_NoLifeTimeAttribute_DoesNothing_ReturnsTrue)
  {
    LimitedLifeTimeDataConverter converter;
    XMLDocument document;
    const XMLElement* element = document.NewElement("LimitedLifeTime");

    Assert::IsNull(element->FindAttribute(LimitedLifeTimeDataConverter::LIFE_TIME_ATTRIBUTE_NAME));
    Assert::AreEqual(0.0f, converter.getLifeTime());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(0.0f, converter.getLifeTime());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_ConvertFromXML_LifeTimeAttribute_InvalidText_DoesNothing_ReturnsFalse)
  {
    LimitedLifeTimeDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("LimitedLifeTime");
    element->SetAttribute(LimitedLifeTimeDataConverter::LIFE_TIME_ATTRIBUTE_NAME, "WubDubDub");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(LimitedLifeTimeDataConverter::LIFE_TIME_ATTRIBUTE_NAME));
    Assert::AreEqual(0.0f, converter.getLifeTime());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::AreEqual(0.0f, converter.getLifeTime());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_ConvertFromXML_LifeTimeAttribute_ValidText_SetsLifeTimeToCorrectValue_ReturnsTrue)
  {
    LimitedLifeTimeDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("LimitedLifeTime");
    element->SetAttribute(LimitedLifeTimeDataConverter::LIFE_TIME_ATTRIBUTE_NAME, 50);

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(LimitedLifeTimeDataConverter::LIFE_TIME_ATTRIBUTE_NAME));
    Assert::AreEqual(0.0f, converter.getLifeTime());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(50.0f, converter.getLifeTime());
  }

#pragma endregion

#pragma region Convert Trigger Key Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_ConvertFromXML_NoTriggerKeyAttribute_DoesNothing_ReturnsTrue)
  {
    LimitedLifeTimeDataConverter converter;
    XMLDocument document;
    const XMLElement* element = document.NewElement("LimitedLifeTime");

    Assert::IsNull(element->FindAttribute(LimitedLifeTimeDataConverter::TRIGGER_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getTriggerKey());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getTriggerKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_ConvertFromXML_TriggerKeyAttribute_Text_SetsTriggerKeyToCorrectValue_ReturnsTrue)
  {
    LimitedLifeTimeDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("LimitedLifeTime");
    element->SetAttribute(LimitedLifeTimeDataConverter::TRIGGER_KEY_ATTRIBUTE_NAME, "a");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(LimitedLifeTimeDataConverter::TRIGGER_KEY_ATTRIBUTE_NAME));
    Assert::AreEqual(GLFW_KEY_UNKNOWN, converter.getTriggerKey());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(GLFW_KEY_A, converter.getTriggerKey());
  }

#pragma endregion

#pragma region Convert Callbacks Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_ConvertFromXML_NoCallbacksElement_DoesNothing_AndReturnsTrue)
  {
    LimitedLifeTimeDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("LimitedLifeTime");
    
    Assert::IsNull(element->FirstChildElement(LimitedLifeTimeDataConverter::ON_DEATH_CALLBACKS_ELEMENT_NAME));
    Assert::IsTrue(converter.getOnDeathCallbacks().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getOnDeathCallbacks().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_ConvertFromXML_CallbacksElement_NoCallbackElement_DoesNothing_AndReturnsTrue)
  {
    LimitedLifeTimeDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("LimitedLifeTime");
    XMLElement* callbacks = document.NewElement(LimitedLifeTimeDataConverter::ON_DEATH_CALLBACKS_ELEMENT_NAME);
    element->InsertFirstChild(callbacks);

    Assert::IsNotNull(element->FirstChildElement(LimitedLifeTimeDataConverter::ON_DEATH_CALLBACKS_ELEMENT_NAME));
    Assert::IsNull(callbacks->FirstChildElement(LimitedLifeTimeDataConverter::CALLBACK_ELEMENT_NAME));
    Assert::IsTrue(converter.getOnDeathCallbacks().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::IsTrue(converter.getOnDeathCallbacks().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_ConvertFromXML_CallbacksElement_CallbackElementWithNoNameAttribute_DoesNothing_AndReturnsFalse)
  {
    LimitedLifeTimeDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("LimitedLifeTime");
    XMLElement* callbacks = document.NewElement(LimitedLifeTimeDataConverter::ON_DEATH_CALLBACKS_ELEMENT_NAME);
    XMLElement* callback = document.NewElement(LimitedLifeTimeDataConverter::CALLBACK_ELEMENT_NAME);
    element->InsertFirstChild(callbacks);
    callbacks->InsertFirstChild(callback);

    Assert::IsNotNull(element->FirstChildElement(LimitedLifeTimeDataConverter::ON_DEATH_CALLBACKS_ELEMENT_NAME));
    Assert::IsNotNull(callbacks->FirstChildElement(LimitedLifeTimeDataConverter::CALLBACK_ELEMENT_NAME));
    Assert::IsNull(static_cast<const XMLElement*>(callback)->FindAttribute("name"));
    Assert::IsTrue(converter.getOnDeathCallbacks().empty());
    Assert::IsFalse(converter.convertFromXML(element));
    Assert::IsTrue(converter.getOnDeathCallbacks().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_ConvertFromXML_CallbacksElement_CallbackElementWithNameAttribute_AddsCallback_AndReturnsTrue)
  {
    LimitedLifeTimeDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("LimitedLifeTime");
    XMLElement* callbacks = document.NewElement(LimitedLifeTimeDataConverter::ON_DEATH_CALLBACKS_ELEMENT_NAME);
    XMLElement* callback = document.NewElement(LimitedLifeTimeDataConverter::CALLBACK_ELEMENT_NAME);
    element->InsertFirstChild(callbacks);
    callbacks->InsertFirstChild(callback);
    callback->SetAttribute("name", "Test");

    Assert::IsNotNull(element->FirstChildElement(LimitedLifeTimeDataConverter::ON_DEATH_CALLBACKS_ELEMENT_NAME));
    Assert::IsNotNull(callbacks->FirstChildElement(LimitedLifeTimeDataConverter::CALLBACK_ELEMENT_NAME));
    Assert::IsNotNull(static_cast<const XMLElement*>(callback)->FindAttribute("name"));
    Assert::IsNull(static_cast<const XMLElement*>(callback)->FindAttribute("arg"));
    Assert::IsTrue(converter.getOnDeathCallbacks().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(static_cast<size_t>(1), converter.getOnDeathCallbacks().size());
    Assert::AreEqual("Test", converter.getOnDeathCallbacks()[0]->getName().c_str());
    Assert::AreEqual("", converter.getOnDeathCallbacks()[0]->getArg().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_ConvertFromXML_CallbacksElement_CallbackElementWithNameAndArgsAttributes_AddsCallback_AndReturnsTrue)
  {
    LimitedLifeTimeDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("LimitedLifeTime");
    XMLElement* callbacks = document.NewElement(LimitedLifeTimeDataConverter::ON_DEATH_CALLBACKS_ELEMENT_NAME);
    XMLElement* callback = document.NewElement(LimitedLifeTimeDataConverter::CALLBACK_ELEMENT_NAME);
    element->InsertFirstChild(callbacks);
    callbacks->InsertFirstChild(callback);
    callback->SetAttribute("name", "Test");
    callback->SetAttribute("arg", "WubbaLubbaDubDub");

    Assert::IsNotNull(element->FirstChildElement(LimitedLifeTimeDataConverter::ON_DEATH_CALLBACKS_ELEMENT_NAME));
    Assert::IsNotNull(callbacks->FirstChildElement(LimitedLifeTimeDataConverter::CALLBACK_ELEMENT_NAME));
    Assert::IsNotNull(static_cast<const XMLElement*>(callback)->FindAttribute("name"));
    Assert::IsNotNull(static_cast<const XMLElement*>(callback)->FindAttribute("arg"));
    Assert::IsTrue(converter.getOnDeathCallbacks().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(static_cast<size_t>(1), converter.getOnDeathCallbacks().size());
    Assert::AreEqual("Test", converter.getOnDeathCallbacks()[0]->getName().c_str());
    Assert::AreEqual("WubbaLubbaDubDub", converter.getOnDeathCallbacks()[0]->getArg().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_ConvertFromXML_CallbacksElement_OnlyConvertsCallbackElements)
  {
    LimitedLifeTimeDataConverter converter;
    XMLDocument document;
    XMLElement* element = document.NewElement("LimitedLifeTime");
    XMLElement* callbacks = document.NewElement(LimitedLifeTimeDataConverter::ON_DEATH_CALLBACKS_ELEMENT_NAME);
    XMLElement* callback = document.NewElement(LimitedLifeTimeDataConverter::CALLBACK_ELEMENT_NAME);
    XMLElement* callback2 = document.NewElement("_Callback");
    element->InsertFirstChild(callbacks);
    callbacks->InsertFirstChild(callback);
    callbacks->InsertFirstChild(callback);
    callback->SetAttribute("name", "Test");
    callback->SetAttribute("arg", "WubbaLubbaDubDub");
    callback2->SetAttribute("name", "Test2");
    callback2->SetAttribute("arg", "RickyTickyTappy");

    Assert::IsNotNull(element->FirstChildElement(LimitedLifeTimeDataConverter::ON_DEATH_CALLBACKS_ELEMENT_NAME));
    Assert::IsNotNull(callbacks->FirstChildElement(LimitedLifeTimeDataConverter::CALLBACK_ELEMENT_NAME));
    Assert::IsNotNull(static_cast<const XMLElement*>(callback)->FindAttribute("name"));
    Assert::IsNotNull(static_cast<const XMLElement*>(callback)->FindAttribute("arg"));
    Assert::IsTrue(converter.getOnDeathCallbacks().empty());
    Assert::IsTrue(converter.convertFromXML(element));
    Assert::AreEqual(static_cast<size_t>(1), converter.getOnDeathCallbacks().size());
    Assert::AreEqual("Test", converter.getOnDeathCallbacks()[0]->getName().c_str());
    Assert::AreEqual("WubbaLubbaDubDub", converter.getOnDeathCallbacks()[0]->getArg().c_str());
  }

#pragma endregion

#pragma region Set Values Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeConverter_SetValues_InputtingNullLimitedLifeTime_DoesNothing)
  {
    observer_ptr<Data> data = getResourceManager().load<Data>(LimitedLifeTimeLoadingResources::getValidNoCallbacksFullPath());

    LimitedLifeTimeDataConverter converter;
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());

    // Check doesn't throw
    converter.setValues(LimitedLifeTime());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_SetValues_InputtingLimitedLifeTime_DataNotLoadedCorrectly_DoesNothing)
  {
    LimitedLifeTime lifeTime;
    lifeTime.setLifeTime(12);

    observer_ptr<Data> data = getResourceManager().load<Data>(LimitedLifeTimeLoadingResources::getInvalidFullPath());

    LimitedLifeTimeDataConverter converter;
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsFalse(converter.isDataLoadedCorrectly());

    converter.setValues(lifeTime);

    Assert::AreEqual(12.0f, lifeTime.getLifeTime());
    Assert::AreEqual(-1, lifeTime.getTriggerKey());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_SetValues_InputtingLimitedLifeTime_DataLoadedCorrectly_ChangesLimitedLifeTimeToMatchData)
  {
    LimitedLifeTime lifeTime;
    lifeTime.setLifeTime(12);

    observer_ptr<Data> data = getResourceManager().load<Data>(LimitedLifeTimeLoadingResources::getValidWithCallbacksFullPath());

    LimitedLifeTimeDataConverter converter;
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());

    converter.setValues(lifeTime);

    Assert::AreEqual(0.1f, lifeTime.getLifeTime());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(LimitedLifeTimeDataConverter_SetValues_InputtingLimitedLifeTime_DataLoadedCorrectly_ChangesTriggerKeyToMatchData)
  {
    LimitedLifeTime lifeTime;
    lifeTime.setTriggerKey(GLFW_KEY_ESCAPE);

    observer_ptr<Data> data = getResourceManager().load<Data>(LimitedLifeTimeLoadingResources::getValidWithCallbacksFullPath());

    LimitedLifeTimeDataConverter converter;
    converter.convertFromXML(data->getDocumentRoot());

    Assert::IsTrue(converter.isDataLoadedCorrectly());

    converter.setValues(lifeTime);

    Assert::AreEqual(GLFW_KEY_A, lifeTime.getTriggerKey());
  }

#pragma endregion

  };
}