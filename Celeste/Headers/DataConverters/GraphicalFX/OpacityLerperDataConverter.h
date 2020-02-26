#pragma once

#include "DataConverters/Objects/ComponentDataConverter.h"
#include "XML/Attributes/DataAttribute.h"


namespace Celeste
{
  class OpacityLerper;

  class OpacityLerperDataConverter : public ComponentDataConverter
  {
    DECLARE_COMPONENT_DATA_CONVERTER(OpacityLerperDataConverter, OpacityLerper, CelesteDllExport)

    public:
      inline float getMaxOpacity() const { return m_maxOpacity.getValue(); }
      inline float getMinOpacity() const { return m_minOpacity.getValue(); }
      inline float getLerpUpTime() const { return m_lerpUpTime.getValue(); }
      inline float getLerpDownTime() const { return m_lerpDownTime.getValue(); }
      inline float getMaxOpacityWaitTime() const { return m_maxOpacityWaitTime.getValue(); }
      inline float getMinOpacityWaitTime() const { return m_minOpacityWaitTime.getValue(); }
      inline bool getLerpingUp() const { return m_lerpingUp.getValue(); }

      CelesteDllExport static const char* const MAX_OPACITY_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const MIN_OPACITY_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const LERP_UP_TIME_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const LERP_DOWN_TIME_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const MAX_OPACITY_WAIT_TIME_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const MIN_OPACITY_WAIT_TIME_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const LERPING_UP_ATTRIBUTE_NAME;
    
    private:
      using Inherited = ComponentDataConverter;

      XML::ValueAttribute<float>& m_maxOpacity;
      XML::ValueAttribute<float>& m_minOpacity;
      XML::ValueAttribute<float>& m_lerpUpTime;
      XML::ValueAttribute<float>& m_lerpDownTime;
      XML::ValueAttribute<float>& m_maxOpacityWaitTime;
      XML::ValueAttribute<float>& m_minOpacityWaitTime;
      XML::ValueAttribute<bool>& m_lerpingUp;
  };
}