#include "UtilityHeaders/UnitTestHeaders.h"

#include "Bindings/InputDataBindingGenerators.h"

using namespace Celeste::Input;
using namespace Celeste::Bindings;


namespace TestCeleste
{
  namespace Bindings
  {
    CELESTE_TEST_CLASS(TestKeyDataBindingGenerator)

#pragma region Generate Binding Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyDataBindingGenerator_GenerateBinding_Value_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<Key, false>::generateBinding("key_value_field", Key(GLFW_KEY_A), output);

      Assert::AreEqual("\t\t[XmlAttribute(\"key_value_field\"), DisplayName(\"Key Value Field\")]\n\t\tpublic Key KeyValueField { get; set; } = Key.A;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<Key, false>::generateBinding("key_value_field", Key(GLFW_KEY_A), output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"key_value_field\"), DisplayName(\"Key Value Field\")]\n\t\tpublic Key KeyValueField { get; set; } = Key.A;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyDataBindingGenerator_GenerateBinding_Value_GLFW_KEY_UNKNOWN_AppendsCorrectUnknownText)
    {
      std::string output;
      DataBindingGenerator<Key, false>::generateBinding("key_value_field", Key(GLFW_KEY_UNKNOWN), output);

      Assert::AreEqual("\t\t[XmlAttribute(\"key_value_field\"), DisplayName(\"Key Value Field\")]\n\t\tpublic Key KeyValueField { get; set; } = Key.Unknown;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<Key, false>::generateBinding("key_value_field", Key(GLFW_KEY_UNKNOWN), output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"key_value_field\"), DisplayName(\"Key Value Field\")]\n\t\tpublic Key KeyValueField { get; set; } = Key.Unknown;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyDataBindingGenerator_GenerateBinding_Reference_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<Key, true>::generateBinding("key_reference_field", Key(GLFW_KEY_A), output);

      Assert::AreEqual("\t\t[XmlAttribute(\"key_reference_field\"), DisplayName(\"Key Reference Field\")]\n\t\tpublic Key KeyReferenceField { get; set; } = Key.A;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<Key, true>::generateBinding("key_reference_field", Key(GLFW_KEY_A), output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"key_reference_field\"), DisplayName(\"Key Reference Field\")]\n\t\tpublic Key KeyReferenceField { get; set; } = Key.A;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(KeyDataBindingGenerator_GenerateBinding_Reference_GLFW_KEY_UNKNOWN_AppendsCorrectUnknownText)
    {
      std::string output;
      DataBindingGenerator<Key, true>::generateBinding("key_reference_field", Key(GLFW_KEY_UNKNOWN), output);

      Assert::AreEqual("\t\t[XmlAttribute(\"key_reference_field\"), DisplayName(\"Key Reference Field\")]\n\t\tpublic Key KeyReferenceField { get; set; } = Key.Unknown;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<Key, true>::generateBinding("key_reference_field", Key(GLFW_KEY_UNKNOWN), output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"key_reference_field\"), DisplayName(\"Key Reference Field\")]\n\t\tpublic Key KeyReferenceField { get; set; } = Key.Unknown;", output.c_str());
    }

#pragma endregion

    };
  }
}