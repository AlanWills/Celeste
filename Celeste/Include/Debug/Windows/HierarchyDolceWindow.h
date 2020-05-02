#pragma once

#include "Dolce/DolceWindow.h"


namespace Celeste
{
  class SceneManager;
  class GameObject;
}

namespace Celeste::Debug
{
  class HierarchyDolceWindow : public Dolce::DolceWindow
  {
    public:
      HierarchyDolceWindow(SceneManager& m_sceneManager);
      ~HierarchyDolceWindow() override = default;

      void render() override;

    private:
      void drawGameObject(GameObject& gameObject);

      SceneManager& m_sceneManager;
  };
}