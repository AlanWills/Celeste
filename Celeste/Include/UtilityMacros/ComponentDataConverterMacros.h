#pragma once


#define DECLARE_MANAGED_COMPONENT_DATA_CONVERTER(ConverterType, CompType, DllExport) \
  public: \
    using ComponentType = CompType; \
    \
    DllExport ConverterType(); \
    ConverterType(const ConverterType&) = delete; \
    ConverterType& operator=(const ConverterType&) = delete; \
    \
    void instantiate(std::unique_ptr<Celeste::ComponentDataConverter>& output) override \
    { \
      output.reset(new ConverterType()); \
    } \
    \
  protected: \
    DllExport void doSetValues(Celeste::Component& component) const override; \
    \
  private: \
    void doSetValues(CompType& component) const; \
    \
    static bool m_registered;

#define REGISTER_COMPONENT_DATA_CONVERTER(ConverterType) \
  bool ConverterType::m_registered = Celeste::ComponentDataConverterRegistry::addConverter<ConverterType>(); \
  \
  void ConverterType::doSetValues(Celeste::Component& component) const \
  { \
    Celeste::ComponentDataConverter::doSetValues(component); \
    doSetValues(reinterpret_cast<typename ConverterType::ComponentType&>(component)); \
  }