#include "UtilityHeaders/UnitTestHeaders.h"

#include "Bindings/DataBindingGenerators.h"

using namespace Celeste::Bindings;


namespace TestCeleste
{
  namespace Bindings
  {
    CELESTE_TEST_CLASS(TestStringDataBindingGenerator)

#pragma region Generate Binding Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringDataBindingGenerator_GenerateBinding_Value_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<std::string, false>::generateBinding("string_value_field", "Test String", output);

      Assert::AreEqual("\t\t[XmlAttribute(\"string_value_field\"), DisplayName(\"String Value Field\")]\n\t\tpublic string StringValueField { get; set; } = \"Test String\";", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<std::string, false>::generateBinding("string_value_field", "Test String", output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"string_value_field\"), DisplayName(\"String Value Field\")]\n\t\tpublic string StringValueField { get; set; } = \"Test String\";", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(StringDataBindingGenerator_GenerateBinding_Reference_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<std::string, true>::generateBinding("string_reference_field", "Test String", output);

      Assert::AreEqual("\t\t[XmlAttribute(\"string_reference_field\"), DisplayName(\"String Reference Field\")]\n\t\tpublic string StringReferenceField { get; set; } = \"Test String\";", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<std::string, true>::generateBinding("string_reference_field", "Test String", output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"string_reference_field\"), DisplayName(\"String Reference Field\")]\n\t\tpublic string StringReferenceField { get; set; } = \"Test String\";", output.c_str());
    }

#pragma endregion

    };
  }
}