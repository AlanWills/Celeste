#include "UtilityHeaders/UnitTestHeaders.h"

#include "Registries/ComponentDataConverterRegistry.h"
#include "DataConverters/Objects/ComponentDataConverter.h"
#include "UI/TextBox.h"
#include "Objects/GameObject.h"
#include "AssertCel.h"

using namespace Celeste;


namespace TestCeleste
{
  CELESTE_TEST_CLASS(TestTextBoxDataConverter)

#pragma region Registration Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextBoxDataConverter_CheckHasNoCustomConverterRegistered)
  {
    Assert::IsFalse(ComponentDataConverterRegistry::hasCustomConverter("TextBox"));
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(TextBoxDataConverter_CheckCanBeConvertedFromXML)
  {
    GameObject gameObject;
    XMLDocument document;
    XMLElement* element = document.NewElement("TextBox");

    observer_ptr<Component> component = ComponentDataConverterRegistry::convert(element, gameObject);

    Assert::IsNotNull(component);
    Assert::IsNotNull(dynamic_cast<UI::TextBox*>(component));
    Assert::IsTrue(&gameObject == component->getGameObject());
  }

#pragma endregion

#pragma region Instantiation Tests

  //----------------------------------------------------------------------------------------------------------
  TEST_METHOD(TextBoxDataConverter_Instantiate_SetsInputtedPointer_ToNewComponentDataConverterInstance)
  {
    std::unique_ptr<ComponentDataConverter> ptr(nullptr);

    ComponentDataConverter converter("");
    converter.instantiate(ptr);

    Assert::IsNotNull(ptr.get());
  }

#pragma endregion

  };
}