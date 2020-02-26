#include "Bindings/MathsDataBindingGenerators.h"
#include "UtilityHeaders/UnitTestHeaders.h"

using namespace Celeste;
using namespace Celeste::Bindings;


namespace TestCeleste
{
  namespace Bindings
  {
    CELESTE_TEST_CLASS(TestGLMUVector2DataBindingGenerator)

#pragma region Generate Binding Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMUVector2DataBindingGenerator_GenerateBinding_Value_AppendsCorrectText)
    {
      std::string output, expected("\t\t[XmlAttribute(\"unsigned_int_vector2_value_field\"), DisplayName(\"Unsigned Int Vector2 Value Field\")]\n\t\tpublic UnsignedIntVector2 UnsignedIntVector2ValueField { get; set; } = new UnsignedIntVector2(");
      expected.append(std::to_string(5));
      expected.append(", ");
      expected.append(std::to_string(666));
      expected.append(");");
      DataBindingGenerator<glm::uvec2, false>::generateBinding("unsigned_int_vector2_value_field", glm::uvec2(5, 666), output);

      Assert::AreEqual(expected, output);

      output.assign("WubbaLubbaDubDub");
      expected = "WubbaLubbaDubDub" + expected;
      DataBindingGenerator<glm::uvec2, false>::generateBinding("unsigned_int_vector2_value_field", glm::uvec2(5, 666), output);

      Assert::AreEqual(expected, output);
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(GLMUVector2DataBindingGenerator_GenerateBinding_Reference_AppendsCorrectText)
    {
      std::string output, expected("\t\t[XmlAttribute(\"unsigned_int_vector2_reference_field\"), DisplayName(\"Unsigned Int Vector2 Reference Field\")]\n\t\tpublic UnsignedIntVector2 UnsignedIntVector2ReferenceField { get; set; } = new UnsignedIntVector2(");
      expected.append(std::to_string(5));
      expected.append(", ");
      expected.append(std::to_string(666));
      expected.append(");");
      DataBindingGenerator<glm::uvec2, true>::generateBinding("unsigned_int_vector2_reference_field", glm::uvec2(5, 666), output);

      Assert::AreEqual(expected, output);

      output.assign("WubbaLubbaDubDub");
      expected = "WubbaLubbaDubDub" + expected;
      DataBindingGenerator<glm::uvec2, true>::generateBinding("unsigned_int_vector2_reference_field", glm::uvec2(5, 666), output);

      Assert::AreEqual(expected, output);
    }

#pragma endregion

    };
  }
}