#pragma once

#include "Events/EventHandle.h"

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
      using EventSubscriber = std::pair<EventHandle, Function>;

    public:
      Event() : m_callbacks() { }
      ~Event() = default;

      size_t getSubscriberCount() const { return m_callbacks.size(); }

      /// These methods are const so that we can expose the subscribe and unsubscribe through a const reference
      /// This saves a lot of boilerplate wrapper code in classes which use events

      EventHandle subscribe(const Function& callback) { return subscribe(callback, generateHandle()); }
      EventHandle subscribe(const Function& callback, EventHandle name)
      {
        m_callbacks[name] = callback;
        return name;
      }

      EventHandle subscribe(Function&& callback) { return subscribe(std::move(callback), generateHandle()); }
      EventHandle subscribe(Function&& callback, EventHandle name)
      {
        m_callbacks[name] = std::move(callback);
        return name;
      }
 
      void unsubscribe(EventHandle callbackId)
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
        std::unordered_map<EventHandle, Function> callbacks = m_callbacks;

        for (const EventSubscriber& func : callbacks)
        {
          func.second(args...);
        }
      }

    private:
      EventHandle generateHandle() const
      {
        EventHandle handle = EventHandle();
        ++handle;

        while (m_callbacks.find(handle) != m_callbacks.end())
        {
          ++handle;
        }

        return handle;
      }

      std::unordered_map<EventHandle, Function> m_callbacks;
  };
}