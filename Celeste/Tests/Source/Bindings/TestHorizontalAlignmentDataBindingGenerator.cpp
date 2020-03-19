#include "Bindings/UIDataBindingGenerators.h"
#include "UtilityHeaders/UnitTestHeaders.h"

using namespace Celeste;
using namespace Celeste::Bindings;


namespace TestCeleste
{
  namespace Bindings
  {
    CELESTE_TEST_CLASS(TestHorizontalAlignmentDataBindingGenerator)

#pragma region Generate Binding Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(HorizontalAlignmentDataBindingGenerator_GenerateValueBindingFor_kLeft_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<UI::HorizontalAlignment, false>::generateBinding("horizontal_alignment_value_field", UI::HorizontalAlignment::kLeft, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"horizontal_alignment_value_field\"), DisplayName(\"Horizontal Alignment Value Field\")]\n\t\tpublic HorizontalAlignment HorizontalAlignmentValueField { get; set; } = HorizontalAlignment.Left;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<UI::HorizontalAlignment, false>::generateBinding("horizontal_alignment_value_field", UI::HorizontalAlignment::kLeft, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"horizontal_alignment_value_field\"), DisplayName(\"Horizontal Alignment Value Field\")]\n\t\tpublic HorizontalAlignment HorizontalAlignmentValueField { get; set; } = HorizontalAlignment.Left;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(HorizontalAlignmentDataBindingGenerator_GenerateValueBindingFor_kCentre_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<UI::HorizontalAlignment, false>::generateBinding("horizontal_alignment_value_field", UI::HorizontalAlignment::kCentre, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"horizontal_alignment_value_field\"), DisplayName(\"Horizontal Alignment Value Field\")]\n\t\tpublic HorizontalAlignment HorizontalAlignmentValueField { get; set; } = HorizontalAlignment.Centre;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<UI::HorizontalAlignment, false>::generateBinding("horizontal_alignment_value_field", UI::HorizontalAlignment::kCentre, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"horizontal_alignment_value_field\"), DisplayName(\"Horizontal Alignment Value Field\")]\n\t\tpublic HorizontalAlignment HorizontalAlignmentValueField { get; set; } = HorizontalAlignment.Centre;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(HorizontalAlignmentDataBindingGenerator_GenerateValueBindingFor_kRight_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<UI::HorizontalAlignment, false>::generateBinding("horizontal_alignment_value_field", UI::HorizontalAlignment::kRight, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"horizontal_alignment_value_field\"), DisplayName(\"Horizontal Alignment Value Field\")]\n\t\tpublic HorizontalAlignment HorizontalAlignmentValueField { get; set; } = HorizontalAlignment.Right;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<UI::HorizontalAlignment, false>::generateBinding("horizontal_alignment_value_field", UI::HorizontalAlignment::kRight, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"horizontal_alignment_value_field\"), DisplayName(\"Horizontal Alignment Value Field\")]\n\t\tpublic HorizontalAlignment HorizontalAlignmentValueField { get; set; } = HorizontalAlignment.Right;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(HorizontalAlignmentDataBindingGenerator_GenerateReferenceBindingFor_kLeft_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<UI::HorizontalAlignment, true>::generateBinding("horizontal_alignment_reference_field", UI::HorizontalAlignment::kLeft, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"horizontal_alignment_reference_field\"), DisplayName(\"Horizontal Alignment Reference Field\")]\n\t\tpublic HorizontalAlignment HorizontalAlignmentReferenceField { get; set; } = HorizontalAlignment.Left;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<UI::HorizontalAlignment, true>::generateBinding("horizontal_alignment_reference_field", UI::HorizontalAlignment::kLeft, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"horizontal_alignment_reference_field\"), DisplayName(\"Horizontal Alignment Reference Field\")]\n\t\tpublic HorizontalAlignment HorizontalAlignmentReferenceField { get; set; } = HorizontalAlignment.Left;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(HorizontalAlignmentDataBindingGenerator_GenerateReferenceBindingFor_kCentre_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<UI::HorizontalAlignment, true>::generateBinding("horizontal_alignment_reference_field", UI::HorizontalAlignment::kCentre, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"horizontal_alignment_reference_field\"), DisplayName(\"Horizontal Alignment Reference Field\")]\n\t\tpublic HorizontalAlignment HorizontalAlignmentReferenceField { get; set; } = HorizontalAlignment.Centre;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<UI::HorizontalAlignment, true>::generateBinding("horizontal_alignment_reference_field", UI::HorizontalAlignment::kCentre, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"horizontal_alignment_reference_field\"), DisplayName(\"Horizontal Alignment Reference Field\")]\n\t\tpublic HorizontalAlignment HorizontalAlignmentReferenceField { get; set; } = HorizontalAlignment.Centre;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(HorizontalAlignmentDataBindingGenerator_GenerateReferenceBindingFor_kRight_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<UI::HorizontalAlignment, true>::generateBinding("horizontal_alignment_reference_field", UI::HorizontalAlignment::kRight, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"horizontal_alignment_reference_field\"), DisplayName(\"Horizontal Alignment Reference Field\")]\n\t\tpublic HorizontalAlignment HorizontalAlignmentReferenceField { get; set; } = HorizontalAlignment.Right;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<UI::HorizontalAlignment, true>::generateBinding("horizontal_alignment_reference_field", UI::HorizontalAlignment::kRight, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"horizontal_alignment_reference_field\"), DisplayName(\"Horizontal Alignment Reference Field\")]\n\t\tpublic HorizontalAlignment HorizontalAlignmentReferenceField { get; set; } = HorizontalAlignment.Right;", output.c_str());
    }

#pragma endregion

    };
  }
}