#pragma once

#include "Resources/ResourceManager.h"
#include "Scene/SceneManager.h"
#include "Viewport/OpenGLWindow.h"
#include "Input/InputManager.h"
#include "Physics/PhysicsManager.h"
#include "Rendering/RenderManager.h"
#include "Audio/AudioManager.h"
#include "Time/Clock.h"
#include "Memory/ObserverPtr.h"

#if _DEBUG
#include "Dolce.h"
#endif

#include <memory>


namespace Celeste
{
  /// Grouper class for all of the game managers
  /// Also contains general meta data about the game and window
  class Game
  {
    private:
      using ResourceManager = Resources::ResourceManager;
      using InputManager = Input::InputManager;
      using PhysicsManager = Physics::PhysicsManager;
      using RenderManager = Rendering::RenderManager;
      using AudioManager = Audio::AudioManager;

    public:
      CelesteDllExport Game();
      CelesteDllExport Game(
        int windowWidth,
        int windowHeight,
        OpenGLWindow::WindowMode windowMode,
        const std::string& windowTitle);
      CelesteDllExport virtual ~Game() = default;

      /// \brief Begin our game loop
      CelesteDllExport void run();

      /// \brief Triggers an exit of the application.  Can use the callback for button events.
      static CelesteDllExport void exit();

      /// Returns true if run() has been called on the game and false if exit() has been called.
      inline bool isRunning() const { return m_running; }

      CelesteDllExport static ResourceManager& getResourceManager();
      CelesteDllExport static SceneManager& getSceneManager();
      CelesteDllExport static OpenGLWindow& getWindow();
      CelesteDllExport static InputManager& getInputManager();
      CelesteDllExport static PhysicsManager& getPhysicsManager();
      CelesteDllExport static RenderManager& getRenderManager();
      CelesteDllExport static AudioManager& getAudioManager();
      CelesteDllExport static Clock& getClock();

#if _DEBUG
      CelesteDllExport static Dolce::Dolce& getDolce();
#endif

    protected:
      virtual void onInitialize() { }
      virtual void onUpdate(float /*elapsedGameTime*/) { }
      virtual void onExit() { }

#if _DEBUG
      virtual void onInitializeDolce(Dolce::Dolce& /*dolce*/) {}
#endif

    private:
      Game(const Game&) = delete;
      Game& operator=(const Game&) = delete;

      void initialize();
      void handleInput();
      void update(GLfloat elapsedGameTime);
      void render(GLfloat lag);

      void applySettings() const;
      void executeGameScript() const;

#if _DEBUG
      void initializeDolce();
#endif

      static void windowCloseFunc(GLFWwindow* window);

      static observer_ptr<Game> m_current;

      ResourceManager m_resourceManager;
      SceneManager m_sceneManager;
      OpenGLWindow m_window;
      InputManager m_inputManager;
      PhysicsManager m_physicsManager;
      RenderManager m_renderManager;
      AudioManager m_audioManager;
      Clock m_clock;
      bool m_running;

#if _DEBUG
      Dolce::Dolce m_dolce;
#endif
  };
}