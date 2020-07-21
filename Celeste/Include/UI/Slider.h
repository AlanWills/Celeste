#pragma once

#include "Objects/Component.h"
#include "Events/Event.h"


namespace Celeste::UI
{
  class Slider : public Component
  {
    DECLARE_UNMANAGED_COMPONENT(Slider, CelesteDllExport)

  public:
    using ValueChangedEvent = Event<GameObject&, float>;

    inline float getMin() const { return m_min; }
    inline void setMin(float min) { m_min = min; }

    inline float getMax() const { return m_max; }
    inline void setMax(float max) { m_max = max; }

    inline float getCurrentValue() const { return m_currentValue; }
    CelesteDllExport void setCurrentValue(float currentValue);

    inline ValueChangedEvent& getValueChangedEvent() { return m_valueChanged; }

    template <typename ...Callbacks>
    void subscribeValueChangedCallback(const Event<GameObject&, float>::Function& callback, const Callbacks&... callbacks);
    inline CelesteDllExport void subscribeValueChangedCallback(const Event<GameObject&, float>::Function& callback)
    {
      m_valueChanged.subscribe(callback);
    }

    CelesteDllExport void update() override;

  private:
    using Inherited = Component;

    Transform* getHandle();

    bool m_sliderClicked;
    float m_min;
    float m_max;
    float m_currentValue;

    ValueChangedEvent m_valueChanged;
  };

  //------------------------------------------------------------------------------------------------
  template <typename ...Callbacks>
  void Slider::subscribeValueChangedCallback(
    const Event<GameObject&, float>::Function& callback,
    const Callbacks&... callbacks)
  {
    subscribeValueChangedCallback(callback);
    subscribeValueChangedCallback(callbacks...);
  }
}