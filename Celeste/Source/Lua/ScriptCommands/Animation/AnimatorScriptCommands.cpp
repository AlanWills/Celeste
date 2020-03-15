#include "Lua/ScriptCommands/Animation/AnimatorScriptCommands.h"
#include "Lua/ScriptCommands/ScriptCommandUtils.h"
#include "Lua/LuaState.h"

#include "Animation/Animator.h"


namespace Celeste::Lua::Animation::AnimatorScriptCommands
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    void setLooping(Celeste::Animation::Animator& animator, bool isLooping)
    {
      animator.setLooping(isLooping ? Celeste::Animation::LoopMode::kLooping :
        Celeste::Animation::LoopMode::kOneTime);
    }
  }

  //------------------------------------------------------------------------------------------------
  void initialize()
  {
    using Animator = Celeste::Animation::Animator;

    registerUserType<Animator>(
      Animator::type_name(),
      "getSpriteSheetDimensions", &Animator::getSpriteSheetDimensions,
      "setSpriteSheetDimensions", &Animator::setSpriteSheetDimensions,
      "getSecondsPerFrame", &Animator::getSecondsPerFrame,
      "setSecondsPerFrame", &Animator::setSecondsPerFrame,
      "isLooping", &Animator::isLooping,
      "setLooping", &Internals::setLooping,
      "play", &Animator::play,
      "pause", &Animator::pause,
      "stop", &Animator::stop,
      "restart", &Animator::restart);
  }
}