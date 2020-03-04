#include "DataConverters/GraphicalFX/OpacityLerperDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "GraphicalFX/OpacityLerper.h"


namespace Celeste
{
  REGISTER_MANAGED_COMPONENT_DATA_CONVERTER(OpacityLerperDataConverter)

  const char* const OpacityLerperDataConverter::MAX_OPACITY_ATTRIBUTE_NAME("max");
  const char* const OpacityLerperDataConverter::MIN_OPACITY_ATTRIBUTE_NAME("min");
  const char* const OpacityLerperDataConverter::LERP_UP_TIME_ATTRIBUTE_NAME("lerp_up_time");
  const char* const OpacityLerperDataConverter::LERP_DOWN_TIME_ATTRIBUTE_NAME("lerp_down_time");
  const char* const OpacityLerperDataConverter::MAX_OPACITY_WAIT_TIME_ATTRIBUTE_NAME("max_wait_time");
  const char* const OpacityLerperDataConverter::MIN_OPACITY_WAIT_TIME_ATTRIBUTE_NAME("min_wait_time");
  const char* const OpacityLerperDataConverter::LERPING_UP_ATTRIBUTE_NAME("lerping_up");

  //------------------------------------------------------------------------------------------------
  OpacityLerperDataConverter::OpacityLerperDataConverter() :
    Inherited(OpacityLerper::type_name()),
    m_maxOpacity(createValueAttribute<float>(MAX_OPACITY_ATTRIBUTE_NAME, 1.0f)),
    m_minOpacity(createValueAttribute<float>(MIN_OPACITY_ATTRIBUTE_NAME, 0.0f)),
    m_lerpUpTime(createValueAttribute<float>(LERP_UP_TIME_ATTRIBUTE_NAME, 1.0f)),
    m_lerpDownTime(createValueAttribute<float>(LERP_DOWN_TIME_ATTRIBUTE_NAME, 1.0f)),
    m_maxOpacityWaitTime(createValueAttribute<float>(MAX_OPACITY_WAIT_TIME_ATTRIBUTE_NAME, 0.0f)),
    m_minOpacityWaitTime(createValueAttribute<float>(MIN_OPACITY_WAIT_TIME_ATTRIBUTE_NAME, 0.0f)),
    m_lerpingUp(createValueAttribute<bool>(LERPING_UP_ATTRIBUTE_NAME, true))
  {
  }

  //------------------------------------------------------------------------------------------------
  void OpacityLerperDataConverter::doSetValues(OpacityLerper& opacityLerper) const
  {
    opacityLerper.setMaxOpacity(getMaxOpacity());
    opacityLerper.setMinOpacity(getMinOpacity());
    opacityLerper.setLerpUpTime(getLerpUpTime());
    opacityLerper.setLerpDownTime(getLerpDownTime());
    opacityLerper.setMaxOpacityWaitTime(getMaxOpacityWaitTime());
    opacityLerper.setMinOpacityWaitTime(getMinOpacityWaitTime());
    opacityLerper.setLerpingUp(getLerpingUp());
  }
}