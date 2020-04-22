#include "Game/Game.h"
#include "OpenGL/GL.h"

#include "Lua/Components/LuaComponentManifestRegistry.h"
#include "Lua/LuaState.h"

#include "Settings/GameSettings.h"
#include "Settings/WindowSettings.h"

#include "Log/Log.h"

#if _DEBUG
#include "Debug/Windows/HierarchyDolceWindow.h"
#include "Debug/Windows/LuaScriptDolceWindow.h"
#include "Debug/Windows/LogDolceWindow.h"
#include "Debug/Logging/DolceLogger.h"
#include "Settings/DolceSettings.h"

#include "imgui.h"
#endif


namespace Celeste
{
  // Initialise static variables
  observer_ptr<Game> Game::m_current(nullptr);

  //------------------------------------------------------------------------------------------------
  Game::Game() :
    m_resourceManager(Path(Directory::getExecutingAppDirectory(), "Resources")),
    m_sceneManager(),
    m_window(),
    m_inputManager(m_window.getGLWindow()),
    m_physicsManager(),
    m_renderManager(),
    m_audioManager(),
    m_clock(),
    m_running(false)
#if _DEBUG
    , m_dolce(m_window.getGLWindow())
#endif
  {
    ASSERT(!m_current);
    m_current = this;
  }

  //------------------------------------------------------------------------------------------------
  Game::Game(
    int windowWidth,
    int windowHeight,
    OpenGLWindow::WindowMode windowMode,
    const std::string& windowTitle) :
    m_resourceManager(Path(Directory::getExecutingAppDirectory(), "Resources")),
    m_sceneManager(),
    m_window(windowWidth, windowHeight, windowMode, windowTitle),
    m_inputManager(m_window.getGLWindow()),
    m_physicsManager(),
    m_renderManager(),
    m_audioManager(),
    m_clock(),
    m_running(false)
#if _DEBUG
    , m_dolce(m_window.getGLWindow())
#endif
  {
    ASSERT(!m_current);
    m_current = this;
  }

  //------------------------------------------------------------------------------------------------
  Game::ResourceManager& Game::getResourceManager()
  {
    return m_current->m_resourceManager;
  }

  //------------------------------------------------------------------------------------------------
  SceneManager& Game::getSceneManager()
  {
    return m_current->m_sceneManager;
  }

  //------------------------------------------------------------------------------------------------
  OpenGLWindow& Game::getWindow()
  {
    return m_current->m_window;
  }

  //------------------------------------------------------------------------------------------------
  Game::InputManager& Game::getInputManager()
  {
    return m_current->m_inputManager;
  }

  //------------------------------------------------------------------------------------------------
  Game::PhysicsManager& Game::getPhysicsManager()
  {
    return m_current->m_physicsManager;
  }

  //------------------------------------------------------------------------------------------------
  Game::RenderManager& Game::getRenderManager()
  {
    return m_current->m_renderManager;
  }

  //------------------------------------------------------------------------------------------------
  Game::AudioManager& Game::getAudioManager()
  {
    return m_current->m_audioManager;
  }

  //------------------------------------------------------------------------------------------------
  Clock& Game::getClock()
  {
    return m_current->m_clock;
  }

#if _DEBUG
  //------------------------------------------------------------------------------------------------
  Dolce::Dolce& Game::getDolce()
  {
    return m_current->m_dolce;
  }
#endif

  //------------------------------------------------------------------------------------------------
  void Game::initialize()
  {
    glfwSetWindowCloseCallback(m_window.getGLWindow(), &Game::windowCloseFunc);

    // Call onInitialize first to give derived game classes the chance to register script commands
    // before their lua Game script is run
    applySettings();
    onInitialize();

#if _DEBUG
    initializeDolce();
#endif

    executeGameScript();
  }

  //------------------------------------------------------------------------------------------------
  void Game::applySettings() const
  {
    std::unique_ptr<Settings::WindowSettings> windowSettings = ScriptableObject::load<Settings::WindowSettings>(Path(Resources::getResourcesDirectory(), "Data", "Settings", "WindowSettings.asset"));
    if (windowSettings != nullptr)
    {
      windowSettings->apply();
    }

    std::unique_ptr<Settings::GameSettings> gameSettings = ScriptableObject::load<Settings::GameSettings>(Path(Resources::getResourcesDirectory(), "Data", "Settings", "GameSettings.asset"));
    if (gameSettings != nullptr)
    {
      gameSettings->apply();
    }

    // The window starts off hidden and we show it now after we have finished processing the window and game settings
    // This is to avoid glitches at the start whilst the window setup is potentially changed from the default values by the settings
    m_window.show();
  }

