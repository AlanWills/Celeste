#pragma once

#if _DEBUG
#define SCRIPTABLE_OBJECT_TYPE_FUNCTION(TypeName) \
  protected: \
    void type_info_i(std::unique_ptr<Celeste::Reflection::ITypeInfo>& output) const override { output.reset(new Celeste::Reflection::Type<TypeName>()); }
#else
#define SCRIPTABLE_OBJECT_TYPE_FUNCTION(Type)
#endif

#if _DEBUG
#define SCRIPTABLE_OBJECT_BINDINGS_GENERATION(Type) \
  protected: \
    void generateBinding(std::string& output) const override \
    { \
      const std::string& name = getName().empty() ? Celeste::Bindings::variableNameToDisplayName(#Type) : getName(); \
      output.append("\t\t[DisplayName(\""); \
      output.append(name); \
      output.append("\")]\n"); \
      output.append("\t\tpublic "); \
      output.append(#Type); \
      output.push_back(' '); \
      output.append(Celeste::Bindings::displayNameToVariableName(name)); \
      output.append(" { get; set; }"); \
    }
#else
#define SCRIPTABLE_OBJECT_BINDINGS_GENERATION(Type)
#endif

#define DECLARE_UNMANAGED_COMPONENTABLE_OBJECT(Type, DllExport) \
  public: \
    static std::string type_name() { return #Type; } \
    \
    Type(const Type&) = delete; \
    Type& operator=(const Type&) = delete; \
    \
    SCRIPTABLE_OBJECT_TYPE_FUNCTION(Type) \
    SCRIPTABLE_OBJECT_BINDINGS_GENERATION(Type) \
  protected: \
    DllExport Type(); \
    \
  private: \
    static bool m_registered; \
    friend class Celeste::ScriptableObject;

#define REGISTER_UNMANAGED_COMPONENTABLE_OBJECT(Type) \
    bool Type::m_registered = Celeste::ScriptableObjectRegistry::addScriptableObject<Type>();
