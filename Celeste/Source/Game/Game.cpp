#include "Game/Game.h"
#include "OpenGL/GL.h"

#include "Lua/Components/LuaComponentManifestRegistry.h"
#include "Lua/LuaState.h"

#include "Serialization/MathsSerializers.h"
#include "Settings/GameSettings.h"
#include "Settings/StartupSettings.h"

#include "Log/Log.h"
#include "Debug/Logging/FileLogger.h"
#include "Scene/SceneManager.h"
#include "Input/InputManager.h"
#include "Physics/PhysicsManager.h"
#include "Rendering/RenderManager.h"
#include "Audio/AudioManager.h"
#include "Layout/LayoutSystem.h"

#if _DEBUG
#include "Dolce/Dolce.h"
#include "Debug/Windows/HierarchyDolceWindow.h"
#include "Debug/Windows/LuaScriptDolceWindow.h"
#include "Debug/Windows/LogDolceWindow.h"
#include "Debug/Logging/DolceLogger.h"
#include "Settings/DolceSettings.h"

#include "imgui/imgui.h"
#else
#include "Dolce/DolceDummy.h"
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
    addSystem<Layout::LayoutSystem>(m_window);

#if _DEBUG
    std::unique_ptr<System::ISystem> dolce = std::make_unique<Dolce::Dolce>(m_window.getGLWindow());
#else
    std::unique_ptr<System::ISystem> dolce = std::make_unique<Dolce::DolceDummy>();
#endif
    addSystem(static_type_info::getTypeIndex<Dolce::IDolce>(), std::move(dolce));
  }

  //------------------------------------------------------------------------------------------------
  void Game::deregisterSystems()
  {
    // Can specify a custom deregistration order if we need it
    m_systems.clear();
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
    std::unique_ptr<Settings::StartupSettings> startupSettings = ScriptableObject::load<Settings::StartupSettings>(Settings::StartupSettings::SETTINGS_RELATIVE_PATH);
    if (startupSettings != nullptr)
    {
      startupSettings->apply();
    }

    std::unique_ptr<Settings::GameSettings> gameSettings = ScriptableObject::load<Settings::GameSettings>(Settings::GameSettings::SETTINGS_RELATIVE_PATH);
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
      Lua::LuaState::scriptFile(gameLuaScriptPath);
    }
  }

#if _DEBUG
  //------------------------------------------------------------------------------------------------
  void Game::initializeDolce()
  {
    Dolce::IDolce* dolcePtr = getSystem<Dolce::IDolce>();
    Dolce::Dolce& dolce = static_cast<Dolce::Dolce&>(*dolcePtr);

    dolce.addWindow(std::make_unique<Debug::HierarchyDolceWindow>(*getSystem<SceneManager>()));
    dolce.addWindow(std::make_unique<Debug::LuaScriptDolceWindow>());
    auto logWindow = dolce.addWindow(std::make_unique<Debug::LogDolceWindow>());

    Path logPath(Directory::getExecutingAppDirectory(), "Log.txt");
    Celeste::Log::Logging::setLogger(std::make_unique<Log::DolceLogger>(*logWindow, logPath));

    onInitializeDolce(dolce);

    std::unique_ptr<Settings::DolceSettings> dolceSettings = ScriptableObject::load<Settings::DolceSettings>(Settings::DolceSettings::SETTINGS_RELATIVE_PATH);
    if (dolceSettings != nullptr)
    {
      dolceSettings->applyTo(dolce);
    }
  }

  //------------------------------------------------------------------------------------------------
  void Game::shutdownDolce()
  {
    std::unique_ptr<Settings::DolceSettings> dolceSettings = ScriptableObject::load<Settings::DolceSettings>(Settings::DolceSettings::SETTINGS_RELATIVE_PATH);

    if (dolceSettings == nullptr)
    {
      dolceSettings = ScriptableObject::create<Settings::DolceSettings>("DolceSettings");
    }

    dolceSettings->applyFrom(*getSystem<Dolce::IDolce>());
    dolceSettings->save(Settings::DolceSettings::SETTINGS_RELATIVE_PATH);
  }
#endif

  //------------------------------------------------------------------------------------------------
  void Game::run()
  {
    // Make sure this variable is set before initialize - that way we can exit the game during the
    // Game.lua script if we want to perform some CLI task
    m_running = true;

    initialize();

    // Game loop:
    // Measure the time since last frame
    // Get the elapsed in game time by using our fixed frame rate & time scale
    // If the time since last frame is greater than our elapsed game time we advance the game forward as many times
    // as necessary before the real time is in the range 0 <= real time <= elapsedGameTime
    // Then we draw the scene
    // The lag now is the amount leftover that the game is actually ahead of the simulation (i.e. realtime - elapsedgametime)
    // We can use that lag to compensate in the rendering by pretending that much extra simulation has occurred
    GLfloat elapsedRealTime = 0;
    auto previous = std::chrono::high_resolution_clock::now();

    while (m_running)
    {
      glfwPollEvents();

      auto current = std::chrono::high_resolution_clock::now();
      m_clock.update(std::chrono::duration<float, std::ratio<1, 1>>(current - previous).count());
      previous = current;

      elapsedRealTime = m_clock.getElapsedDeltaTime();

      // Can also implement fixed update here by performing as many fixed update calls as is required to get the elapsedRealTime below
      // the target FPS in the clock
      update(elapsedRealTime);

      glClear(GL_COLOR_BUFFER_BIT);

      // Render
      render(0);

      glfwSwapBuffers(m_window.getGLWindow());
    }

    onExit();

#if _DEBUG
    shutdownDolce();
#endif

    deregisterSystems();

    GL::terminate();

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
    getSystem<Dolce::IDolce>()->render();
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