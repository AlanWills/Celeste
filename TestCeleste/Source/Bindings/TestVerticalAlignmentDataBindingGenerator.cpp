#include "UtilityHeaders/UnitTestHeaders.h"

#include "Bindings/UIDataBindingGenerators.h"

using namespace Celeste;
using namespace Celeste::Bindings;


namespace TestCeleste
{
  namespace Bindings
  {
    CELESTE_TEST_CLASS(TestVerticalAlignmentDataBindingGenerator)

#pragma region Generate Binding Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(VerticalAlignmentDataBindingGenerator_GenerateValueBindingFor_kTop_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<UI::VerticalAlignment, false>::generateBinding("vertical_alignment_value_field", UI::VerticalAlignment::kTop, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"vertical_alignment_value_field\"), DisplayName(\"Vertical Alignment Value Field\")]\n\t\tpublic VerticalAlignment VerticalAlignmentValueField { get; set; } = VerticalAlignment.Top;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<UI::VerticalAlignment, false>::generateBinding("vertical_alignment_value_field", UI::VerticalAlignment::kTop, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"vertical_alignment_value_field\"), DisplayName(\"Vertical Alignment Value Field\")]\n\t\tpublic VerticalAlignment VerticalAlignmentValueField { get; set; } = VerticalAlignment.Top;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(VerticalAlignmentDataBindingGenerator_GenerateValueBindingFor_kCentre_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<UI::VerticalAlignment, false>::generateBinding("vertical_alignment_value_field", UI::VerticalAlignment::kCentre, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"vertical_alignment_value_field\"), DisplayName(\"Vertical Alignment Value Field\")]\n\t\tpublic VerticalAlignment VerticalAlignmentValueField { get; set; } = VerticalAlignment.Centre;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<UI::VerticalAlignment, false>::generateBinding("vertical_alignment_value_field", UI::VerticalAlignment::kCentre, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"vertical_alignment_value_field\"), DisplayName(\"Vertical Alignment Value Field\")]\n\t\tpublic VerticalAlignment VerticalAlignmentValueField { get; set; } = VerticalAlignment.Centre;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(VerticalAlignmentDataBindingGenerator_GenerateValueBindingFor_kBottom_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<UI::VerticalAlignment, false>::generateBinding("vertical_alignment_value_field", UI::VerticalAlignment::kBottom, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"vertical_alignment_value_field\"), DisplayName(\"Vertical Alignment Value Field\")]\n\t\tpublic VerticalAlignment VerticalAlignmentValueField { get; set; } = VerticalAlignment.Bottom;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<UI::VerticalAlignment, false>::generateBinding("vertical_alignment_value_field", UI::VerticalAlignment::kBottom, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"vertical_alignment_value_field\"), DisplayName(\"Vertical Alignment Value Field\")]\n\t\tpublic VerticalAlignment VerticalAlignmentValueField { get; set; } = VerticalAlignment.Bottom;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(VerticalAlignmentDataBindingGenerator_GenerateReferenceBindingFor_kTop_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<UI::VerticalAlignment, true>::generateBinding("vertical_alignment_reference_field", UI::VerticalAlignment::kTop, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"vertical_alignment_reference_field\"), DisplayName(\"Vertical Alignment Reference Field\")]\n\t\tpublic VerticalAlignment VerticalAlignmentReferenceField { get; set; } = VerticalAlignment.Top;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<UI::VerticalAlignment, true>::generateBinding("vertical_alignment_reference_field", UI::VerticalAlignment::kTop, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"vertical_alignment_reference_field\"), DisplayName(\"Vertical Alignment Reference Field\")]\n\t\tpublic VerticalAlignment VerticalAlignmentReferenceField { get; set; } = VerticalAlignment.Top;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(VerticalAlignmentDataBindingGenerator_GenerateReferenceBindingFor_kCentre_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<UI::VerticalAlignment, true>::generateBinding("vertical_alignment_reference_field", UI::VerticalAlignment::kCentre, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"vertical_alignment_reference_field\"), DisplayName(\"Vertical Alignment Reference Field\")]\n\t\tpublic VerticalAlignment VerticalAlignmentReferenceField { get; set; } = VerticalAlignment.Centre;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<UI::VerticalAlignment, true>::generateBinding("vertical_alignment_reference_field", UI::VerticalAlignment::kCentre, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"vertical_alignment_reference_field\"), DisplayName(\"Vertical Alignment Reference Field\")]\n\t\tpublic VerticalAlignment VerticalAlignmentReferenceField { get; set; } = VerticalAlignment.Centre;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(VerticalAlignmentDataBindingGenerator_GenerateReferenceBindingFor_kBottom_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<UI::VerticalAlignment, true>::generateBinding("vertical_alignment_reference_field", UI::VerticalAlignment::kBottom, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"vertical_alignment_reference_field\"), DisplayName(\"Vertical Alignment Reference Field\")]\n\t\tpublic VerticalAlignment VerticalAlignmentReferenceField { get; set; } = VerticalAlignment.Bottom;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<UI::VerticalAlignment, true>::generateBinding("vertical_alignment_reference_field", UI::VerticalAlignment::kBottom, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"vertical_alignment_reference_field\"), DisplayName(\"Vertical Alignment Reference Field\")]\n\t\tpublic VerticalAlignment VerticalAlignmentReferenceField { get; set; } = VerticalAlignment.Bottom;", output.c_str());
    }

#pragma endregion

    };
  }
}