#include "Bindings/MathsDataBindingGenerators.h"
#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

using namespace Celeste;
using namespace Celeste::Bindings;


namespace TestCeleste
{
  namespace Bindings
  {
    CELESTE_TEST_CLASS(TestGLMUVector4DataBindingGenerator)

#pragma region Generate Binding Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMUVector4DataBindingGenerator_GenerateBinding_Value_AppendsCorrectText)
    {
      std::string output, expected("\t\t[XmlAttribute(\"unsigned_int_vector4_value_field\"), DisplayName(\"Unsigned Int Vector4 Value Field\")]\n\t\tpublic UnsignedIntVector4 UnsignedIntVector4ValueField { get; set; } = new UnsignedIntVector4(");
      expected.append(std::to_string(5));
      expected.append("f, ");
      expected.append(std::to_string(666));
      expected.append("f, ");
      expected.append(std::to_string(1234));
      expected.append("f, ");
      expected.append(std::to_string(0));
      expected.append("f);");
      DataBindingGenerator<glm::uvec4, false>::generateBinding("unsigned_int_vector4_value_field", glm::uvec4(5, 666, 1234, 0), output);

      Assert::AreEqual(expected, output);

      output.assign("WubbaLubbaDubDub");
      expected = "WubbaLubbaDubDub" + expected;
      DataBindingGenerator<glm::uvec4, false>::generateBinding("unsigned_int_vector4_value_field", glm::vec4(5, 666, 1234, 0), output);

      Assert::AreEqual(expected, output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMUVector4DataBindingGenerator_GenerateBinding_Reference_AppendsCorrectText)
    {
      std::string output, expected("\t\t[XmlAttribute(\"unsigned_int_vector4_reference_field\"), DisplayName(\"Unsigned Int Vector4 Reference Field\")]\n\t\tpublic UnsignedIntVector4 UnsignedIntVector4ReferenceField { get; set; } = new UnsignedIntVector4(");
      expected.append(std::to_string(5));
      expected.append("f, ");
      expected.append(std::to_string(666));
      expected.append("f, ");
      expected.append(std::to_string(1234));
      expected.append("f, ");
      expected.append(std::to_string(0));
      expected.append("f);");
      DataBindingGenerator<glm::uvec4, true>::generateBinding("unsigned_int_vector4_reference_field", glm::vec4(5, 666, 1234, 0), output);

      Assert::AreEqual(expected, output);

      output.assign("WubbaLubbaDubDub");
      expected = "WubbaLubbaDubDub" + expected;
      DataBindingGenerator<glm::uvec4, true>::generateBinding("unsigned_int_vector4_reference_field", glm::vec4(5, 666, 1234, 0), output);

      Assert::AreEqual(expected, output);
    }

#pragma endregion

    };
  }
}