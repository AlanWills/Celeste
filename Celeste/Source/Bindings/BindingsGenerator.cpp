#if _DEBUG

#include "Bindings/BindingsGenerator.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "DataConverters/Objects/ComponentDataConverter.h"
#include "Utils/StringUtils.h"

#include <unordered_set>


namespace Celeste::Bindings
{
  //------------------------------------------------------------------------------------------------
  std::string BindingsGenerator::createDefaultNamespaces()
  {
    std::string namespaces;
    namespaces.reserve(256);
    namespaces.append("using System;\n");
    namespaces.append("using System.Collections.Generic;\n");
    namespaces.append("using System.Linq;\n");
    namespaces.append("using System.Text;\n");
    namespaces.append("using System.Windows;\n");
    namespaces.append("using System.Windows.Controls;\n");
    namespaces.append("using System.Threading.Tasks;\n");
    namespaces.append("using System.Xml.Serialization;\n");
    namespaces.append("using BindingsKernel;\n");
    namespaces.push_back('\n');

    return namespaces;
  }

  //------------------------------------------------------------------------------------------------
  std::string BindingsGenerator::createClassDeclaration(const Reflection::ITypeInfo& typeInfo)
  {
    std::string classDeclaration;
    classDeclaration.reserve(256);
    classDeclaration.append("namespace ");
    classDeclaration.append(cppNamespaceToCsNamespace(typeInfo.getNamespace()));
    classDeclaration.push_back('\n');
    classDeclaration.append("{\n");
    classDeclaration.append("\tpublic class ");
    classDeclaration.append(typeInfo.getName());

    return classDeclaration;
  }

  //------------------------------------------------------------------------------------------------
  std::string BindingsGenerator::createFilePostamble()
  {
    std::string postAmble;
    postAmble.append("\t}\n");
    postAmble.append("}\n");

    return postAmble;
  }

  //------------------------------------------------------------------------------------------------
  void BindingsGenerator::generateScriptableObjectBindings(
    const Directory& parentDirectory,
    const Reflection::ITypeInfo& typeInfo,
    const ScriptableObject& scriptableObject)
  {
    File file(Path(parentDirectory.getDirectoryPath(), typeInfo.getName() + ".cs"));
    if (file.exists())
    {
      // Bindings already generated for this class and also any sub classes, so we can just quit here
      return;
    }

    std::unordered_set<std::string> customNamespaces;
    std::string classContent;
    classContent.reserve(4096);
    classContent.append(" : ScriptableObject\n\t{");

    size_t index = 0;
    for (const auto& field : scriptableObject.m_fields)
    {
      classContent.push_back('\n');
      classContent.append("\t\t[Serialize, DisplayPriority(");
      classContent.append(std::to_string(++index));
      classContent.append(")]\n");
      field->generateBinding(classContent);
      classContent.push_back('\n');
    }

    for (const auto& childSO : scriptableObject.m_scriptableObjects)
    {
      classContent.push_back('\n');
      classContent.append("\t\t[Serialize, DisplayPriority(");
      classContent.append(std::to_string(++index));
      classContent.append(")]\n");
      childSO->generateBinding(classContent);
      classContent.push_back('\n');

      std::unique_ptr<Reflection::ITypeInfo> scriptableObjectTypeInfo(nullptr);
      childSO->type_info_i(scriptableObjectTypeInfo);

      if (customNamespaces.find(scriptableObjectTypeInfo->getNamespace()) == customNamespaces.end() &&
        scriptableObjectTypeInfo->getNamespace() != typeInfo.getNamespace())
      {
        // New unique namespace, so we add it to our set to add later
        customNamespaces.insert(scriptableObjectTypeInfo->getNamespace());
      }
    }

    for (const auto& customNamespace : customNamespaces)
    {
      file.append("using ");
      file.append(cppNamespaceToCsNamespace(customNamespace));
      file.append(";\n");
    }

    file.append(createDefaultNamespaces());
    file.append(createClassDeclaration(typeInfo));
    file.append(classContent);
    file.append(createFilePostamble());
  }

  //------------------------------------------------------------------------------------------------
  void BindingsGenerator::generateComponentBindings(
    const Directory& parentDirectory,
    const Reflection::ITypeInfo& componentTypeInfo)
  {
    File file(Path(parentDirectory.getDirectoryPath(), componentTypeInfo.getName() + ".cs"));
    if (file.exists())
    {
      // Bindings already generated for this class and also any sub classes, so we can just quit here
      return;
    }

    std::unique_ptr<ComponentDataConverter> converter(nullptr);
    ComponentDataConverterRegistry::getConverter(componentTypeInfo.getName(), converter);
    ASSERT(converter.get());

    std::string classContent;
    classContent.reserve(4096);
    classContent.append(" : Component\n\t{");

    size_t index = 0;
    for (XML::Attribute* attribute : converter->m_attributes)
    {
      classContent.push_back('\n');
      classContent.append("\t\t[Serialize, DisplayPriority(");
      classContent.append(std::to_string(++index));
      classContent.append(")]\n");
      attribute->generateBinding(classContent);
      classContent.push_back('\n');
    }

    for (XML::Element* element : converter->m_elements)
    {
      classContent.push_back('\n');
      classContent.append("\t\t[Serialize, DisplayPriority(");
      classContent.append(std::to_string(++index));
      classContent.append(")]\n");
      element->generateBinding(classContent);
      classContent.push_back('\n');
    }

    file.append(createDefaultNamespaces());
    file.append(createClassDeclaration(componentTypeInfo));
    file.append(classContent);
    file.append(createFilePostamble());
  }
}

#endif