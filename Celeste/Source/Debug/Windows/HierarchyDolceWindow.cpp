#include "Debug/Windows/HierarchyDolceWindow.h"
#include "Scene/SceneManager.h"
#include "Objects/GameObject.h"

#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

#include <cstdio>


namespace Celeste::Debug
{
  //------------------------------------------------------------------------------------------------
  HierarchyDolceWindow::HierarchyDolceWindow(SceneManager& sceneManager) :
    Dolce::DolceWindow("Hierarchy"),
    m_sceneManager(sceneManager)
  {
  }

  //------------------------------------------------------------------------------------------------
  void HierarchyDolceWindow::render()
  {
    for (const auto& rootGameObject : m_sceneManager.getRootGameObjects())
    {
      drawGameObject(rootGameObject);
    }
  }

  //------------------------------------------------------------------------------------------------
  void HierarchyDolceWindow::drawGameObject(GameObject& gameObject)
  {
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_AllowItemOverlap;

    if (gameObject.getChildCount() == 0)
    {
      flags |= ImGuiTreeNodeFlags_Leaf;
    }

    bool treeOpen = ImGui::TreeNodeEx(&gameObject, flags, "");
    
    ImGui::SameLine();

    bool isActive = gameObject.isActive();
    if (ImGui::Checkbox(gameObject.getName().debug_string(), &isActive))
    {
      gameObject.setActive(isActive);
    }

    if (treeOpen)
    {
      for (size_t i = 0; i < gameObject.getChildCount(); ++i)
      {
        drawGameObject(*gameObject.getChild(i));
      }

      ImGui::TreePop();
    }
  }
}