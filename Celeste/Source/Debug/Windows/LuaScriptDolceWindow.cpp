#if _DEBUG

#include "Debug/Windows/LuaScriptDolceWindow.h"
#include "Lua/LuaState.h"

#include "imgui.h"
#include "imgui_stdlib.h"


namespace Celeste::Debug
{
  //------------------------------------------------------------------------------------------------
  LuaScriptDolceWindow::LuaScriptDolceWindow() :
    Dolce::DolceWindow("Lua")
  {
  }

  //------------------------------------------------------------------------------------------------
  void LuaScriptDolceWindow::render()
  {
    ImGui::PushItemWidth(ImGui::GetWindowContentRegionWidth());
    ImGui::InputTextMultiline("", &m_text);
    ImGui::PopItemWidth();

    if (ImGui::Button("Run"))
    {
      run();
    }

    ImGui::Separator();

    ImGui::Text("Output");

    ImGui::Spacing();

    ImGui::Text(m_output.c_str());
  }

  //------------------------------------------------------------------------------------------------
  void LuaScriptDolceWindow::run()
  {
    auto result = Lua::LuaState::script(m_text);
    if (result.valid())
    {
      if (result.return_count() == 1)
      {
        m_output.assign(result.get<std::string>());
      }
    }
    else
    {
      sol::error e = result;
      m_output.assign(e.what());
    }
  }
}

#endif