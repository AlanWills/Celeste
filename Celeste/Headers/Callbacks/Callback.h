#pragma once

#include <string>


namespace Celeste
{
  #define DECLARE_CALLBACK(Type) \
    public: \
      inline static std::string name() { return #Type; } \
      \
    private: \
      static bool m_registered;

  #define REGISTER_CALLBACK(Type) \
    bool Type::m_registered = Celeste::CallbackRegistry::addCallback<Type>();
}