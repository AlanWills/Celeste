#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Bindings/DataBindingGenerators.h"

using namespace Celeste;
using namespace Celeste::Bindings;


namespace TestCeleste
{
  namespace Bindings
  {
    CELESTE_TEST_CLASS(TestPathDataBindingGenerator)

#pragma region Generate Binding Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(PathDataBindingGenerator_GenerateBinding_Value_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<Path, false>::generateBinding("path_value_field", Path("Parent", "TestPath.xml"), output);

      Assert::AreEqual("\t\t[XmlAttribute(\"path_value_field\"), DisplayName(\"Path Value Field\")]\n\t\tpublic Path PathValueField { get; set; } = new Path(@\"Parent\\TestPath.xml\");", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<Path, false>::generateBinding("path_value_field", Path("Parent", "TestPath.xml"), output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"path_value_field\"), DisplayName(\"Path Value Field\")]\n\t\tpublic Path PathValueField { get; set; } = new Path(@\"Parent\\TestPath.xml\");", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(PathDataBindingGenerator_GenerateBinding_Reference_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<Path, true>::generateBinding("path_reference_field", Path("Parent", "TestPath.xml"), output);

      Assert::AreEqual("\t\t[XmlAttribute(\"path_reference_field\"), DisplayName(\"Path Reference Field\")]\n\t\tpublic Path PathReferenceField { get; set; } = new Path(@\"Parent\\TestPath.xml\");", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<Path, true>::generateBinding("path_reference_field", Path("Parent", "TestPath.xml"), output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"path_reference_field\"), DisplayName(\"Path Reference Field\")]\n\t\tpublic Path PathReferenceField { get; set; } = new Path(@\"Parent\\TestPath.xml\");", output.c_str());
    }

#pragma endregion

  };
}
}