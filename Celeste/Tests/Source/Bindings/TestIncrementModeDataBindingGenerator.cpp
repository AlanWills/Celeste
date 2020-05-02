#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Bindings/InputDataBindingGenerators.h"

using namespace Celeste;
using namespace Celeste::Bindings;


namespace TestCeleste
{
  namespace Bindings
  {
    CELESTE_TEST_CLASS(TestIncrementModeDataBindingGenerator)

#pragma region Generate Binding Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(IncrementModeDataBindingGenerator_GenerateValueBindingFor_kToggle_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<Input::IncrementMode, false>::generateBinding("increment_mode_value_field", Input::IncrementMode::kToggle, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"increment_mode_value_field\"), DisplayName(\"Increment Mode Value Field\")]\n\t\tpublic IncrementMode IncrementModeValueField { get; set; } = IncrementMode.Toggle;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<Input::IncrementMode, false>::generateBinding("increment_mode_value_field", Input::IncrementMode::kToggle, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"increment_mode_value_field\"), DisplayName(\"Increment Mode Value Field\")]\n\t\tpublic IncrementMode IncrementModeValueField { get; set; } = IncrementMode.Toggle;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(IncrementModeDataBindingGenerator_GenerateValueBindingFor_kContinuous_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<Input::IncrementMode, false>::generateBinding("increment_mode_value_field", Input::IncrementMode::kContinuous, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"increment_mode_value_field\"), DisplayName(\"Increment Mode Value Field\")]\n\t\tpublic IncrementMode IncrementModeValueField { get; set; } = IncrementMode.Continuous;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<Input::IncrementMode, false>::generateBinding("increment_mode_value_field", Input::IncrementMode::kContinuous, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"increment_mode_value_field\"), DisplayName(\"Increment Mode Value Field\")]\n\t\tpublic IncrementMode IncrementModeValueField { get; set; } = IncrementMode.Continuous;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(IncrementModeDataBindingGenerator_GenerateReferenceBindingFor_kToggle_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<Input::IncrementMode, true>::generateBinding("increment_mode_reference_field", Input::IncrementMode::kToggle, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"increment_mode_reference_field\"), DisplayName(\"Increment Mode Reference Field\")]\n\t\tpublic IncrementMode IncrementModeReferenceField { get; set; } = IncrementMode.Toggle;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<Input::IncrementMode, true>::generateBinding("increment_mode_reference_field", Input::IncrementMode::kToggle, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"increment_mode_reference_field\"), DisplayName(\"Increment Mode Reference Field\")]\n\t\tpublic IncrementMode IncrementModeReferenceField { get; set; } = IncrementMode.Toggle;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(IncrementModeDataBindingGenerator_GenerateReferenceBindingFor_kContinuous_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<Input::IncrementMode, true>::generateBinding("increment_mode_reference_field", Input::IncrementMode::kContinuous, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"increment_mode_reference_field\"), DisplayName(\"Increment Mode Reference Field\")]\n\t\tpublic IncrementMode IncrementModeReferenceField { get; set; } = IncrementMode.Continuous;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<Input::IncrementMode, true>::generateBinding("increment_mode_reference_field", Input::IncrementMode::kContinuous, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"increment_mode_reference_field\"), DisplayName(\"Increment Mode Reference Field\")]\n\t\tpublic IncrementMode IncrementModeReferenceField { get; set; } = IncrementMode.Continuous;", output.c_str());
    }

#pragma endregion

    };
  }
}