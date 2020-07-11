#pragma once

#define DECLARE_SCRIPTABLE_OBJECT(Type, DllExport) \
  public: \
    static constexpr const char* const type_name() { return #Type; } \
    \
    Type(const Type&) = delete; \
    Type& operator=(const Type&) = delete; \
    \
  protected: \
    DllExport Type(); \
    \
    const std::string getTypeName() const override { return type_name(); } \
    \
  private: \
    static bool m_registered; \
    friend class Celeste::ScriptableObject;

#define REGISTER_SCRIPTABLE_OBJECT(Type) \
    bool Type::m_registered = Celeste::ScriptableObjectRegistry::addScriptableObject<Type>();
