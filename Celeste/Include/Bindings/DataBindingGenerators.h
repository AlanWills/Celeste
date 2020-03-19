#pragma once

#include "Templates/ChooseClass.h"
#include "BindingUtils.h"
#include "FileSystem/Path.h"
#include "Reflection/Type.h"

#include <vector>


namespace Celeste
{
  namespace Resources
  {
    class Texture2D;
  }

  namespace Bindings
  {
#define DECLARE_DATA_BINDING_GENERATOR(Type) \
    static void generateBinding( \
      const std::string& dataXMLName, \
      typename choose_class<is_reference, const Type&, Type>::type value, \
      std::string& output) \
    { \
      output.append("\t\t[XmlAttribute(\""); \
      output.append(dataXMLName); \
      output.append("\"), DisplayName(\""); \
      output.append(xmlAttributeNameToDisplayName(dataXMLName)); \
      output.append("\")]\n\t\t"); \
      \
      generatePropertyBinding(xmlAttributeNameToVariableName(dataXMLName), value, output); \
    }

    template <typename T, bool is_reference>
    struct DataBindingGenerator
    {
      DECLARE_DATA_BINDING_GENERATOR(T);

      private:
        static void generatePropertyBinding(
          const std::string& variableName,
          typename choose_class<is_reference, const T&, T>::type /*value*/,
          std::string& output)
        {
          output.append("public ");
          output.append(Reflection::Type<T>().getName());
          output.append(variableName);
          output.append(" { get; set; }");
        }
    };

    //------------------------------------------------------------------------------------------------
    template <bool is_reference>
    struct DataBindingGenerator<bool, is_reference>
    {
      DECLARE_DATA_BINDING_GENERATOR(bool)

      private:
        static void generatePropertyBinding(
          const std::string& variableName,
          typename choose_class<static_cast<bool>(is_reference), const bool&, bool>::type value,
          std::string& output)
        {
          output.append("public bool ");
          output.append(variableName);
          output.append(" { get; set; } = ");
          output.append(value ? "true" : "false");
          output.push_back(';');
        }
    };

    //------------------------------------------------------------------------------------------------
    template <bool is_reference>
    struct DataBindingGenerator<int, is_reference>
    {
      DECLARE_DATA_BINDING_GENERATOR(int)

      private:
        static void generatePropertyBinding(
          const std::string& variableName,
          typename choose_class<static_cast<bool>(is_reference), const int&, int>::type value,
          std::string& output)
        {
          output.append("public int ");
          output.append(variableName);
          output.append(" { get; set; } = ");
          output.append(std::to_string(value));
          output.push_back(';');
        }
    };

    //------------------------------------------------------------------------------------------------
    template <bool is_reference>
    struct DataBindingGenerator<size_t, is_reference>
    {
      DECLARE_DATA_BINDING_GENERATOR(size_t)

    private:
      static void generatePropertyBinding(
        const std::string& variableName,
        typename choose_class<static_cast<bool>(is_reference), const size_t&, size_t>::type value,
        std::string& output)
      {
        output.append("public uint ");
        output.append(variableName);
        output.append(" { get; set; } = ");
        output.append(std::to_string(value));
        output.push_back(';');
      }
    };

    //------------------------------------------------------------------------------------------------
    template <bool is_reference>
    struct DataBindingGenerator<float, is_reference>
    {
      DECLARE_DATA_BINDING_GENERATOR(float)

      private:
        static void generatePropertyBinding(
          const std::string& variableName,
          typename choose_class<static_cast<bool>(is_reference), const float&, float>::type value,
          std::string& output)
        {
          output.append("public float ");
          output.append(variableName);
          output.append(" { get; set; } = ");
          output.append(std::to_string(value));
          output.append("f;");
        }
    };

    //------------------------------------------------------------------------------------------------
    template <bool is_reference>
    struct DataBindingGenerator<std::string, is_reference>
    {
      DECLARE_DATA_BINDING_GENERATOR(std::string)

      private:
        static void generatePropertyBinding(
          const std::string& variableName,
          typename choose_class<static_cast<bool>(is_reference), const std::string&, std::string>::type value,
          std::string& output)
        {
          output.append("public string ");
          output.append(variableName);
          output.append(" { get; set; } = \"");
          output.append(value);
          output.append("\";");
        }
    };

    //------------------------------------------------------------------------------------------------
    template <bool is_reference>
    struct DataBindingGenerator<Path, is_reference>
    {
      DECLARE_DATA_BINDING_GENERATOR(Path)

      private:
        static void generatePropertyBinding(
          const std::string& variableName,
          typename choose_class<static_cast<bool>(is_reference), const Path&, Path>::type value,
          std::string& output)
        {
          output.append("public Path ");
          output.append(variableName);
          output.append(" { get; set; } = new Path(@\"");
          output.append(value.as_string());
          output.append("\");");
        }
    };

    //------------------------------------------------------------------------------------------------
    template <bool is_reference>
    struct DataBindingGenerator<Resources::Texture2D, is_reference>
    {
      DECLARE_DATA_BINDING_GENERATOR(Resources::Texture2D)

      private:
        static void generatePropertyBinding(
          const std::string& variableName,
          typename choose_class<static_cast<bool>(is_reference), const Resources::Texture2D&, Resources::Texture2D>::type value,
          std::string& output)
        {
          output.append("public Texture2D ");
          output.append(variableName);
          output.append(" { get; set; }");
        }
    };

    //------------------------------------------------------------------------------------------------
    template <bool is_reference>
    struct DataBindingGenerator<std::vector<Resources::Texture2D*>, is_reference>
    {
      DECLARE_DATA_BINDING_GENERATOR(std::vector<Resources::Texture2D*>)

      private:
        static void generatePropertyBinding(
          const std::string& variableName,
          typename choose_class<static_cast<bool>(is_reference), const std::vector<Resources::Texture2D*>&, std::vector<Resources::Texture2D*>>::type value,
          std::string& output)
        {
          output.append("public List<Texture2D> ");
          output.append(variableName);
          output.append(" { get; set; } = new List<Texture2D>();");
        }
    };
  }
}