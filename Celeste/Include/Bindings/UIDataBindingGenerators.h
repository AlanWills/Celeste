#pragma once

#include "DataBindingGenerators.h"
#include "UI/LayoutEnums.h"


namespace Celeste
{
  namespace Bindings
  {
    //------------------------------------------------------------------------------------------------
    template <bool is_reference>
    struct DataBindingGenerator<UI::VerticalAlignment, is_reference>
    {
      DECLARE_DATA_BINDING_GENERATOR(UI::VerticalAlignment)

      private:
        static void generatePropertyBinding(
          const std::string& variableName,
          typename choose_class<static_cast<bool>(is_reference), const UI::VerticalAlignment&, UI::VerticalAlignment>::type value,
          std::string& output)
        {
          output.append("public VerticalAlignment ");
          output.append(variableName);
          output.append(" { get; set; } = VerticalAlignment.");
          output.append(to_string(value));
          output.push_back(';');
        }
    };

    //------------------------------------------------------------------------------------------------
    template <bool is_reference>
    struct DataBindingGenerator<UI::HorizontalAlignment, is_reference>
    {
      DECLARE_DATA_BINDING_GENERATOR(UI::HorizontalAlignment)

      private:
        static void generatePropertyBinding(
          const std::string& variableName,
          typename choose_class<static_cast<bool>(is_reference), const UI::HorizontalAlignment&, UI::HorizontalAlignment>::type value,
          std::string& output)
        {
          output.append("public HorizontalAlignment ");
          output.append(variableName);
          output.append(" { get; set; } = HorizontalAlignment.");
          output.append(to_string(value));
          output.push_back(';');
        }
    };

    //------------------------------------------------------------------------------------------------
    template <bool is_reference>
    struct DataBindingGenerator<UI::Orientation, is_reference>
    {
      DECLARE_DATA_BINDING_GENERATOR(UI::Orientation)

      private:
        static void generatePropertyBinding(
          const std::string& variableName,
          typename choose_class<static_cast<bool>(is_reference), const UI::Orientation&, UI::Orientation>::type value,
          std::string& output)
        {
          output.append("public Orientation ");
          output.append(variableName);
          output.append(" { get; set; } = Orientation.");
          output.append(to_string(value));
          output.push_back(';');
        }
    };
  }
}