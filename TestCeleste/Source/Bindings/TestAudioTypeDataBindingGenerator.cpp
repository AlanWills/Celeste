#include "Bindings/AudioDataBindingGenerators.h"
#include "UtilityHeaders/UnitTestHeaders.h"

using namespace Celeste;
using namespace Celeste::Bindings;


namespace TestCeleste
{
  namespace Bindings
  {
    CELESTE_TEST_CLASS(TestAudioTypeDataBindingGenerator)

#pragma region Generate Binding Tests

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioTypeDataBindingGenerator_GenerateValueBindingFor_kMusic_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<Audio::AudioType, false>::generateBinding("audio_type_value_field", Audio::AudioType::kMusic, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"audio_type_value_field\"), DisplayName(\"Audio Type Value Field\")]\n\t\tpublic AudioType AudioTypeValueField { get; set; } = AudioType.Music;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<Audio::AudioType, false>::generateBinding("audio_type_value_field", Audio::AudioType::kMusic, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"audio_type_value_field\"), DisplayName(\"Audio Type Value Field\")]\n\t\tpublic AudioType AudioTypeValueField { get; set; } = AudioType.Music;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioTypeDataBindingGenerator_GenerateValueBindingFor_kSFX_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<Audio::AudioType, false>::generateBinding("audio_type_value_field", Audio::AudioType::kSFX, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"audio_type_value_field\"), DisplayName(\"Audio Type Value Field\")]\n\t\tpublic AudioType AudioTypeValueField { get; set; } = AudioType.SFX;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<Audio::AudioType, false>::generateBinding("audio_type_value_field", Audio::AudioType::kSFX, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"audio_type_value_field\"), DisplayName(\"Audio Type Value Field\")]\n\t\tpublic AudioType AudioTypeValueField { get; set; } = AudioType.SFX;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioTypeDataBindingGenerator_GenerateReferenceBindingFor_kMusic_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<Audio::AudioType, true>::generateBinding("audio_type_reference_field", Audio::AudioType::kMusic, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"audio_type_reference_field\"), DisplayName(\"Audio Type Reference Field\")]\n\t\tpublic AudioType AudioTypeReferenceField { get; set; } = AudioType.Music;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<Audio::AudioType, true>::generateBinding("audio_type_reference_field", Audio::AudioType::kMusic, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"audio_type_reference_field\"), DisplayName(\"Audio Type Reference Field\")]\n\t\tpublic AudioType AudioTypeReferenceField { get; set; } = AudioType.Music;", output.c_str());
    }

    //------------------------------------------------------------------------------------------------
    TEST_METHOD(AudioTypeDataBindingGenerator_GenerateReferenceBindingFor_kSFX_AppendsCorrectText)
    {
      std::string output;
      DataBindingGenerator<Audio::AudioType, true>::generateBinding("audio_type_reference_field", Audio::AudioType::kSFX, output);

      Assert::AreEqual("\t\t[XmlAttribute(\"audio_type_reference_field\"), DisplayName(\"Audio Type Reference Field\")]\n\t\tpublic AudioType AudioTypeReferenceField { get; set; } = AudioType.SFX;", output.c_str());

      output.assign("WubbaLubbaDubDub");
      DataBindingGenerator<Audio::AudioType, true>::generateBinding("audio_type_reference_field", Audio::AudioType::kSFX, output);

      Assert::AreEqual("WubbaLubbaDubDub\t\t[XmlAttribute(\"audio_type_reference_field\"), DisplayName(\"Audio Type Reference Field\")]\n\t\tpublic AudioType AudioTypeReferenceField { get; set; } = AudioType.SFX;", output.c_str());
    }

#pragma endregion

    };
  }
}