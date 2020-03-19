#include "UtilityHeaders/UnitTestHeaders.h"

#include "Bindings/MathsDataBindingGenerators.h"

using namespace Celeste::Bindings;


namespace TestCeleste
{
  namespace Bindings
  {
    CELESTE_TEST_CLASS(TestGLMVector2DataBindingGenerator)

#pragma region Generate Binding Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector2DataBindingGenerator_GenerateBinding_Value_AppendsCorrectText)
    {
      std::string output, expected("\t\t[XmlAttribute(\"vector2_value_field\"), DisplayName(\"Vector2 Value Field\")]\n\t\tpublic Vector2 Vector2ValueField { get; set; } = new Vector2(");
      expected.append(std::to_string(-5.1123123f));
      expected.append("f, ");
      expected.append(std::to_string(666.0f));
      expected.append("f);");
      DataBindingGenerator<glm::vec2, false>::generateBinding("vector2_value_field", glm::vec2(-5.1123123f, 666.0f), output);

      Assert::AreEqual(expected, output);

      output.assign("WubbaLubbaDubDub");
      expected = "WubbaLubbaDubDub" + expected;
      DataBindingGenerator<glm::vec2, false>::generateBinding("vector2_value_field", glm::vec2(-5.1123123f, 666.0f), output);

      Assert::AreEqual(expected, output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector2DataBindingGenerator_GenerateBinding_Reference_AppendsCorrectText)
    {
      std::string output, expected("\t\t[XmlAttribute(\"vector2_reference_field\"), DisplayName(\"Vector2 Reference Field\")]\n\t\tpublic Vector2 Vector2ReferenceField { get; set; } = new Vector2(");
      expected.append(std::to_string(-5.1123123f));
      expected.append("f, ");
      expected.append(std::to_string(666.0f));
      expected.append("f);");
      DataBindingGenerator<glm::vec2, true>::generateBinding("vector2_reference_field", glm::vec2(-5.1123123f, 666.0f), output);

      Assert::AreEqual(expected, output);

      output.assign("WubbaLubbaDubDub");
      expected = "WubbaLubbaDubDub" + expected;
      DataBindingGenerator<glm::vec2, true>::generateBinding("vector2_reference_field", glm::vec2(-5.1123123f, 666.0f), output);

      Assert::AreEqual(expected, output);
    }

#pragma endregion

  };
}
}