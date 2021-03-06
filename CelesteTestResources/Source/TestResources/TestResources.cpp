#include "Resources/ResourceManager.h"
#include "TestResources/TestResources.h"
#include "TestResources/Animation/AnimatorLoadingResources.h"
#include "TestResources/Audio/AudioSourceLoadingResources.h"
#include "TestResources/GraphicalFX/OpacityLerperLoadingResources.h"

#include "TestResources/Input/KeyboardActivatorLoadingResources.h"
#include "TestResources/Input/KeyboardRigidBody2DControllerLoadingResources.h"
#include "TestResources/Input/KeyboardTransformerLoadingResources.h"
#include "TestResources/Input/KeyboardVisibilityLoadingResources.h"

#include "TestResources/Objects/GameObjectLoadingResources.h"
#include "TestResources/Objects/MockScriptableObjectLoadingResources.h"

#include "TestResources/Physics/EllipseColliderLoadingResources.h"
#include "TestResources/Physics/RectangleColliderLoadingResources.h"
#include "TestResources/Physics/RigidBody2DLoadingResources.h"

#include "TestResources/Rendering/CanvasLoadingResources.h"
#include "TestResources/Rendering/SpriteRendererLoadingResources.h"
#include "TestResources/Rendering/TextRendererLoadingResources.h"

#include "TestResources/Resources/Data/PrefabLoadingResources.h"
#include "TestResources/Resources/Models/ModelLoadingResources.h"

#include "TestResources/Scene/SceneLoadingResources.h"

#include "TestResources/Settings/GameSettingsLoadingResources.h"

#include "TestResources/UI/ButtonLoadingResources.h"
#include "TestResources/UI/SliderLoadingResources.h"
#include "TestResources/UI/StackPanelLoadingResources.h"


namespace CelesteTestResources
{
  Path TestResources::m_resourcesDirectory(Path(Directory::getExecutingAppDirectory(), UPDIR_STRING, UPDIR_STRING, UPDIR_STRING, 
    "Celeste", "Celeste", "Tests", "Resources"));

  REGISTER_TEST_RESOURCE_CLASS(TestResources)

  //------------------------------------------------------------------------------------------------
  void TestResources::initialize()
  {
    sol::table testResources = createLuaResourcesTable();

    ADD_DIRECTORY_TO_LUA(testResources, VertexShaders);
    ADD_DIRECTORY_TO_LUA(testResources, FragmentShaders);
    ADD_DIRECTORY_TO_LUA(testResources, Textures);
    ADD_DIRECTORY_TO_LUA(testResources, Fonts);
    ADD_DIRECTORY_TO_LUA(testResources, Sounds);
    ADD_DIRECTORY_TO_LUA(testResources, Data);
    ADD_DIRECTORY_TO_LUA(testResources, MockResources);
    ADD_DIRECTORY_TO_LUA(testResources, MoreMockResources);

    // Vertex Shaders
    ADD_RESOURCE_TO_LUA(testResources, SpriteVertexShader);
    ADD_RESOURCE_TO_LUA(testResources, TextVertexShader);

    // Fragment Shaders
    ADD_RESOURCE_TO_LUA(testResources, SpriteFragmentShader);
    ADD_RESOURCE_TO_LUA(testResources, TextFragmentShader);

    // Textures
    ADD_RESOURCE_TO_LUA(testResources, BlockPng);
    ADD_RESOURCE_TO_LUA(testResources, ContainerJpg);

    // Fonts
    ADD_RESOURCE_TO_LUA(testResources, ArialTtf);

    // Sounds
    ADD_RESOURCE_TO_LUA(testResources, ButtonHoverWav);

    // Data
    ADD_RESOURCE_TO_LUA(testResources, DataXml);
    ADD_RESOURCE_TO_LUA(testResources, ElementDataAsVectorFloat);
    ADD_RESOURCE_TO_LUA(testResources, ElementDataAsVectorString);

    AnimatorLoadingResources::addAllResourcesToLua();
    AudioSourceLoadingResources::addAllResourcesToLua();
    OpacityLerperLoadingResources::addAllResourcesToLua();

    // Input
    KeyboardActivatorLoadingResources::addAllResourcesToLua();
    KeyboardRigidBody2DControllerLoadingResources::addAllResourcesToLua();
    KeyboardTransformerLoadingResources::addAllResourcesToLua();
    KeyboardVisibilityLoadingResources::addAllResourcesToLua();

    GameObjectLoadingResources::addAllResourcesToLua();
    MockScriptableObjectLoadingResources::addAllResourcesToLua();

    // Physics
    EllipseColliderLoadingResources::addAllResourcesToLua();
    RectangleColliderLoadingResources::addAllResourcesToLua();
    RigidBody2DLoadingResources::addAllResourcesToLua();

    // Rendering
    CanvasLoadingResources::addAllResourcesToLua();
    SpriteRendererLoadingResources::addAllResourcesToLua();
    TextRendererLoadingResources::addAllResourcesToLua();

    PrefabLoadingResources::addAllResourcesToLua();
    ModelLoadingResources::addAllResourcesToLua();
    SceneLoadingResources::addAllResourcesToLua();

    // Settings
    GameSettingsLoadingResources::addAllResourcesToLua();

    ButtonLoadingResources::addAllResourcesToLua();
    SliderLoadingResources::addAllResourcesToLua();
    StackPanelLoadingResources::addAllResourcesToLua();
  }

