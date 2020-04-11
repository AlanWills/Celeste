#pragma once

#include "UID/StringId.h"
#include "Debug/Logging/FileLogger.h"
#include "Debug/Profiling/ProfilingBlock.h"
#include "Memory/Allocators/PoolAllocator.h"
#include "IProfiler.h"

#include <unordered_map>
#include <memory>


namespace Celeste
{
  // TODO: Profiling hierarchy so we do not get overlap in our profiling times

  #define MAX_PROFILING_BLOCKS 100

  // Times sections of code and records them in a database with appropriate information
  // Also outputs results to a log file
  class Profiler : public IProfiler
  {
    public:
      CelesteDllExport Profiler(const std::string& profilingFileFullPath);
      CelesteDllExport Profiler(const Path& profilingFilePath) : Profiler(profilingFilePath.as_string()) { }
      CelesteDllExport ~Profiler() override;

      /// \brief Begin a profiling block
      /// Will create a new block if one for the inputted profiling name does not exist
      CelesteDllExport void beginProfilingBlock(const std::string& profilingBlockName) override;

      /// \brief Close off the profiling block and check the input matches the current block running
      CelesteDllExport void endProfilingBlock(const std::string& profilingBlockName) override;

      /// \brief Return a profiling block corresponding to the inputted name to inspect the current profiling results
      /// Returns null if profiling block does not exist
      CelesteDllExport const ProfilingBlock* getProfilingBlock(const std::string& profilingBlockName) override;

      /// \brief Returns the name of the profiling block that was most recently created
      const std::string& getCurrentProfilingBlockName() const { return m_currentBlockName; }

    private:
      /// \brief Build our profiling information into a string and write it to our log
      void logProfilingBlockInfo(const std::pair<StringId, ProfilingBlock>& profilingInfo);

      /// The map we will store profiling information in
      std::unordered_map<StringId, ProfilingBlock> m_profilingInfo;

      /// Not necessary, but useful for debugging to make people aware they have closed off profiling blocks incorrectly
      std::string m_currentBlockName;

      /// The logger we will use to write profiling information to a file
      Log::FileLogger m_logger;
  };
}