#include "Lua/ScriptCommands/CelesteScriptCommands.h"
#include "Lua/ScriptCommands/CoreScriptCommands.h"
#include "Lua/ScriptCommands/Animation/AnimationScriptCommands.h"
#include "Lua/ScriptCommands/Audio/AudioScriptCommands.h"
#include "Lua/ScriptCommands/Debug/DebugScriptCommands.h"
#include "Lua/ScriptCommands/Events/EventScriptCommands.h"
#include "Lua/ScriptCommands/Resources/ResourcesScriptCommands.h"
#include "Lua/ScriptCommands/Scene/SceneScriptCommands.h"
#include "Lua/ScriptCommands/Maths/MathsScriptCommands.h"
#include "Lua/ScriptCommands/Media/VideoScriptCommands.h"
#include "Lua/ScriptCommands/Physics/PhysicsScriptCommands.h"
#include "Lua/ScriptCommands/Rendering/RenderingScriptCommands.h"
#include "Lua/ScriptCommands/Input/InputScriptCommands.h"
#include "Lua/ScriptCommands/Objects/ObjectScriptCommands.h"
#include "Lua/ScriptCommands/DataConverters/DataConverterScriptCommands.h"
#include "Lua/ScriptCommands/Viewport/ViewportScriptCommands.h"
#include "Lua/ScriptCommands/UI/UIScriptCommands.h"
#include "Lua/ScriptCommands/XML/XMLScriptCommands.h"
#include "Lua/ScriptCommands/Lua/Components/LuaComponentManifestRegistryScriptCommands.h"
#include "Lua/LuaState.h"

#include "Resources/ResourceUtils.h"


namespace Celeste::Lua::CelesteScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    // Update lua path to ensure all engine scripts will be found
    Lua::LuaState::appendToLuaPackagePath(Path(Celeste::Resources::getResourcesDirectory(), "Scripts", "?.lua;"));

    // Now initialize all lua scripts and API
    Lua::Debug::ScriptCommands::initialize();
    Lua::Core::ScriptCommands::initialize();
    Lua::Maths::ScriptCommands::initialize();
    Lua::Viewport::ScriptCommands::initialize();
    Lua::XML::XMLScriptCommands::initialize();
    Lua::Objects::ScriptCommands::initialize();
    Lua::Resources::ScriptCommands::initialize();
    Lua::Scene::ScriptCommands::initialize();
    Lua::DataConverters::ScriptCommands::initialize();
    Lua::Animation::ScriptCommands::initialize();
    Lua::Audio::ScriptCommands::initialize();
    Lua::Media::VideoScriptCommands::initialize();
    Lua::Physics::ScriptCommands::initialize();
    Lua::Rendering::ScriptCommands::initialize();
    Lua::Input::ScriptCommands::initialize();
    Lua::UI::ScriptCommands::initialize();
    Lua::Events::ScriptCommands::initialize();
    Lua::LuaComponentManifestRegistryScriptCommands::initialize();
  }
}