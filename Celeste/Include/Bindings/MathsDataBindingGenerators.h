#pragma once

#include "DataBindingGenerators.h"
#include "Maths/MathsEnums.h"


namespace Celeste
{
  namespace Bindings
  {
    //------------------------------------------------------------------------------------------------
    template <bool is_reference>
    struct DataBindingGenerator<glm::vec2, is_reference>
    {
      DECLARE_DATA_BINDING_GENERATOR(glm::vec2)

      private:
        static void generatePropertyBinding(
          const std::string& variableName,
          typename choose_class<static_cast<bool>(is_reference), const glm::vec2&, glm::vec2>::type value,
          std::string& output)
        {
          output.append("public Vector2 ");
          output.append(variableName);
          output.append(" { get; set; } = ");
          output.append("new Vector2(");
          output.append(std::to_string(value.x));
          output.append("f, ");
          output.append(std::to_string(value.y));
          output.append("f);");
        }
    };

    //------------------------------------------------------------------------------------------------
    template <bool is_reference>
    struct DataBindingGenerator<glm::uvec2, is_reference>
    {
      DECLARE_DATA_BINDING_GENERATOR(glm::uvec2)

      private:
        static void generatePropertyBinding(
          const std::string& variableName,
          typename choose_class<static_cast<bool>(is_reference), const glm::uvec2&, glm::uvec2>::type value,
          std::string& output)
        {
          output.append("public UnsignedIntVector2 ");
          output.append(variableName);
          output.append(" { get; set; } = ");
          output.append("new UnsignedIntVector2(");
          output.append(std::to_string(value.x));
          output.append(", ");
          output.append(std::to_string(value.y));
          output.append(");");
        }
    };

    //------------------------------------------------------------------------------------------------
    template <bool is_reference>
    struct DataBindingGenerator<glm::vec3, is_reference>
    {
      DECLARE_DATA_BINDING_GENERATOR(glm::vec3)

      private:
        static void generatePropertyBinding(
          const std::string& variableName,
          typename choose_class<static_cast<bool>(is_reference), const glm::vec3&, glm::vec3>::type value,
          std::string& output)
        {
          output.append("public Vector3 ");
          output.append(variableName);
          output.append(" { get; set; } = ");
          output.append("new Vector3(");
          output.append(std::to_string(value.x));
          output.append("f, ");
          output.append(std::to_string(value.y));
          output.append("f, ");
          output.append(std::to_string(value.z));
          output.append("f);");
        }
    };

    //------------------------------------------------------------------------------------------------
    template <bool is_reference>
    struct DataBindingGenerator<glm::uvec3, is_reference>
    {
      DECLARE_DATA_BINDING_GENERATOR(glm::uvec3)

      private:
        static void generatePropertyBinding(
          const std::string& variableName,
          typename choose_class<static_cast<bool>(is_reference), const glm::uvec3&, glm::uvec3>::type value,
          std::string& output)
        {
          output.append("public UnsignedIntVector3 ");
          output.append(variableName);
          output.append(" { get; set; } = ");
          output.append("new UnsignedIntVector3(");
          output.append(std::to_string(value.x));
          output.append("f, ");
          output.append(std::to_string(value.y));
          output.append("f, ");
          output.append(std::to_string(value.z));
          output.append("f);");
        }
    };

    //------------------------------------------------------------------------------------------------
    template <bool is_reference>
    struct DataBindingGenerator<glm::vec4, is_reference>
    {
      DECLARE_DATA_BINDING_GENERATOR(glm::vec4)

      private:
        static void generatePropertyBinding(
          const std::string& variableName,
          typename choose_class<static_cast<bool>(is_reference), const glm::vec4&, glm::vec4>::type value,
          std::string& output)
        {
          output.append("public Vector4 ");
          output.append(variableName);
          output.append(" { get; set; } = ");
          output.append("new Vector4(");
          output.append(std::to_string(value.x));
          output.append("f, ");
          output.append(std::to_string(value.y));
          output.append("f, ");
          output.append(std::to_string(value.z));
          output.append("f, ");
          output.append(std::to_string(value.w));
          output.append("f);");
        }
    };

    //------------------------------------------------------------------------------------------------
    template <bool is_reference>
    struct DataBindingGenerator<glm::uvec4, is_reference>
    {
      DECLARE_DATA_BINDING_GENERATOR(glm::uvec4)

      private:
        static void generatePropertyBinding(
          const std::string& variableName,
          typename choose_class<static_cast<bool>(is_reference), const glm::uvec4&, glm::uvec4>::type value,
          std::string& output)
        {
          output.append("public UnsignedIntVector4 ");
          output.append(variableName);
          output.append(" { get; set; } = ");
          output.append("new UnsignedIntVector4(");
          output.append(std::to_string(value.x));
          output.append("f, ");
          output.append(std::to_string(value.y));
          output.append("f, ");
          output.append(std::to_string(value.z));
          output.append("f, ");
          output.append(std::to_string(value.w));
          output.append("f);");
        }
    };

    //------------------------------------------------------------------------------------------------
    template <bool is_reference>
    struct DataBindingGenerator<Maths::Space, is_reference>
    {
      DECLARE_DATA_BINDING_GENERATOR(Maths::Space)

      private:
        static void generatePropertyBinding(
          const std::string& variableName,
          typename choose_class<static_cast<bool>(is_reference), const Maths::Space&, Maths::Space>::type value,
          std::string& output)
        {
          output.append("public Space ");
          output.append(variableName);
          output.append(" { get; set; } = Space.");
          output.append(to_string(value));
          output.push_back(';');
        }
    };
  }
}