#include "UtilityHeaders/UnitTestHeaders.h"

#include "DataConverters/Objects/ScriptableObjectDataConverter.h"
#include "Registries/ScriptableObjectRegistry.h"
#include "Resources/Objects/MockScriptableObjectLoadingResources.h"
#include "Mocks/Objects/MockScriptableObject.h"
#include "Utils/ObjectUtils.h"
#include "AssertCel.h"
#include "AssertExt.h"

using namespace Celeste;
using namespace Celeste::Resources;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestScriptableObjectDataConverter)

  //------------------------------------------------------------------------------------------------
  void TestScriptableObjectDataConverter::testInitialize()
  {
    ScriptableObjectRegistry::removeScriptableObject<MockScriptableObject>();
  }

  //------------------------------------------------------------------------------------------------
  void TestScriptableObjectDataConverter::testCleanup()
  {
    ScriptableObjectRegistry::removeScriptableObject<MockScriptableObject>();
  }

#pragma region Constructor Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObjectDataConverter_Constructor_SetsIsDataLoadedCorrectly_ToFalse)
  {
    ScriptableObjectDataConverter converter("ScriptableObject");

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObjectDataConverter_Constructor_SetsPath_ToEmptyString)
  {
    ScriptableObjectDataConverter converter("ScriptableObject");

    Assert::IsTrue(converter.getPath().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObjectDataConverter_Constructor_AddsPathAttribute)
  {
    const ScriptableObjectDataConverter converter("ScriptableObject");

    Assert::IsNotNull(converter.findAttribute(ScriptableObjectDataConverter::PATH_ATTRIBUTE_NAME));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObjectDataConverter_Constructor_SetsPathDeserializationRequirement_ToRequired)
  {
    const ScriptableObjectDataConverter converter("ScriptableObject");

    Assert::IsTrue(converter.findAttribute(ScriptableObjectDataConverter::PATH_ATTRIBUTE_NAME)->isRequired());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObjectDataConverter_Constructor_SetsElementName_ToInput)
  {
    const ScriptableObjectDataConverter converter("ScriptableObject");

    Assert::AreEqual("ScriptableObject", converter.getElementName().c_str());
  }

#pragma endregion

#pragma region Copy Constructor Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObjectDataConverter_CopyConstructor_CopiesElementName)
  {
    ScriptableObjectDataConverter converter("ScriptableObject");
    ScriptableObjectDataConverter converter2(converter);

    Assert::AreEqual("ScriptableObject", converter.getElementName().c_str());
    Assert::AreEqual("ScriptableObject", converter2.getElementName().c_str());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObjectDataConverter_CopyConstructor_CopiesPathAttribute)
  {
    const ScriptableObjectDataConverter converter("ScriptableObject");
    const ScriptableObjectDataConverter converter2(converter);

    Assert::AreEqual(static_cast<size_t>(1), converter2.getAttributesSize());
    Assert::IsNotNull(converter2.findAttribute(ScriptableObjectDataConverter::PATH_ATTRIBUTE_NAME));
  }

#pragma endregion

#pragma region Move Constructor Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObjectDataConverter_MoveConstructor_MovesElementName)
  {
    ScriptableObjectDataConverter converter("ScriptableObject");

    Assert::AreEqual("ScriptableObject", converter.getElementName().c_str());

    ScriptableObjectDataConverter converter2(std::move(converter));

    Assert::AreEqual("ScriptableObject", converter2.getElementName().c_str());
  }

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObjectDataConverter_MoveConstructor_MovesPathAttribute)
  {
    const ScriptableObjectDataConverter converter("ScriptableObject");
    auto isActiveAttribute = converter.findAttribute(ScriptableObjectDataConverter::PATH_ATTRIBUTE_NAME);

    Assert::IsNotNull(isActiveAttribute);

    const ScriptableObjectDataConverter converter2(std::move(converter));

    Assert::IsNotNull(converter2.findAttribute(ScriptableObjectDataConverter::PATH_ATTRIBUTE_NAME));
  }

#pragma endregion

