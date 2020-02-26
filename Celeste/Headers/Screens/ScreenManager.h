#pragma once

#include "ScreenUtils.h"
#include "Objects/Entity.h"
#include "Viewport/OpenGLWindow.h"
#include "Memory/Iterators/EntityAllocatorIterator.h"
#include "Memory/ObserverPtr.h"


namespace Celeste
{
  class Screen;

  class ScreenManager : public Entity
  {
    public:
      CelesteDllExport ScreenManager();
      CelesteDllExport ~ScreenManager();

      // Do not want to allow copying of this object
      ScreenManager(const ScreenManager&) = delete;
      ScreenManager& operator=(const ScreenManager&) = delete;

      /// Get the window
      CelesteDllExport OpenGLWindow* getWindow() const;

      CelesteDllExport EntityAllocatorIterator<const Screen> begin() const;
      CelesteDllExport EntityAllocatorIterator<const Screen> end() const;

      observer_ptr<Screen> findScreen(const std::string& name) { return findScreen(internString(name)); }
      CelesteDllExport observer_ptr<Screen> findScreen(StringId name);

    protected:
      void onHandleInput() override;
      void onUpdate(float elapsedGameTime) override;
      void onDeath() override;

    private:
      using Inherited = Entity;

      /// The GL window context
      std::unique_ptr<OpenGLWindow> m_window;
  };
}