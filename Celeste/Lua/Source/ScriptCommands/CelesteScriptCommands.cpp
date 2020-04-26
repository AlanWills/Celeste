#include "ScriptCommands/CelesteScriptCommands.h"
#include "ScriptCommands/CoreScriptCommands.h"
#include "ScriptCommands/Animation/AnimationScriptCommands.h"
#include "ScriptCommands/Audio/AudioScriptCommands.h"
#include "ScriptCommands/Events/EventScriptCommands.h"
#include "ScriptCommands/Resources/ResourcesScriptCommands.h"
#include "ScriptCommands/Scene/SceneScriptCommands.h"
#include "ScriptCommands/Maths/MathsScriptCommands.h"
#include "ScriptCommands/Media/VideoScriptCommands.h"
#include "ScriptCommands/Physics/PhysicsScriptCommands.h"
#include "ScriptCommands/Rendering/RenderingScriptCommands.h"
#include "ScriptCommands/Input/InputScriptCommands.h"
#include "ScriptCommands/Objects/ObjectScriptCommands.h"
#include "ScriptCommands/DataConverters/DataConverterScriptCommands.h"
#include "ScriptCommands/Time/TimeScriptCommands.h"
#include "ScriptCommands/Viewport/ViewportScriptCommands.h"
#include "ScriptCommands/UI/UIScriptCommands.h"
#include "ScriptCommands/XML/XMLScriptCommands.h"
#include "ScriptCommands/Lua/Components/LuaComponentManifestRegistryScriptCommands.h"
#include "Lua/LuaState.h"

#include "Resources/ResourceUtils.h"

#if _DEBUG
#include "Debug/DolceUtils.h"
#include "ScriptCommands/DolceScriptCommands.h"
#endif


namespace Celeste::Lua::CelesteScriptCommands
{
  //------------------------------------------------------------------------------------------------
  void initialize(sol::state& state)
  {
    // Update lua path to ensure scripts in resources directory will be found will be found
    Lua::LuaState::appendToLuaPackagePath(Path(Celeste::Resources::getResourcesDirectory(), "Scripts", "?.lua;"));

    // Now initialize all lua scripts and API
    Lua::Core::ScriptCommands::initialize(state);
    Lua::Maths::ScriptCommands::initialize(state);
    Lua::Viewport::ScriptCommands::initialize(state);
    Lua::XML::XMLScriptCommands::initialize(state);
    Lua::Objects::ScriptCommands::initialize(state);
    Lua::Resources::ScriptCommands::initialize(state);
    Lua::Scene::ScriptCommands::initialize(state);
    Lua::DataConverters::ScriptCommands::initialize(state);
    Lua::Animation::ScriptCommands::initialize(state);
    Lua::Audio::ScriptCommands::initialize(state);
    Lua::Media::VideoScriptCommands::initialize(state);
    Lua::Physics::ScriptCommands::initialize(state);
    Lua::Rendering::ScriptCommands::initialize(state);
    Lua::Input::ScriptCommands::initialize(state);
    Lua::UI::ScriptCommands::initialize(state);
    Lua::Events::ScriptCommands::initialize(state);
    Lua::LuaComponentManifestRegistryScriptCommands::initialize(state);
    Lua::Time::ScriptCommands::initialize(state);

#if _DEBUG
    Dolce::Lua::ScriptCommands::initialize(state, Debug::getDolce());
#endif
  }
}