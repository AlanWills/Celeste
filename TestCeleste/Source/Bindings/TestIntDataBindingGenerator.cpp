#include "UtilityHeaders/UnitTestHeaders.h"

#include "Bindings/DataBindingGenerators.h"

using namespace Celeste::Bindings;


namespace TestCeleste
{
  namespace Bindings
  {
    CELESTE_TEST_CLASS(TestIntDataBindingGenerator)

#pragma region Generate Binding Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(IntDataBindingGenerator_GenerateBinding_Value_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<int, false>::generateBinding("int_value_field", -5, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"int_value_field\"), DisplayName(\"Int Value Field\")]\n\t\tpublic int IntValueField { get; set; } = -5;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<int, false>::generateBinding("int_value_field", -5, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"int_value_field\"), DisplayName(\"Int Value Field\")]\n\t\tpublic int IntValueField { get; set; } = -5;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(IntDataBindingGenerator_GenerateBinding_Reference_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<int, true>::generateBinding("int_reference_field", -5, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"int_reference_field\"), DisplayName(\"Int Reference Field\")]\n\t\tpublic int IntReferenceField { get; set; } = -5;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<int, true>::generateBinding("int_reference_field", -5, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"int_reference_field\"), DisplayName(\"Int Reference Field\")]\n\t\tpublic int IntReferenceField { get; set; } = -5;", output.c_str());
    }

#pragma endregion

    };
  }
}