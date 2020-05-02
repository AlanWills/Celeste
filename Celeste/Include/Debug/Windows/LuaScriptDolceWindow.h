#pragma once

#if _DEBUG

#include "Dolce/DolceWindow.h"


namespace Celeste::Debug
{
  class LuaScriptDolceWindow : public Dolce::DolceWindow
  {
    public:
      LuaScriptDolceWindow();
      ~LuaScriptDolceWindow() override = default;

      void render() override;

    private:
      void run();

      std::string m_text;
      std::string m_output;
  };
}

#endif