#pragma once

#include "FileSystem/Path.h"
#include "FileSystem/Directory.h"
#include "Lua/LuaState.h"

using namespace Celeste;


namespace CelesteTestResources
{
  #define DECLARE_TEST_RESOURCE_CLASS(Name) \
    public: \
      Name() = delete; \
      ~Name() = delete; \
      Name(const Name&) = delete; \
      Name& operator=(const Name&) = delete; \
      \
      static void addAllResourcesToLua(); \
      static void unloadAllResources(); \
      \
    private: \
      static sol::table createLuaResourcesTable();

  #define REGISTER_TEST_RESOURCE_CLASS(Name) \
    sol::table Name::createLuaResourcesTable() \
    { \
      sol::table resources = Celeste::Lua::LuaState::instance().create_named_table(#Name##); \
      resources["unloadAllResources"] = &Name::unloadAllResources; \
      return resources; \
    }

  #define TEST_RESOURCE(Name, ParentDirectory, ResourceRelativePath) \
    public: \
      static std::string get##Name##RelativePath() { return Path(get##ParentDirectory##DirectoryRelativePath(), ResourceRelativePath).as_string(); } \
      static Path get##Name##FullPath() { return Path(get##ParentDirectory##Directory(), ResourceRelativePath); }

  #define TEST_VERTEX_SHADER(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, VertexShaders, ResourceRelativePath)

  #define TEST_FRAGMENT_SHADER(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, FragmentShaders, ResourceRelativePath)

  #define TEST_TEXTURE(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, Textures, ResourceRelativePath)

  #define TEST_FONT(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, Fonts, ResourceRelativePath)

  #define TEST_SOUND(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, Sounds, ResourceRelativePath)

  #define TEST_DATA(Name, ResourceRelativePath) \
    TEST_RESOURCE(Name, Data, ResourceRelativePath)

  #define DECLARE_TEST_RESOURCE_DIRECTORY(Name, Relative_Path) \
    public: \
      static std::string get##Name##DirectoryRelativePath() { return Relative_Path; } \
      static Path get##Name##Directory() { return Path(TestResources::getResourcesDirectory(), Relative_Path); }

  #define ADD_RESOURCE_TO_LUA(Table, Name) \
    Table[#Name##] = get##Name##FullPath().as_string();

  #define ADD_DIRECTORY_TO_LUA(Table, Name) \
    Table[#Name##"Directory"] = get##Name##Directory().as_string();

  #define UNLOAD_RESOURCE(Type, Name) \
    Celeste::Resources::getResourceManager().unload<Type>(get##Name##FullPath());

  #define UNLOAD_VERTEX_SHADER(Name) \
    UNLOAD_RESOURCE(Celeste::Resources::VertexShader, Name)

  #define UNLOAD_FRAGMENT_SHADER(Name) \
    UNLOAD_RESOURCE(Celeste::Resources::FragmentShader, Name)

  #define UNLOAD_TEXTURE2D(Name) \
    UNLOAD_RESOURCE(Celeste::Resources::Texture2D, Name)

  #define UNLOAD_FONT(Name) \
    UNLOAD_RESOURCE(Celeste::Resources::Font, Name)

  #define UNLOAD_SOUND(Name) \
    UNLOAD_RESOURCE(Celeste::Resources::Sound, Name)

  #define UNLOAD_DATA(Name) \
    UNLOAD_RESOURCE(Celeste::Resources::Data, Name)

  class TestResources
  {
    DECLARE_TEST_RESOURCE_CLASS(TestResources)

    public:
      static void initialize();

      static Path getResourcesDirectory();
      static void setResourcesDirectory(const Path& resourcesDirectory);

      DECLARE_TEST_RESOURCE_DIRECTORY(VertexShaders, "Vertex Shaders")
      DECLARE_TEST_RESOURCE_DIRECTORY(FragmentShaders, "Fragment Shaders")
      DECLARE_TEST_RESOURCE_DIRECTORY(Textures, "Textures")
      DECLARE_TEST_RESOURCE_DIRECTORY(Fonts, "Fonts")
      DECLARE_TEST_RESOURCE_DIRECTORY(Sounds, "Audio")
      DECLARE_TEST_RESOURCE_DIRECTORY(Data, "Data")
      DECLARE_TEST_RESOURCE_DIRECTORY(MockResources, "Mock Resources")
      DECLARE_TEST_RESOURCE_DIRECTORY(MoreMockResources, "More Mock Resources")

      // Vertex Shaders
      TEST_VERTEX_SHADER(SpriteVertexShader, "sprite.vert");
      TEST_VERTEX_SHADER(TextVertexShader, "text.vert");

      // Fragment Shaders
      TEST_FRAGMENT_SHADER(SpriteFragmentShader, "sprite.frag");
      TEST_FRAGMENT_SHADER(TextFragmentShader, "text.frag");

      // Textures
      TEST_TEXTURE(BlockPng, "block.png");
      TEST_TEXTURE(ContainerJpg, "container.jpg");

      // Fonts
      TEST_FONT(ArialTtf, "arial.ttf");

      // Sounds
      TEST_SOUND(ButtonHoverWav, "SFX\\ButtonHover.wav");
    
      // Data
      TEST_DATA(DataXml, "Data.xml");
      TEST_DATA(ElementDataAsVectorFloat, "ElementDataAsVectorFloat.xml");
      TEST_DATA(ElementDataAsVectorString, "ElementDataAsVectorString.xml");

    private:
      static Path m_resourcesDirectory;
  };
}