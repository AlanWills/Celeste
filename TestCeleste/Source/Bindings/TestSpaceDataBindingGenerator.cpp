#include "UtilityHeaders/UnitTestHeaders.h"

#include "Bindings/MathsDataBindingGenerators.h"

using namespace Celeste;
using namespace Celeste::Bindings;


namespace TestCeleste
{
  namespace Bindings
  {
    CELESTE_TEST_CLASS(TestSpaceDataBindingGenerator)

#pragma region Generate Binding Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(SpaceDataBindingGenerator_GenerateValueBindingFor_kWorld_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<Maths::Space, false>::generateBinding("space_value_field", Maths::Space::kWorld, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"space_value_field\"), DisplayName(\"Space Value Field\")]\n\t\tpublic Space SpaceValueField { get; set; } = Space.World;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<Maths::Space, false>::generateBinding("space_value_field", Maths::Space::kWorld, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"space_value_field\"), DisplayName(\"Space Value Field\")]\n\t\tpublic Space SpaceValueField { get; set; } = Space.World;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(SpaceDataBindingGenerator_GenerateValueBindingFor_kLocal_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<Maths::Space, false>::generateBinding("space_value_field", Maths::Space::kLocal, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"space_value_field\"), DisplayName(\"Space Value Field\")]\n\t\tpublic Space SpaceValueField { get; set; } = Space.Local;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<Maths::Space, false>::generateBinding("space_value_field", Maths::Space::kLocal, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"space_value_field\"), DisplayName(\"Space Value Field\")]\n\t\tpublic Space SpaceValueField { get; set; } = Space.Local;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(SpaceDataBindingGenerator_GenerateReferenceBindingFor_kWorld_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<Maths::Space, true>::generateBinding("space_reference_field", Maths::Space::kWorld, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"space_reference_field\"), DisplayName(\"Space Reference Field\")]\n\t\tpublic Space SpaceReferenceField { get; set; } = Space.World;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<Maths::Space, true>::generateBinding("space_reference_field", Maths::Space::kWorld, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"space_reference_field\"), DisplayName(\"Space Reference Field\")]\n\t\tpublic Space SpaceReferenceField { get; set; } = Space.World;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(SpaceDataBindingGenerator_GenerateReferenceBindingFor_kLocal_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<Maths::Space, true>::generateBinding("space_reference_field", Maths::Space::kLocal, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"space_reference_field\"), DisplayName(\"Space Reference Field\")]\n\t\tpublic Space SpaceReferenceField { get; set; } = Space.Local;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<Maths::Space, true>::generateBinding("space_reference_field", Maths::Space::kLocal, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"space_reference_field\"), DisplayName(\"Space Reference Field\")]\n\t\tpublic Space SpaceReferenceField { get; set; } = Space.Local;", output.c_str());
    }

#pragma endregion

    };
  }
}