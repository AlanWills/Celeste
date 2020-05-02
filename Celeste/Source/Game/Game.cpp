#include "Game/Game.h"
#include "OpenGL/GL.h"

#include "Lua/Components/LuaComponentManifestRegistry.h"
#include "Lua/LuaState.h"

#include "Settings/GameSettings.h"
#include "Settings/WindowSettings.h"

#include "Log/Log.h"
#include "Scene/SceneManager.h"
#include "Input/InputManager.h"
#include "Physics/PhysicsManager.h"
#include "Rendering/RenderManager.h"
#include "Audio/AudioManager.h"

#if _DEBUG
#include "Dolce/Dolce.h"
#include "Debug/Windows/HierarchyDolceWindow.h"
#include "Debug/Windows/LuaScriptDolceWindow.h"
#include "Debug/Windows/LogDolceWindow.h"
#include "Debug/Logging/DolceLogger.h"
#include "Settings/DolceSettings.h"

#include "imgui/imgui.h"
#endif


namespace Celeste
{
  // Initialise static variables
  observer_ptr<Game> Game::m_current(nullptr);

  //------------------------------------------------------------------------------------------------
  Game::Game() :
    m_resourceManager(Path(Directory::getExecutingAppDirectory(), "Resources")),
    m_window(),
    m_clock()
  {
    ASSERT(!m_current);
    m_current = this;

    registerSystems();
  }

  //------------------------------------------------------------------------------------------------
  Game::Game(
    int windowWidth,
    int windowHeight,
    OpenGLWindow::WindowMode windowMode,
    const std::string& windowTitle) :
    m_resourceManager(Path(Directory::getExecutingAppDirectory(), "Resources")),
    m_window(windowWidth, windowHeight, windowMode, windowTitle),
    m_clock()
  {
    ASSERT(!m_current);
    m_current = this;

    registerSystems();
  }

  //------------------------------------------------------------------------------------------------
  Game& Game::current()
  {
    return *m_current;
  }

  //------------------------------------------------------------------------------------------------
  Game::ResourceManager& Game::getResourceManager()
  {
    return m_resourceManager;
  }

  //------------------------------------------------------------------------------------------------
  OpenGLWindow& Game::getWindow()
  {
    return m_window;
  }

  //------------------------------------------------------------------------------------------------
  Clock& Game::getClock()
  {
    return m_clock;
  }

  //------------------------------------------------------------------------------------------------
  void Game::addSystem(static_type_info::TypeIndex id, std::unique_ptr<System::ISystem>&& system)
  {
    ASSERT(m_systems.find(id) == m_systems.end());
    if (m_systems.find(id) == m_systems.end())
    {
      m_systems.emplace(id, std::move(system));
    }
  }

  //------------------------------------------------------------------------------------------------
  void Game::removeSystem(static_type_info::TypeIndex id)
  {
    ASSERT(m_systems.find(id) != m_systems.end());
    if (m_systems.find(id) != m_systems.end())
    {
      m_systems.erase(id);
    }
  }

  //------------------------------------------------------------------------------------------------
  System::ISystem* Game::getSystem(static_type_info::TypeIndex id)
  {
    ASSERT(m_systems.find(id) != m_systems.end());
    return m_systems.find(id) != m_systems.end() ? m_systems.at(id).get() : nullptr;
  }

  //------------------------------------------------------------------------------------------------
  void Game::registerSystems()
  {
    addSystem<SceneManager>();
    addSystem<Input::InputManager>(m_window.getGLWindow());
    addSystem<Physics::PhysicsManager>();
    addSystem<Rendering::RenderManager>();
    addSystem<Audio::AudioManager>();

#if _DEBUG
    addSystem<Dolce::Dolce>(m_window.getGLWindow());
#endif
  }

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
    Dolce::Dolce* dolcePtr = getSystem<Dolce::Dolce>();
    Dolce::Dolce& dolce = *dolcePtr;

    dolce.registerWindow(std::make_unique<Debug::HierarchyDolceWindow>(*getSystem<SceneManager>()));
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

    dolceSettings->applyFrom(*getSystem<Dolce::Dolce>());
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
  void Game::update(GLfloat elapsedGameTime)
  {
    for (const auto& systemPair : m_systems)
    {
      systemPair.second->update(elapsedGameTime);
    }

    onUpdate(elapsedGameTime);
  }

  //------------------------------------------------------------------------------------------------
  void Game::render(GLfloat lag)
  {
    getSystem<Rendering::RenderManager>()->render(lag);

#if _DEBUG
    getSystem<Dolce::Dolce>()->render();
#endif
  }

  //------------------------------------------------------------------------------------------------
  void Game::exit()
  {
    if (m_current != nullptr)
    {
      m_current->m_running = false;

      if (m_current->getWindow().getGLWindow())
      {
        glfwSetWindowShouldClose(m_current->getWindow().getGLWindow(), GL_TRUE);
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void Game::windowCloseFunc(GLFWwindow* /*window*/)
  {
    Game::exit();
  }
}