#include "Bindings/MathsDataBindingGenerators.h"
#include "TestUtils/UtilityHeaders/UnitTestHeaders.h"

using namespace Celeste;
using namespace Celeste::Bindings;


namespace TestCeleste
{
  namespace Bindings
  {
    CELESTE_TEST_CLASS(TestGLMUVector3DataBindingGenerator)

#pragma region Generate Binding Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMUVector3DataBindingGenerator_GenerateBinding_Value_AppendsCorrectText)
    {
      std::string output, expected("\t\t[XmlAttribute(\"unsigned_int_vector3_value_field\"), DisplayName(\"Unsigned Int Vector3 Value Field\")]\n\t\tpublic UnsignedIntVector3 UnsignedIntVector3ValueField { get; set; } = new UnsignedIntVector3(");
      expected.append(std::to_string(5));
      expected.append("f, ");
      expected.append(std::to_string(666));
      expected.append("f, ");
      expected.append(std::to_string(1234));
      expected.append("f);");
      DataBindingGenerator<glm::uvec3, false>::generateBinding("unsigned_int_vector3_value_field", glm::uvec3(5, 666, 1234), output);

      Assert::AreEqual(expected, output);

      output.assign("WubbaLubbaDubDub");
      expected = "WubbaLubbaDubDub" + expected;
      DataBindingGenerator<glm::uvec3, false>::generateBinding("unsigned_int_vector3_value_field", glm::uvec3(5, 666, 1234), output);

      Assert::AreEqual(expected, output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMUVector3DataBindingGenerator_GenerateBinding_Reference_AppendsCorrectText)
    {
      std::string output, expected("\t\t[XmlAttribute(\"unsigned_int_vector3_reference_field\"), DisplayName(\"Unsigned Int Vector3 Reference Field\")]\n\t\tpublic UnsignedIntVector3 UnsignedIntVector3ReferenceField { get; set; } = new UnsignedIntVector3(");
      expected.append(std::to_string(5));
      expected.append("f, ");
      expected.append(std::to_string(666));
      expected.append("f, ");
      expected.append(std::to_string(1234));
      expected.append("f);");
      DataBindingGenerator<glm::uvec3, true>::generateBinding("unsigned_int_vector3_reference_field", glm::uvec3(5, 666, 1234), output);

      Assert::AreEqual(expected, output);

      output.assign("WubbaLubbaDubDub");
      expected = "WubbaLubbaDubDub" + expected;
      DataBindingGenerator<glm::uvec3, true>::generateBinding("unsigned_int_vector3_reference_field", glm::uvec3(5, 666, 1234), output);

      Assert::AreEqual(expected, output);
    }

#pragma endregion

    };
  }
}