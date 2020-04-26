#include "ScriptCommands/Resources/ResourcesScriptCommands.h"
#include "ScriptCommands/Resources/2D/Texture2DScriptCommands.h"
#include "ScriptCommands/Resources/3D/ModelScriptCommands.h"
#include "ScriptCommands/Resources/Audio/SoundScriptCommands.h"
#include "ScriptCommands/Resources/Data/DataScriptCommands.h"
#include "ScriptCommands/Resources/Data/PrefabScriptCommands.h"
#include "ScriptCommands/Resources/Fonts/FontScriptCommands.h"
#include "ScriptCommands/Resources/Shaders/ShaderScriptCommands.h"
#include "ScriptCommands/ScriptCommandUtils.h"
#include "sol/sol.hpp"

#include "Resources/ResourceUtils.h"
#include "Resources/ResourceManager.h"


namespace Celeste::Lua::Resources::ScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    std::string getResourcesDirectory()
    {
      return Celeste::Resources::getResourcesDirectory().as_string();
    }

    //------------------------------------------------------------------------------------------------
    observer_ptr<Celeste::Resources::Prefab> loadPrefab(const std::string& path)
    {
      return Celeste::Resources::getResourceManager().load<Celeste::Resources::Prefab>(path);
    }

    //------------------------------------------------------------------------------------------------
    bool isVertexShaderLoaded(const std::string& path)
    {
      return Celeste::Resources::getResourceManager().isLoaded<Celeste::Resources::VertexShader>(path);
    }

    //------------------------------------------------------------------------------------------------
    bool isFragmentShaderLoaded(const std::string& path)
    {
      return Celeste::Resources::getResourceManager().isLoaded<Celeste::Resources::FragmentShader>(path);
    }

    //------------------------------------------------------------------------------------------------
    bool isSoundLoaded(const std::string& path)
    {
      return Celeste::Resources::getResourceManager().isLoaded<Celeste::Resources::Sound>(path);
    }

    //------------------------------------------------------------------------------------------------
    bool isDataLoaded(const std::string& path)
    {
      return Celeste::Resources::getResourceManager().isLoaded<Celeste::Resources::Data>(path);
    }

    //------------------------------------------------------------------------------------------------
    bool isTexture2DLoaded(const std::string& path)
    {
      return Celeste::Resources::getResourceManager().isLoaded<Celeste::Resources::Texture2D>(path);
    }

    //------------------------------------------------------------------------------------------------
    bool isFontLoaded(const std::string& path)
    {
      return Celeste::Resources::getResourceManager().isLoaded<Celeste::Resources::Font>(path);
    }

    //------------------------------------------------------------------------------------------------
    bool isPrefabLoaded(const std::string& path)
    {
      return Celeste::Resources::getResourceManager().isLoaded<Celeste::Resources::Prefab>(path);
    }

    //------------------------------------------------------------------------------------------------
    bool isModelLoaded(const std::string& path)
    {
      return Celeste::Resources::getResourceManager().isLoaded<Celeste::Resources::Model>(path);
    }

    //------------------------------------------------------------------------------------------------
    void unloadVertexShader(const std::string& path)
    {
      Celeste::Resources::getResourceManager().unload<Celeste::Resources::VertexShader>(path);
    }

    //------------------------------------------------------------------------------------------------
    void unloadFragmentShader(const std::string& path)
    {
      Celeste::Resources::getResourceManager().unload<Celeste::Resources::FragmentShader>(path);
    }

    //------------------------------------------------------------------------------------------------
    void unloadSound(const std::string& path)
    {
      Celeste::Resources::getResourceManager().unload<Celeste::Resources::Sound>(path);
    }

    //------------------------------------------------------------------------------------------------
    void unloadData(const std::string& path)
    {
      Celeste::Resources::getResourceManager().unload<Celeste::Resources::Data>(path);
    }

    //------------------------------------------------------------------------------------------------
    void unloadTexture2D(const std::string& path)
    {
      Celeste::Resources::getResourceManager().unload<Celeste::Resources::Texture2D>(path);
    }

    //------------------------------------------------------------------------------------------------
    void unloadFont(const std::string& path)
    {
      Celeste::Resources::getResourceManager().unload<Celeste::Resources::Font>(path);
    }

    //------------------------------------------------------------------------------------------------
    void unloadPrefab(const std::string& path)
    {
      Celeste::Resources::getResourceManager().unload<Celeste::Resources::Prefab>(path);
    }

    //------------------------------------------------------------------------------------------------
    void unloadModel(const std::string& path)
    {
      Celeste::Resources::getResourceManager().unload<Celeste::Resources::Model>(path);
    }

    //------------------------------------------------------------------------------------------------
    void unloadAllVertexShaders()
    {
      Celeste::Resources::getResourceManager().unloadAll<Celeste::Resources::VertexShader>();
    }

    //------------------------------------------------------------------------------------------------
    void unloadAllFragmentShaders()
    {
      Celeste::Resources::getResourceManager().unloadAll<Celeste::Resources::FragmentShader>();
    }

    //------------------------------------------------------------------------------------------------
    void unloadAllSounds()
    {
      Celeste::Resources::getResourceManager().unloadAll<Celeste::Resources::Sound>();
    }

    //------------------------------------------------------------------------------------------------
    void unloadAllData()
    {
      Celeste::Resources::getResourceManager().unloadAll<Celeste::Resources::Data>();
    }

    //------------------------------------------------------------------------------------------------
    void unloadAllTexture2Ds()
    {
      Celeste::Resources::getResourceManager().unloadAll<Celeste::Resources::Texture2D>();
    }

    //------------------------------------------------------------------------------------------------
    void unloadAllFonts()
    {
      Celeste::Resources::getResourceManager().unloadAll<Celeste::Resources::Font>();
    }

    //------------------------------------------------------------------------------------------------
    void unloadAllPrefabs()
    {
      Celeste::Resources::getResourceManager().unloadAll<Celeste::Resources::Prefab>();
    }

    //------------------------------------------------------------------------------------------------
    void unloadAllModels()
    {
      Celeste::Resources::getResourceManager().unloadAll<Celeste::Resources::Model>();
    }

    //------------------------------------------------------------------------------------------------
    void unloadAllResources()
    {
      Celeste::Resources::getResourceManager().unloadAllResources();
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    sol::table resourcesTable = state.create_named_table("Resources");

    resourcesTable["getResourcesDirectory"] = &Internals::getResourcesDirectory;

    resourcesTable["loadPrefab"] = &Internals::loadPrefab;

    resourcesTable["isVertexShaderLoaded"] = &Internals::isVertexShaderLoaded;
    resourcesTable["isFragmentShaderLoaded"] = &Internals::isFragmentShaderLoaded;
    resourcesTable["isSoundLoaded"] = &Internals::isSoundLoaded;
    resourcesTable["isDataLoaded"] = &Internals::isDataLoaded;
    resourcesTable["isTexture2DLoaded"] = &Internals::isTexture2DLoaded;
    resourcesTable["isFontLoaded"] = &Internals::isFontLoaded;
    resourcesTable["isPrefabLoaded"] = &Internals::isPrefabLoaded;
    resourcesTable["isModelLoaded"] = &Internals::isModelLoaded;

    resourcesTable["unloadVertexShader"] = &Internals::unloadVertexShader;
    resourcesTable["unloadFragmentShader"] = &Internals::unloadFragmentShader;
    resourcesTable["unloadSound"] = &Internals::unloadSound;
    resourcesTable["unloadData"] = &Internals::unloadData;
    resourcesTable["unloadTexture2D"] = &Internals::unloadTexture2D;
    resourcesTable["unloadFont"] = &Internals::unloadFont;
    resourcesTable["unloadPrefab"] = &Internals::unloadPrefab;
    resourcesTable["unloadModel"] = &Internals::unloadModel;

    resourcesTable["unloadAllVertexShaders"] = &Internals::unloadAllVertexShaders;
    resourcesTable["unloadAllFragmentShaders"] = &Internals::unloadAllFragmentShaders;
    resourcesTable["unloadAllSounds"] = &Internals::unloadAllSounds;
    resourcesTable["unloadAllData"] = &Internals::unloadAllData;
    resourcesTable["unloadAllTexture2Ds"] = &Internals::unloadAllTexture2Ds;
    resourcesTable["unloadAllFonts"] = &Internals::unloadAllFonts;
    resourcesTable["unloadAllPrefabs"] = &Internals::unloadAllPrefabs;
    resourcesTable["unloadAllModels"] = &Internals::unloadAllModels;
    resourcesTable["unloadAllResources"] = &Internals::unloadAllResources;

    Resources::Texture2DScriptCommands::initialize(state);
    Resources::ModelScriptCommands::initialize(state);
    Resources::Audio::SoundScriptCommands::initialize(state);
    Resources::DataScriptCommands::initialize(state);
    Resources::PrefabScriptCommands::initialize(state);
    Resources::FontScriptCommands::initialize(state);
    Resources::ShaderScriptCommands::initialize(state);
  }
}