#pragma once

#include <chrono>
#include <string>


namespace Celeste
{
  /// A wrapper around some profiling information
  /// Most of the implementation of this will be hidden except for a data access interface
  class ProfilingBlock
  {
    public:
      typedef std::chrono::time_point<std::chrono::system_clock> SystemClockTime;
      typedef std::chrono::seconds Seconds;

      /// TODO:
      /// Hide the constructors and destructors so only profiler can create them
      ProfilingBlock() : m_averageTimeTaken(0), m_lastCallTimeTaken(0), m_numCalls(0), m_closed(true) { }

      /// Getters for data - no public setters though (we want this class to be only be useful through using the Profiler)
      const std::string& getName() const { return m_name; }
      Seconds getAverageTimeTaken() const { return m_averageTimeTaken; }
      Seconds getLastCallTimeTaken() const { return m_lastCallTimeTaken; }
      int getNumCalls() const { return m_numCalls; }
      SystemClockTime getStartTime() const { return m_startTime; }
    
      bool isClosed() const { return m_closed; }
      void open() { m_closed = false; }
      void close() { m_closed = true; }

    private:
      std::string m_name;

      /// An average of the time taken to run the block
      Seconds m_averageTimeTaken;

      /// The time taken for the last call
      Seconds m_lastCallTimeTaken;

      /// The number of times this profiling block has been entered
      int m_numCalls;

      /// The amount of time elapsed over the current call
      SystemClockTime m_startTime;

      /// A flag to indicate whether this block has been successfully closed off
      bool m_closed;

      friend class Profiler;
  };
};