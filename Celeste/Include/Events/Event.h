#pragma once

#include "UID/StringId.h"

#include <functional>
#include <unordered_map>


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  template <typename ...ArgTypes>
  class Event
  {
    public:
      using Function = std::function<void(ArgTypes...)>;

    private:
      using EventSubscriber = std::pair<StringId, Function>;

    public:
      Event() : m_callbacks() { }
      ~Event() = default;

      size_t getSubscriberCount() const { return m_callbacks.size(); }

      /// These methods are const so that we can expose the subscribe and unsubscribe through a const reference
      /// This saves a lot of boilerplate wrapper code in classes which use events

      StringId subscribe(const Function& callback) { return subscribe(callback, generateUniqueId()); }
      StringId subscribe(const Function& callback, const std::string& name) { return subscribe(callback, internString(name)); }
      StringId subscribe(const Function& callback, StringId name)
      {
        m_callbacks[name] = callback;
        return name;
      }

      StringId subscribe(Function&& callback) { return subscribe(std::move(callback), generateUniqueId()); }
      StringId subscribe(Function&& callback, const std::string& name) { return subscribe(std::move(callback), internString(name)); }
      StringId subscribe(Function&& callback, StringId name)
      {
        m_callbacks[name] = std::move(callback);
        return name;
      }
 
      void unsubscribe(const std::string& name) { unsubscribe(internString(name)); }
      void unsubscribe(StringId callbackId)
      { 
        auto it = m_callbacks.find(callbackId);
        if (it != m_callbacks.end())
        {
          m_callbacks.erase(it);
        }
      }

      void unsubscribeAll() { m_callbacks.clear(); }

      void invoke(ArgTypes... args) const
      {
        // Copy here to allow subscribers to unsubscribe themselves in callbacks
        // e.g. when a game object dies inside callback
        std::unordered_map<StringId, Function> callbacks = m_callbacks;

        for (const EventSubscriber& func : callbacks)
        {
          func.second(args...);
        }
      }

    private:
      StringId generateUniqueId() const
      {
        StringId id = 1;
        while (m_callbacks.find(id) != m_callbacks.end())
        {
          ++id;
        }

        return id;
      }

      std::unordered_map<StringId, Function> m_callbacks;
  };
}