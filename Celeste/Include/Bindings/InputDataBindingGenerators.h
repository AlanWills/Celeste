#pragma once

#include "DataBindingGenerators.h"
#include "Input/InputEnums.h"
#include "Input/Key.h"


namespace Celeste
{
  namespace Bindings
  {
    //------------------------------------------------------------------------------------------------
    template <bool is_reference>
    struct DataBindingGenerator<Input::IncrementMode, is_reference>
    {
      DECLARE_DATA_BINDING_GENERATOR(Input::IncrementMode)

      private:
        static void generatePropertyBinding(
          const std::string& variableName,
          typename choose_class<static_cast<bool>(is_reference), const Input::IncrementMode&, Input::IncrementMode>::type value,
          std::string& output)
        {
          output.append("public IncrementMode ");
          output.append(variableName);
          output.append(" { get; set; } = IncrementMode.");
          output.append(to_string(value));
          output.push_back(';');
        }
    };

    //------------------------------------------------------------------------------------------------
    template <bool is_reference>
    struct DataBindingGenerator<Input::Key, is_reference>
    {
      DECLARE_DATA_BINDING_GENERATOR(Input::Key)

      private:
        static void generatePropertyBinding(
          const std::string& variableName,
          typename choose_class<static_cast<bool>(is_reference), const Input::Key&, Input::Key>::type value,
          std::string& output)
        {
          output.append("public Key ");
          output.append(variableName);
          output.append(" { get; set; } = Key.");

          if (value.m_key == GLFW_KEY_UNKNOWN)
          {
            output.append("Unknown");
          }
          else
          {
            output.append(Bindings::displayNameToVariableName(to_string(value)));
          }

          output.push_back(';');
        }
    };
  }
}