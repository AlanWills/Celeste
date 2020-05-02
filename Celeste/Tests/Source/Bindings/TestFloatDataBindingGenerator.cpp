#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Bindings/DataBindingGenerators.h"

using namespace Celeste::Bindings;


namespace TestCeleste
{
  namespace Bindings
  {
    CELESTE_TEST_CLASS(TestFloatDataBindingGenerator)

#pragma region Generate Binding Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(FloatDataBindingGenerator_GenerateBinding_Value_AppendsCorrectText)
    {
      std::string output, expected("\t\t[XmlAttribute(\"float_value_field\"), DisplayName(\"Float Value Field\")]\n\t\tpublic float FloatValueField { get; set; } = ");
      expected.append(std::to_string(-5.1123123f));
      expected.append("f;");
      DataBindingGenerator<float, false>::generateBinding("float_value_field", -5.1123123f, output);

      Assert::AreEqual(expected, output);

      output.assign("WubbaLubbaDubDub");
      expected = "WubbaLubbaDubDub" + expected;
      DataBindingGenerator<float, false>::generateBinding("float_value_field", -5.1123123f, output);

      Assert::AreEqual(expected, output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(FloatDataBindingGenerator_GenerateBinding_Reference_AppendsCorrectText)
    {
      std::string output, expected("\t\t[XmlAttribute(\"float_reference_field\"), DisplayName(\"Float Reference Field\")]\n\t\tpublic float FloatReferenceField { get; set; } = ");
      expected.append(std::to_string(-5.1123123f));
      expected.append("f;");
      DataBindingGenerator<float, true>::generateBinding("float_reference_field", -5.1123123f, output);

      Assert::AreEqual(expected, output);

      output.assign("WubbaLubbaDubDub");
      expected = "WubbaLubbaDubDub" + expected;
      DataBindingGenerator<float, true>::generateBinding("float_reference_field", -5.1123123f, output);

      Assert::AreEqual(expected, output);
    }

#pragma endregion

    };
  }
}