#include "Bindings/DataBindingGenerators.h"
#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

using namespace Celeste;
using namespace Celeste::Bindings;


namespace TestCeleste
{
  namespace Bindings
  {
    CELESTE_TEST_CLASS(TestBoolDataBindingGenerator)

#pragma region Generate Binding Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BoolDataBindingGenerator_GenerateValueBindingFor_True_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<bool, false>::generateBinding("bool_value_field", true, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"bool_value_field\"), DisplayName(\"Bool Value Field\")]\n\t\tpublic bool BoolValueField { get; set; } = true;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<bool, false>::generateBinding("bool_value_field", true, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"bool_value_field\"), DisplayName(\"Bool Value Field\")]\n\t\tpublic bool BoolValueField { get; set; } = true;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BoolDataBindingGenerator_GenerateValueBindingFor_False_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<bool, false>::generateBinding("bool_value_field", false, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"bool_value_field\"), DisplayName(\"Bool Value Field\")]\n\t\tpublic bool BoolValueField { get; set; } = false;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<bool, false>::generateBinding("bool_value_field", false, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"bool_value_field\"), DisplayName(\"Bool Value Field\")]\n\t\tpublic bool BoolValueField { get; set; } = false;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BoolDataBindingGenerator_GenerateReferenceBindingFor_True_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<bool, true>::generateBinding("bool_reference_field", true, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"bool_reference_field\"), DisplayName(\"Bool Reference Field\")]\n\t\tpublic bool BoolReferenceField { get; set; } = true;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<bool, true>::generateBinding("bool_reference_field", true, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"bool_reference_field\"), DisplayName(\"Bool Reference Field\")]\n\t\tpublic bool BoolReferenceField { get; set; } = true;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(BoolDataBindingGenerator_GenerateReferenceBindingFor_False_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<bool, true>::generateBinding("bool_reference_field", false, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"bool_reference_field\"), DisplayName(\"Bool Reference Field\")]\n\t\tpublic bool BoolReferenceField { get; set; } = false;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<bool, true>::generateBinding("bool_reference_field", false, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"bool_reference_field\"), DisplayName(\"Bool Reference Field\")]\n\t\tpublic bool BoolReferenceField { get; set; } = false;", output.c_str());
    }

#pragma endregion

    };
  }
}