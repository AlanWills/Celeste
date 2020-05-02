#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Bindings/MathsDataBindingGenerators.h"

using namespace Celeste::Bindings;


namespace TestCeleste
{
  namespace Bindings
  {
    CELESTE_TEST_CLASS(TestGLMVector4DataBindingGenerator)

#pragma region Generate Binding Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector4DataBindingGenerator_GenerateBinding_Value_AppendsCorrectText)
    {
      std::string output, expected("\t\t[XmlAttribute(\"vector4_value_field\"), DisplayName(\"Vector4 Value Field\")]\n\t\tpublic Vector4 Vector4ValueField { get; set; } = new Vector4(");
      expected.append(std::to_string(-5.1123123f));
      expected.append("f, ");
      expected.append(std::to_string(666.0f));
      expected.append("f, ");
      expected.append(std::to_string(0.1234f));
      expected.append("f, ");
      expected.append(std::to_string(0.0f));
      expected.append("f);");
      DataBindingGenerator<glm::vec4, false>::generateBinding("vector4_value_field", glm::vec4(-5.1123123f, 666.0f, 0.1234f, 0.0f), output);

      Assert::AreEqual(expected, output);

      output.assign("WubbaLubbaDubDub");
      expected = "WubbaLubbaDubDub" + expected;
      DataBindingGenerator<glm::vec4, false>::generateBinding("vector4_value_field", glm::vec4(-5.1123123f, 666.0f, 0.1234f, 0.0f), output);

      Assert::AreEqual(expected, output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector4DataBindingGenerator_GenerateBinding_Reference_AppendsCorrectText)
    {
      std::string output, expected("\t\t[XmlAttribute(\"vector4_reference_field\"), DisplayName(\"Vector4 Reference Field\")]\n\t\tpublic Vector4 Vector4ReferenceField { get; set; } = new Vector4(");
      expected.append(std::to_string(-5.1123123f));
      expected.append("f, ");
      expected.append(std::to_string(666.0f));
      expected.append("f, ");
      expected.append(std::to_string(0.1234f));
      expected.append("f, ");
      expected.append(std::to_string(0.0f));
      expected.append("f);");
      DataBindingGenerator<glm::vec4, true>::generateBinding("vector4_reference_field", glm::vec4(-5.1123123f, 666.0f, 0.1234f, 0.0f), output);

      Assert::AreEqual(expected, output);

      output.assign("WubbaLubbaDubDub");
      expected = "WubbaLubbaDubDub" + expected;
      DataBindingGenerator<glm::vec4, true>::generateBinding("vector4_reference_field", glm::vec4(-5.1123123f, 666.0f, 0.1234f, 0.0f), output);

      Assert::AreEqual(expected, output);
    }

#pragma endregion

    };
  }
}