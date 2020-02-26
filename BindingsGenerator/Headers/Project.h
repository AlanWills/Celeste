#pragma once

#include "BindingsGeneratorDllExport.h"
#include "FileSystem/Directory.h"


namespace BindingsGenerator
{

class BindingsGeneratorDllExport Project
{
  public:
    Project(
      const Celeste::Path& bindingsProjectDirectoryPath, 
      const std::string& bindingsProjectName, 
      const std::string& assemblyName);

    void generateBindings();

  private:
    Celeste::Directory m_projectDirectory;
    std::string m_projectName;
    std::string m_assemblyName;
};

}