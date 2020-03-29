#pragma once

#include "CelesteDllExport.h"

#include "Objects/ScriptableObject.h"
#include "Objects/Object.h"

#include "Lua/LuaState.h"


namespace Celeste::Lua
{
  namespace Internals
  {
    //------------------------------------------------------------------------------------------------
    template <class T>
    T* __as(Object* ptr)
    {
      return dynamic_cast<T*>(ptr);
    }

    //------------------------------------------------------------------------------------------------
    template <typename T>
    sol::object as(T* object, const std::string& typeName)
    {
      sol::table typeTable = Lua::LuaState::instance()[typeName].get_or<sol::table>(sol::nil);
      if (!typeTable.valid())
      {
        return sol::nil;
      }

      sol::protected_function internalAs = typeTable.get_or<sol::protected_function>("__as", sol::nil);
      if (!internalAs.valid())
      {
        return sol::nil;
      }

      sol::protected_function_result result = internalAs.call(reinterpret_cast<Object*>(object));
      if (!result.valid())
      {
        return sol::nil;
      }

      return result.get<sol::object>();
    }
  }

  //------------------------------------------------------------------------------------------------
  template <typename T, bool is_reference>
  T addition(
    typename choose_class<is_reference, T, const T&>::type lhs,
    typename choose_class<is_reference, T, const T&>::type rhs)
  {
    return lhs + rhs;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T, bool is_reference>
  T subtraction(
    typename choose_class<is_reference, T, const T&>::type lhs,
    typename choose_class<is_reference, T, const T&>::type rhs)
  {
    return lhs - rhs;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T, bool is_reference>
  T multiplication(
    typename choose_class<is_reference, T, const T&>::type lhs,
    typename choose_class<is_reference, T, const T&>::type rhs)
  {
    return lhs * rhs;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T, bool is_reference>
  T division(
    typename choose_class<is_reference, T, const T&>::type lhs,
    typename choose_class<is_reference, T, const T&>::type rhs)
  {
    return lhs / rhs;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  std::unique_ptr<T> loadScriptableObject(const std::string& path)
  {
    return ScriptableObject::load<T>(path);
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  std::unique_ptr<T> createScriptableObject(const std::string& name)
  {
    return ScriptableObject::create<T>(name);
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void saveScriptableObject(T& scriptableObject, const std::string& path)
  {
    scriptableObject.save(path);
  }

  //------------------------------------------------------------------------------------------------
  template <typename Class, typename... Args>
  void registerUserType(const std::string& name, Args&& ... args)
  {
    sol::state& state = LuaState::instance();
    ASSERT(!state[name].valid());

    if (!state[name].valid())
    {
      state.new_usertype<Class>(
        name,
        std::forward<Args>(args)...,
        "__as", &Celeste::Lua::Internals::template __as<Class>,
        "as", &Celeste::Lua::Internals::template as<Class>);
    }
  }

  //------------------------------------------------------------------------------------------------
  template <typename Class, typename... Args>
  void registerScriptableObjectUserType(const std::string& name, Args&& ... args)
  {
    sol::state& state = LuaState::instance();
    ASSERT(!state[name].valid());
    
    if (!state[name].valid())
    {
      state.new_usertype<Class>(
        name,
        "create", sol::factories(&createScriptableObject<Class>),
        "load", sol::factories(&loadScriptableObject<Class>),
        "save", &saveScriptableObject<Class>,
        std::forward<Args>(args)...);
    }
  }

  //------------------------------------------------------------------------------------------------
  template <typename TEvent, typename ...ArgTypes>
  void subscribeToEvent(
    const TEvent& e,
    sol::protected_function function,
    sol::object extraArgs)
  {
    if (!function.valid())
    {
      ASSERT_FAIL();
      return;
    }

    e.subscribe([function, extraArgs](ArgTypes... args) -> void
      {
        ASSERT(function.valid());
        auto result = function.call(args..., extraArgs);

        if (!result.valid())
        {
          sol::error error = result;
          LOG(error.what());
        }
      });
  }
}

namespace sol
{
  template <>
  struct is_to_stringable<Celeste::Object> : std::false_type {};

  template <>
  struct is_to_stringable<Celeste::ScriptableObject> : std::false_type {};
}