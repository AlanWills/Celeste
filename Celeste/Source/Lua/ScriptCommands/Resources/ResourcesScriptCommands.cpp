#include "Lua/ScriptCommands/Resources/ResourcesScriptCommands.h"
#include "Lua/ScriptCommands/Resources/2D/Texture2DScriptCommands.h"
#include "Lua/ScriptCommands/Resources/3D/ModelScriptCommands.h"
#include "Lua/ScriptCommands/Resources/Audio/SoundScriptCommands.h"
#include "Lua/ScriptCommands/Resources/Data/DataScriptCommands.h"
#include "Lua/ScriptCommands/Resources/Data/PrefabScriptCommands.h"
#include "Lua/ScriptCommands/Resources/Fonts/FontScriptCommands.h"
#include "Lua/ScriptCommands/Resources/Shaders/ShaderScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

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
  void initialize()
  {
    sol::state& state = LuaState::instance();
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

    Resources::Texture2DScriptCommands::initialize();
    Resources::ModelScriptCommands::initialize();
    Resources::Audio::SoundScriptCommands::initialize();
    Resources::DataScriptCommands::initialize();
    Resources::PrefabScriptCommands::initialize();
    Resources::FontScriptCommands::initialize();
    Resources::ShaderScriptCommands::initialize();
  }
}