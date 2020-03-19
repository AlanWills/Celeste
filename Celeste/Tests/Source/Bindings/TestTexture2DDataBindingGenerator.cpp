#include "UtilityHeaders/UnitTestHeaders.h"
#include "Bindings/DataBindingGenerators.h"
#include "Resources/2D/Texture2D.h"

using namespace Celeste;
using namespace Celeste::Resources;
using namespace Celeste::Bindings;


namespace TestCeleste::Bindings
{
  CELESTE_TEST_CLASS(TestTexture2DDataBindingGenerator)

#pragma region Generate Binding Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Texture2DDataBindingGenerator_GenerateBinding_Value_AppendsCorrectText)
  {
    Texture2D texture;
    std::string output, expected("\t\t[XmlAttribute(\"texture2D_value_field\"), DisplayName(\"Texture2D Value Field\")]\n\t\tpublic Texture2D Texture2DValueField { get; set; }");
    DataBindingGenerator<Texture2D, false>::generateBinding("texture2D_value_field", texture, output);

    Assert::AreEqual(expected, output);

    output.assign("WubbaLubbaDubDub");
    expected = "WubbaLubbaDubDub" + expected;
    DataBindingGenerator<Texture2D, false>::generateBinding("texture2D_value_field", texture, output);

    Assert::AreEqual(expected, output);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Texture2DDataBindingGenerator_GenerateBinding_Reference_AppendsCorrectText)
  {
    Texture2D texture;
    std::string output, expected("\t\t[XmlAttribute(\"texture2D_reference_field\"), DisplayName(\"Texture2D Reference Field\")]\n\t\tpublic Texture2D Texture2DReferenceField { get; set; }");
    DataBindingGenerator<Texture2D, true>::generateBinding("texture2D_reference_field", texture, output);

    Assert::AreEqual(expected, output);

    output.assign("WubbaLubbaDubDub");
    expected = "WubbaLubbaDubDub" + expected;
    DataBindingGenerator<Texture2D, true>::generateBinding("texture2D_reference_field", texture, output);

    Assert::AreEqual(expected, output);
  }

#pragma endregion

  };
}