#pragma region Convert From XML Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObjectDataConverter_ConvertFromXML_InputtingNullptr_ReturnsFalse)
  {
    ScriptableObjectDataConverter converter("ScriptableObject");

    Assert::IsFalse(converter.convertFromXML(nullptr));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObjectDataConverter_ConvertFromXML_InputtingNullptr_SetsIsDataLoadedCorrectlyToFalse)
  {
    ScriptableObjectDataConverter converter("ScriptableObject");
    converter.convertFromXML(nullptr);

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObjectDataConverter_ConvertFromXML_InputtingInvalidXML_ReturnsFalse)
  {
    ScriptableObjectDataConverter converter("ScriptableObject");
    XMLDocument document;
    XMLElement* element = document.NewElement("ScriptableObject");

    Assert::IsFalse(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObjectDataConverter_ConvertFromXML_InputtingInvalidXML_SetsIsDataLoadedCorrectlyToFalse)
  {
    ScriptableObjectDataConverter converter("ScriptableObject");
    XMLDocument document;
    XMLElement* element = document.NewElement("ScriptableObject");

    converter.convertFromXML(element);

    Assert::IsFalse(converter.isDataLoadedCorrectly());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObjectDataConverter_ConvertFromXML_InputtingValidXML_ReturnsTrue)
  {
    ScriptableObjectDataConverter converter("ScriptableObject");
    XMLDocument document;
    XMLElement* element = document.NewElement("ScriptableObject");
    element->SetAttribute(ScriptableObjectDataConverter::PATH_ATTRIBUTE_NAME, "WubDub.json");

    Assert::IsTrue(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObjectDataConverter_ConvertFromXML_InputtingValidXML_SetsIsDataLoadedCorrectlyToTrue)
  {
    ScriptableObjectDataConverter converter("ScriptableObject");
    XMLDocument document;
    XMLElement* element = document.NewElement("ScriptableObject");
    element->SetAttribute(ScriptableObjectDataConverter::PATH_ATTRIBUTE_NAME, "WubDub.json");

    converter.convertFromXML(element);

    Assert::IsTrue(converter.isDataLoadedCorrectly());
  }

#pragma endregion

#pragma region Convert Path Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObjectDataConverter_ConvertPath_AttributeDoesNotExist_LeavesPathAsEmpty)
  {
    ScriptableObjectDataConverter converter("ScriptableObject");
    XMLDocument document;
    const XMLElement* element = document.NewElement("ScriptableObject");

    Assert::IsNull(element->FindAttribute(ScriptableObjectDataConverter::PATH_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getPath().empty());

    converter.convertFromXML(element);

    Assert::IsTrue(converter.getPath().empty());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObjectDataConverter_ConvertPath_AttributeDoesNotExist_CausesConversionToFail)
  {
    ScriptableObjectDataConverter converter("ScriptableObject");
    XMLDocument document;
    const XMLElement* element = document.NewElement("ScriptableObject");

    Assert::IsNull(element->FindAttribute(ScriptableObjectDataConverter::PATH_ATTRIBUTE_NAME));
    Assert::IsFalse(converter.convertFromXML(element));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObjectDataConverter_ConvertPath_AttributeExists_InvalidText_LeavesPathAsEmptyString)
  {
    // Invalid text doesn't exist for text attributes
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObjectDataConverter_ConvertPath_AttributeExists_InvalidText_CausesConversionToFail)
  {
    // Invalid text doesn't exist for text attributes
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObjectDataConverter_ConvertPath_AttributeExists_ValidText_SetsPathToValue)
  {
    ScriptableObjectDataConverter converter("ScriptableObject");
    XMLDocument document;
    XMLElement* element = document.NewElement("ScriptableObject");
    element->SetAttribute(ScriptableObjectDataConverter::PATH_ATTRIBUTE_NAME, "WubDub.json");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(ScriptableObjectDataConverter::PATH_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.getPath().empty());

    converter.convertFromXML(element);

    Assert::AreEqual("WubDub.json", converter.getPath().c_str());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObjectDataConverter_ConvertPath_AttributeExists_ValidText_DoesNotCauseConversionToFail)
  {
    ScriptableObjectDataConverter converter("ScriptableObject");
    XMLDocument document;
    XMLElement* element = document.NewElement("ScriptableObject");
    element->SetAttribute(ScriptableObjectDataConverter::PATH_ATTRIBUTE_NAME, "WubDub.json");

    Assert::IsNotNull(static_cast<const XMLElement*>(element)->FindAttribute(ScriptableObjectDataConverter::PATH_ATTRIBUTE_NAME));
    Assert::IsTrue(converter.convertFromXML(element));
  }

#pragma endregion

#pragma region Instantiate Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObjectDataConverter_Instantiate_InvalidPath_ReturnsNullptr)
  {
    ScriptableObjectDataConverter converter("ScriptableObject");
    XMLDocument document;
    XMLElement* element = document.NewElement("ScriptableObject");
    element->SetAttribute(ScriptableObjectDataConverter::PATH_ATTRIBUTE_NAME, "WubDub.json");
    converter.convertFromXML(element);

    AssertExt::IsNull(converter.instantiate<MockScriptableObject>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObjectDataConverter_Instantiate_ValidPathToUnregisteredValidScriptableObject_ReturnsNullptr)
  {
    Assert::IsFalse(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

    ScriptableObjectDataConverter converter("ScriptableObject");
    XMLDocument document;
    XMLElement* element = document.NewElement("ScriptableObject");
    element->SetAttribute(ScriptableObjectDataConverter::PATH_ATTRIBUTE_NAME, MockScriptableObjectLoadingResources::getValidFullPath().c_str());
    converter.convertFromXML(element);

    AssertExt::IsNull(converter.instantiate<MockScriptableObject>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObjectDataConverter_Instantiate_ValidPathToRegisteredInvalidScriptableObject_ReturnsNullptr)
  {
    ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();

    Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

    ScriptableObjectDataConverter converter("ScriptableObject");
    XMLDocument document;
    XMLElement* element = document.NewElement("ScriptableObject");
    element->SetAttribute(ScriptableObjectDataConverter::PATH_ATTRIBUTE_NAME, MockScriptableObjectLoadingResources::getInvalidFullPath().c_str());
    converter.convertFromXML(element);

    AssertExt::IsNull(converter.instantiate<MockScriptableObject>());
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(ScriptableObjectDataConverter_Instantiate_ValidPathToValidScriptableObject_ReturnsInstanceOfScriptableObject)
  {
    ScriptableObjectRegistry::addScriptableObject<MockScriptableObject>();

    Assert::IsTrue(ScriptableObjectRegistry::hasScriptableObject<MockScriptableObject>());

    ScriptableObjectDataConverter converter("ScriptableObject");
    XMLDocument document;
    XMLElement* element = document.NewElement("ScriptableObject");
    element->SetAttribute(ScriptableObjectDataConverter::PATH_ATTRIBUTE_NAME, MockScriptableObjectLoadingResources::getValidFullPath().c_str());
    converter.convertFromXML(element);

    AssertExt::IsNotNull(converter.instantiate<MockScriptableObject>());
  }

#pragma endregion

  };
}