  //------------------------------------------------------------------------------------------------
  void Game::executeGameScript() const
  {
    Path gameLuaScriptPath(Resources::getResourcesDirectory(), "Scripts", "Game.lua");
    if (File::exists(gameLuaScriptPath))
    {
      auto result = Lua::LuaState::scriptFile(gameLuaScriptPath);
#if _DEBUG
      if (!result.valid())
      {
        ASSERT_FAIL();
      }
#elif
      UNUSED(result);
#endif
    }
  }

#if _DEBUG
  //------------------------------------------------------------------------------------------------
  void Game::initializeDolce()
  {
    Dolce::Dolce& dolce = getDolce();

    dolce.registerWindow(std::make_unique<Debug::HierarchyDolceWindow>(m_sceneManager));
    dolce.registerWindow(std::make_unique<Debug::LuaScriptDolceWindow>());
    auto& logWindow = dolce.registerWindow(std::make_unique<Debug::LogDolceWindow>());

    Path logPath(Directory::getExecutingAppDirectory(), "Log.txt");
    Celeste::Log::Logging::setLogger(std::make_unique<Log::DolceLogger>(logWindow, logPath));

    onInitializeDolce(dolce);

    std::unique_ptr<Settings::DolceSettings> dolceSettings = ScriptableObject::load<Settings::DolceSettings>(Path(Resources::getResourcesDirectory(), "Data", "Settings", "DolceSettings.asset"));
    if (dolceSettings != nullptr)
    {
      dolceSettings->applyTo(dolce);
    }
  }

  //------------------------------------------------------------------------------------------------
  void Game::shutdownDolce()
  {
    Path dolcePath(Resources::getResourcesDirectory(), "Data", "Settings", "DolceSettings.asset");
    std::unique_ptr<Settings::DolceSettings> dolceSettings = ScriptableObject::load<Settings::DolceSettings>(dolcePath);

    if (dolceSettings == nullptr)
    {
      dolceSettings = std::move(ScriptableObject::create<Settings::DolceSettings>("DolceSettings"));
    }
    
    dolceSettings->applyFrom(getDolce());
    dolceSettings->save(dolcePath);
  }
#endif

  //------------------------------------------------------------------------------------------------
  void Game::run()
  {
    // Make sure this variable is set before initialize - that way we can exit the game during the
    // Game.lua script if we want to perform some CLI task
    m_running = true;

    // Call awake on the clock to remove any wait time since start up
    initialize();
    m_clock.awake();

    // Game loop:
    // Measure the time since last frame
    // Get the elapsed in game time by using our fixed frame rate & time scale
    // If the time since last frame is greater than our elapsed game time we advance the game forward as many times
    // as necessary before the real time is in the range 0 <= real time <= elapsedGameTime
    // Then we draw the scene
    // The lag now is the amount leftover that the game is actually ahead of the simulation (i.e. realtime - elapsedgametime)
    // We can use that lag to compensate in the rendering by pretending that much extra simulation has occurred
    GLfloat elapsedRealTime = 0;

    while (m_running)
    {
      glfwPollEvents();

      m_clock.update();

      elapsedRealTime = m_clock.getElapsedDeltaTime();

      // If we have spent more than 1 second paused for some reason
      // we should not update the world - it will cause confusion in physics etc.
      if (elapsedRealTime < 1)
      {
        //float targetGameTime = m_clock.getTargetSecondsPerFrame() * m_clock.getTimeScale();

        handleInput();

        //while (elapsedRealTime > targetGameTime)
        {
          // Manage user input
          update(elapsedRealTime);

          //elapsedRealTime -= targetGameTime;
        }

        //update(elapsedRealTime);
        //elapsedRealTime = 0;
      }

      glClear(GL_COLOR_BUFFER_BIT);

      // Render
      render(0);

      glfwSwapBuffers(m_window.getGLWindow());
    }

    onExit();

    GL::terminate();

#if _DEBUG
    shutdownDolce();
#endif

    // We flush the logger here to allow it to write any remaining information
    // Then we reset it to allow proper cleanup before the app terminates
    Log::Logging::getLogger().flush();
    Log::Logging::setLogger(std::unique_ptr<Log::ILogger>(nullptr));
  }

  //------------------------------------------------------------------------------------------------
  void Game::handleInput()
  {
    if (m_inputManager.isActive())
    {
      m_inputManager.handleInput();
    }
    
    if (m_sceneManager.isActive())
    {
      m_sceneManager.handleInput();
    }

    if (m_physicsManager.isActive())
    {
      m_physicsManager.handleInput();
    }

    if (m_audioManager.isActive())
    {
      m_audioManager.handleInput();
    }

    if (m_renderManager.isActive())
    {
      m_renderManager.handleInput();
    }

    if (m_inputManager.getKeyboard().isKeyTapped(GLFW_KEY_ESCAPE))
    {
      glfwSetWindowShouldClose(m_window.getGLWindow(), GL_TRUE);
    }
  }

  //------------------------------------------------------------------------------------------------
  void Game::update(GLfloat elapsedGameTime)
  {
    if (m_inputManager.isActive())
    {
      m_inputManager.update(elapsedGameTime);
    }

    if (m_sceneManager.isActive())
    {
      m_sceneManager.update(elapsedGameTime);
    }

    if (m_physicsManager.isActive())
    {
      m_physicsManager.update(elapsedGameTime);
    }

    if (m_audioManager.isActive())
    {
      m_audioManager.update(elapsedGameTime);
    }

    if (m_renderManager.isActive())
    {
      m_renderManager.update(elapsedGameTime);
    }

    onUpdate(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  void Game::render(GLfloat lag)
  {
    m_renderManager.render(lag);

#if _DEBUG
    m_dolce.render();
#endif
  }

  //------------------------------------------------------------------------------------------------
  void Game::exit()
  {
    if (m_current != nullptr)
    {
      m_current->m_running = false;

      if (getWindow().getGLWindow())
      {
        glfwSetWindowShouldClose(getWindow().getGLWindow(), GL_TRUE);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void Game::windowCloseFunc(GLFWwindow* /*window*/)
  {
    Game::exit();
  }
}