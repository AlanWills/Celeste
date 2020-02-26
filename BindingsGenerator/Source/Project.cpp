#include "stdafx.h"

#include "Project.h"
#include "Registries/ScriptableObjectRegistry.h"
#include "Registries/ComponentRegistry.h"

using namespace tinyxml2;
using namespace Celeste;
using namespace Celeste::XML;


namespace BindingsGenerator
{
  //------------------------------------------------------------------------------------------------
  Project::Project(
    const Celeste::Path& bindingsProjectDirectoryPath,
    const std::string& bindingsProjectName,
    const std::string& assemblyName) :
      m_projectDirectory(bindingsProjectDirectoryPath),
      m_projectName(bindingsProjectName),
      m_assemblyName(assemblyName)
  {
  }

  //------------------------------------------------------------------------------------------------
  void Project::generateBindings()
  {
    Path projectPath(m_projectDirectory.getDirectoryPath(), m_projectName + ".csproj");
    XMLDocument document;
    tinyxml2::XMLError error = document.LoadFile(projectPath.c_str());
    ASSERT(error == XMLError::XML_SUCCESS);

    // Find the appropriate item group in the project that we have previously created bindings for (if it exists)
    // and remove it so that we can recreate fresh dependencies for our project
    tinyxml2::XMLElement* itemGroup = nullptr;
    for (tinyxml2::XMLElement* itemGroupElement : children(document.FirstChildElement("Project"), "ItemGroup"))
    {
      for (const tinyxml2::XMLElement* folderElement : children(itemGroupElement, "Folder"))
      {
        if (strcmp(folderElement->Attribute("Include"), "Bindings\\") == 0)
        {
          // We have found the correct item group element
          itemGroup = itemGroupElement;
          break;
        }

        if (itemGroup != nullptr)
        {
          // Recursively break
          break;
        }
      }
    }

    if (itemGroup == nullptr)
    {
      itemGroup = document.NewElement("ItemGroup");
      document.FirstChildElement("Project")->InsertEndChild(itemGroup);
    }
    else
    {
      // Erase all children underneath the existent item group
      itemGroup->DeleteChildren();
    }

    // Re-add the folder element
    XMLElement* folderElement = document.NewElement("Folder");
    folderElement->SetAttribute("Include", "Bindings\\");
    itemGroup->InsertFirstChild(folderElement);

    // Bindings won't be created if a matching file already exists, so we clear the output directory first
    Directory bindingsOutputDirectory(Path(m_projectDirectory.getDirectoryPath(), "Bindings"));
    bindingsOutputDirectory.remove();
    bindingsOutputDirectory.create();

    ScriptableObjectRegistry::generateBindingsForAssembly(m_assemblyName, bindingsOutputDirectory, [&itemGroup](const std::string& name, const Path& filePath) -> void
    {
      XMLElement* element = itemGroup->GetDocument()->NewElement("Compile");
      element->SetAttribute("Include", ("Bindings\\" + name + ".cs").c_str());
      itemGroup->InsertEndChild(element);

      std::cout << "Generated bindings for " + name << std::endl;
    });

    ComponentRegistry::generateBindingsForAssembly(m_assemblyName, bindingsOutputDirectory, [&itemGroup](const std::string& name, const Path& filePath) -> void
    {
      XMLElement* element = itemGroup->GetDocument()->NewElement("Compile");
      element->SetAttribute("Include", ("Bindings\\" + name + ".cs").c_str());
      itemGroup->InsertEndChild(element);

      std::cout << "Generated bindings for " + name << std::endl;
    });

    document.SaveFile(projectPath.c_str());
  }
}