  //------------------------------------------------------------------------------------------------
  void TestResources::unloadAllResources()
  {
    // Vertex Shaders
    UNLOAD_VERTEX_SHADER(SpriteVertexShader);
    UNLOAD_VERTEX_SHADER(TextVertexShader);

    // Fragment Shaders
    UNLOAD_FRAGMENT_SHADER(SpriteFragmentShader);
    UNLOAD_FRAGMENT_SHADER(TextFragmentShader);

    // Textures
    UNLOAD_TEXTURE2D(BlockPng);
    UNLOAD_TEXTURE2D(ContainerJpg);

    // Fonts
    UNLOAD_FONT(ArialTtf);

    // Sounds
    UNLOAD_SOUND(ButtonHoverWav);

    // Data
    UNLOAD_DATA(DataXml);
    UNLOAD_DATA(ElementDataAsVectorFloat);
    UNLOAD_DATA(ElementDataAsVectorString);

    AnimatorLoadingResources::unloadAllResources();
    AudioSourceLoadingResources::unloadAllResources();
    OpacityLerperLoadingResources::unloadAllResources();

    // Input
    KeyboardActivatorLoadingResources::unloadAllResources();
    KeyboardRigidBody2DControllerLoadingResources::unloadAllResources();
    KeyboardTransformerLoadingResources::unloadAllResources();
    KeyboardVisibilityLoadingResources::unloadAllResources();

    GameObjectLoadingResources::unloadAllResources();
    MockScriptableObjectLoadingResources::unloadAllResources();

    // Physics
    EllipseColliderLoadingResources::unloadAllResources();
    RectangleColliderLoadingResources::unloadAllResources();
    RigidBody2DLoadingResources::unloadAllResources();

    // Rendering
    CanvasLoadingResources::unloadAllResources();
    SpriteRendererLoadingResources::unloadAllResources();
    TextRendererLoadingResources::unloadAllResources();

    PrefabLoadingResources::unloadAllResources();
    ModelLoadingResources::unloadAllResources();
    SceneLoadingResources::unloadAllResources();

    // Settings
    GameSettingsLoadingResources::unloadAllResources();

    ButtonLoadingResources::unloadAllResources();
    SliderLoadingResources::unloadAllResources();
    StackPanelLoadingResources::unloadAllResources();
  }

  //------------------------------------------------------------------------------------------------
  Path TestResources::getResourcesDirectory()
  {
    return m_resourcesDirectory;
  }

  //------------------------------------------------------------------------------------------------
  void TestResources::setResourcesDirectory(const Path& resourcesDirectory)
  {
    m_resourcesDirectory = resourcesDirectory;
  }
}