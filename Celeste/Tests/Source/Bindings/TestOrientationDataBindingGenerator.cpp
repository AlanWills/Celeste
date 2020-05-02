#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Bindings/UIDataBindingGenerators.h"

using namespace Celeste;
using namespace Celeste::Bindings;


namespace TestCeleste
{
  namespace Bindings
  {
    CELESTE_TEST_CLASS(TestOrientationDataBindingGenerator)

#pragma region Generate Binding Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(OrientationDataBindingGenerator_GenerateValueBindingFor_kVertical_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<UI::Orientation, false>::generateBinding("orientation_value_field", UI::Orientation::kVertical, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"orientation_value_field\"), DisplayName(\"Orientation Value Field\")]\n\t\tpublic Orientation OrientationValueField { get; set; } = Orientation.Vertical;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<UI::Orientation, false>::generateBinding("orientation_value_field", UI::Orientation::kVertical, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"orientation_value_field\"), DisplayName(\"Orientation Value Field\")]\n\t\tpublic Orientation OrientationValueField { get; set; } = Orientation.Vertical;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(OrientationDataBindingGenerator_GenerateValueBindingFor_kHorizontal_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<UI::Orientation, false>::generateBinding("orientation_value_field", UI::Orientation::kHorizontal, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"orientation_value_field\"), DisplayName(\"Orientation Value Field\")]\n\t\tpublic Orientation OrientationValueField { get; set; } = Orientation.Horizontal;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<UI::Orientation, false>::generateBinding("orientation_value_field", UI::Orientation::kHorizontal, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"orientation_value_field\"), DisplayName(\"Orientation Value Field\")]\n\t\tpublic Orientation OrientationValueField { get; set; } = Orientation.Horizontal;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(OrientationDataBindingGenerator_GenerateReferenceBindingFor_kVertical_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<UI::Orientation, true>::generateBinding("orientation_reference_field", UI::Orientation::kVertical, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"orientation_reference_field\"), DisplayName(\"Orientation Reference Field\")]\n\t\tpublic Orientation OrientationReferenceField { get; set; } = Orientation.Vertical;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<UI::Orientation, true>::generateBinding("orientation_reference_field", UI::Orientation::kVertical, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"orientation_reference_field\"), DisplayName(\"Orientation Reference Field\")]\n\t\tpublic Orientation OrientationReferenceField { get; set; } = Orientation.Vertical;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(OrientationDataBindingGenerator_GenerateReferenceBindingFor_kHorizontal_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<UI::Orientation, true>::generateBinding("orientation_reference_field", UI::Orientation::kHorizontal, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"orientation_reference_field\"), DisplayName(\"Orientation Reference Field\")]\n\t\tpublic Orientation OrientationReferenceField { get; set; } = Orientation.Horizontal;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<UI::Orientation, true>::generateBinding("orientation_reference_field", UI::Orientation::kHorizontal, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"orientation_reference_field\"), DisplayName(\"Orientation Reference Field\")]\n\t\tpublic Orientation OrientationReferenceField { get; set; } = Orientation.Horizontal;", output.c_str());
    }

#pragma endregion

    };
  }
}