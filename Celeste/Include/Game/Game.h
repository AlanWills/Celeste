#pragma once

#include "Resources/ResourceManager.h"
#include "Viewport/OpenGLWindow.h"
#include "Time/Clock.h"
#include "CelesteStl/Memory/ObserverPtr.h"
#include "System/ISystemContainer.h"
#include "System/ISystem.h"
#include "static_type_info.h"

#include <memory>
#include <unordered_map>


namespace Dolce
{
  class IDolce;
}

namespace Celeste
{
  /// Grouper class for all of the game managers
  /// Also contains general meta data about the game and window
  class Game : public System::ISystemContainer
  {
    private:
      using ResourceManager = Resources::ResourceManager;

    public:
      CelesteDllExport Game();
      CelesteDllExport Game(
        int windowWidth,
        int windowHeight,
        OpenGLWindow::WindowMode windowMode,
        const std::string& windowTitle);
      CelesteDllExport ~Game() override = default;

      /// \brief Begin our game loop
      CelesteDllExport void run();

      /// \brief Triggers an exit of the application.  Can use the callback for button events.
      static CelesteDllExport void exit();

      /// Returns true if run() has been called on the game and false if exit() has been called.
      inline bool isRunning() const { return m_running; }
      
      CelesteDllExport static Game& current();

      CelesteDllExport void addSystem(static_type_info::TypeIndex id, std::unique_ptr<System::ISystem>&& system) override;
      CelesteDllExport void removeSystem(static_type_info::TypeIndex id) override;
      CelesteDllExport System::ISystem* getSystem(static_type_info::TypeIndex id) override;

      template <typename TSystem, typename ...Args>
      void addSystem(Args&&... arguments);

      template <class TSystem>
      TSystem* getSystem();

      template <class TSystem>
      const TSystem* getSystem() const;

      CelesteDllExport ResourceManager& getResourceManager();
      CelesteDllExport OpenGLWindow& getWindow();
      CelesteDllExport Clock& getClock();

    protected:
      virtual void onInitialize() { }
      virtual void onInitializeDolce(Dolce::IDolce& /*dolce*/) {}
      virtual void onUpdate(float /*elapsedGameTime*/) { }
      virtual void onExit() { }

    private:
      using Systems = std::unordered_map<static_type_info::TypeIndex, std::unique_ptr<System::ISystem>>;

      Game(const Game&) = delete;
      Game& operator=(const Game&) = delete;

      void registerSystems();
      void initialize();
      void update(GLfloat elapsedGameTime);
      void render(GLfloat lag);

      void applySettings() const;
      void executeGameScript() const;

#if _DEBUG
      void initializeDolce();
      void shutdownDolce();
#endif

      static void windowCloseFunc(GLFWwindow* window);

      static observer_ptr<Game> m_current;

      ResourceManager m_resourceManager;
      OpenGLWindow m_window;
      Clock m_clock;
      Systems m_systems;

      bool m_running = false;
  };


  //------------------------------------------------------------------------------------------------
  template <typename TSystem, typename ...Args>
  void Game::addSystem(Args&&... arguments)
  {
    addSystem(static_type_info::getTypeIndex<TSystem>(), std::make_unique<TSystem>(std::forward<Args>(arguments)...));
  }

  //------------------------------------------------------------------------------------------------
  template <class TSystem>
  TSystem* Game::getSystem()
  {
    return static_cast<TSystem*>(getSystem(static_type_info::getTypeIndex<TSystem>()));
  }

  //------------------------------------------------------------------------------------------------
  template <class TSystem>
  const TSystem* Game::getSystem() const
  {
    return const_cast<Game*>(this)->getSystem<TSystem>();
  }
}