#pragma once

#include "DataBindingGenerators.h"
#include "Audio/AudioEnums.h"


namespace Celeste
{
  namespace Bindings
  {
    //------------------------------------------------------------------------------------------------
    template <bool is_reference>
    struct DataBindingGenerator<Audio::AudioType, is_reference>
    {
      DECLARE_DATA_BINDING_GENERATOR(Audio::AudioType)

      private:
        static void generatePropertyBinding(
          const std::string& variableName,
          typename choose_class<static_cast<bool>(is_reference), const Audio::AudioType&, Audio::AudioType>::type value,
          std::string& output)
        {
          output.append("public AudioType ");
          output.append(variableName);
          output.append(" { get; set; } = AudioType.");
          output.append(to_string(value));
          output.push_back(';');
        }
    };
  }
}