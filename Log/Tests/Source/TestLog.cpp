#include "TestUtils/TestUtils.h"

#include "Log/Log.h"
#include "FileSystem/Path.h"
#include "FileSystem/Directory.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

using namespace Celeste;
using namespace Celeste::Log;


namespace TestLog
{
  BASE_TEST_CLASS(TestLog)

  std::shared_ptr<spdlog::logger> defaultLogger;

  //------------------------------------------------------------------------------------------------
  void TestLog::testInitialize() override
  {
    defaultLogger = spdlog::default_logger();
  }

  //------------------------------------------------------------------------------------------------
  void TestLog::testCleanup() override
  {
    spdlog::set_default_logger(defaultLogger);
  }

#pragma region Add Sink Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Log_AddSink_AddsSinkToDefaultLogger)
  {
    std::shared_ptr<spdlog::logger> logger = spdlog::create<spdlog::sinks::stdout_sink_mt>("Log");
    spdlog::set_default_logger(logger);

    Assert::AreEqual(static_cast<size_t>(1), logger->sinks().size());

    std::shared_ptr<spdlog::sinks::stderr_sink_st> sink = std::make_shared<spdlog::sinks::stderr_sink_st>();
    addSink(sink);

    Assert::AreEqual(static_cast<size_t>(2), logger->sinks().size());
    Assert::IsTrue(sink == logger->sinks()[1]);
  }

#pragma endregion

#pragma region Add File Sink Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Log_AddFileSink_AddsFileSinkToDefaultLogger)
  {
    std::shared_ptr<spdlog::logger> logger = spdlog::create<spdlog::sinks::stdout_sink_mt>("Log");
    spdlog::set_default_logger(logger);

    Assert::AreEqual(static_cast<size_t>(1), logger->sinks().size());

    addFileSink("Log.txt");

    Assert::AreEqual(static_cast<size_t>(2), logger->sinks().size());
    Assert::IsNotNull(dynamic_cast<spdlog::sinks::basic_file_sink_mt*>(logger->sinks()[1].get()));
  }

#pragma endregion

#pragma region Remove Sink Tests

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Log_RemoveSink_InputtingUnregisteredSink_DoesNothing)
  {
    std::shared_ptr<spdlog::logger> logger = spdlog::create<spdlog::sinks::stdout_sink_mt>("Log");
    spdlog::set_default_logger(logger);

    Assert::AreEqual(static_cast<size_t>(1), logger->sinks().size());

    auto original = logger->sinks()[0];
    std::shared_ptr<spdlog::sinks::stderr_sink_st> sink = std::make_shared<spdlog::sinks::stderr_sink_st>();
    removeSink(sink);

    Assert::AreEqual(static_cast<size_t>(1), logger->sinks().size());
    Assert::IsTrue(original == logger->sinks()[0]);
  }

  //------------------------------------------------------------------------------------------------
  TEST_METHOD(Log_RemoveSink_InputtingRegisteredSink_RemovesSink)
  {
    std::shared_ptr<spdlog::logger> logger = spdlog::create<spdlog::sinks::stdout_sink_mt>("Log");
    spdlog::set_default_logger(logger);

    Assert::AreEqual(static_cast<size_t>(1), logger->sinks().size());

    std::shared_ptr<spdlog::sinks::stderr_sink_st> sink = std::make_shared<spdlog::sinks::stderr_sink_st>();
    addSink(sink);

    Assert::AreEqual(static_cast<size_t>(2), logger->sinks().size());
    Assert::IsTrue(sink == logger->sinks()[1]);

    removeSink(sink);

    Assert::AreEqual(static_cast<size_t>(1), logger->sinks().size());
    Assert::IsTrue(sink != logger->sinks()[0]);
  }

#pragma endregion

  };
}