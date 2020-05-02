#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Bindings/DataBindingGenerators.h"

using namespace Celeste::Bindings;


namespace TestCeleste
{
  namespace Bindings
  {
    CELESTE_TEST_CLASS(TestSize_tDataBindingGenerator)

#pragma region Generate Binding Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Size_tDataBindingGenerator_GenerateBinding_Value_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<size_t, false>::generateBinding("sizet_value_field", 5, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"sizet_value_field\"), DisplayName(\"Sizet Value Field\")]\n\t\tpublic uint SizetValueField { get; set; } = 5;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<size_t, false>::generateBinding("sizet_value_field", 5, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"sizet_value_field\"), DisplayName(\"Sizet Value Field\")]\n\t\tpublic uint SizetValueField { get; set; } = 5;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(Size_tDataBindingGenerator_GenerateBinding_Reference_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<size_t, true>::generateBinding("sizet_reference_field", 5, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"sizet_reference_field\"), DisplayName(\"Sizet Reference Field\")]\n\t\tpublic uint SizetReferenceField { get; set; } = 5;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<size_t, true>::generateBinding("sizet_reference_field", 5, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"sizet_reference_field\"), DisplayName(\"Sizet Reference Field\")]\n\t\tpublic uint SizetReferenceField { get; set; } = 5;", output.c_str());
    }

#pragma endregion

  };
}
}