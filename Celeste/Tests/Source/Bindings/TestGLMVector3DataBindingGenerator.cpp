#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

#include "Bindings/MathsDataBindingGenerators.h"

using namespace Celeste::Bindings;


namespace TestCeleste
{
  namespace Bindings
  {
    CELESTE_TEST_CLASS(TestGLMVector3DataBindingGenerator)

#pragma region Generate Binding Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector3DataBindingGenerator_GenerateBinding_Value_AppendsCorrectText)
    {
      std::string output, expected("\t\t[XmlAttribute(\"vector3_value_field\"), DisplayName(\"Vector3 Value Field\")]\n\t\tpublic Vector3 Vector3ValueField { get; set; } = new Vector3(");
      expected.append(std::to_string(-5.1123123f));
      expected.append("f, ");
      expected.append(std::to_string(666.0f));
      expected.append("f, ");
      expected.append(std::to_string(0.1234f));
      expected.append("f);");
      DataBindingGenerator<glm::vec3, false>::generateBinding("vector3_value_field", glm::vec3(-5.1123123f, 666.0f, 0.1234f), output);

      Assert::AreEqual(expected, output);

      output.assign("WubbaLubbaDubDub");
      expected = "WubbaLubbaDubDub" + expected;
      DataBindingGenerator<glm::vec3, false>::generateBinding("vector3_value_field", glm::vec3(-5.1123123f, 666.0f, 0.1234f), output);

      Assert::AreEqual(expected, output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMVector3DataBindingGenerator_GenerateBinding_Reference_AppendsCorrectText)
    {
      std::string output, expected("\t\t[XmlAttribute(\"vector3_reference_field\"), DisplayName(\"Vector3 Reference Field\")]\n\t\tpublic Vector3 Vector3ReferenceField { get; set; } = new Vector3(");
      expected.append(std::to_string(-5.1123123f));
      expected.append("f, ");
      expected.append(std::to_string(666.0f));
      expected.append("f, ");
      expected.append(std::to_string(0.1234f));
      expected.append("f);");
      DataBindingGenerator<glm::vec3, true>::generateBinding("vector3_reference_field", glm::vec3(-5.1123123f, 666.0f, 0.1234f), output);

      Assert::AreEqual(expected, output);

      output.assign("WubbaLubbaDubDub");
      expected = "WubbaLubbaDubDub" + expected;
      DataBindingGenerator<glm::vec3, true>::generateBinding("vector3_reference_field", glm::vec3(-5.1123123f, 666.0f, 0.1234f), output);

      Assert::AreEqual(expected, output);
    }

#pragma endregion

  };
}
}