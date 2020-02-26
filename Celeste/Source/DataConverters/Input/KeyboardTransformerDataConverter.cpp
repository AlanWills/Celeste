#include "DataConverters/Input/KeyboardTransformerDataConverter.h"
#include "Registries/ComponentDataConverterRegistry.h"
#include "Input/KeyboardTransformer.h"


namespace Celeste
{
  REGISTER_COMPONENT_DATA_CONVERTER(KeyboardTransformerDataConverter)

  const char* const KeyboardTransformerDataConverter::TRANSLATE_LEFT_KEY_ATTRIBUTE_NAME("translate_left_key");
  const char* const KeyboardTransformerDataConverter::TRANSLATE_RIGHT_KEY_ATTRIBUTE_NAME("translate_right_key");
  const char* const KeyboardTransformerDataConverter::TRANSLATE_UP_KEY_ATTRIBUTE_NAME("translate_up_key");
  const char* const KeyboardTransformerDataConverter::TRANSLATE_DOWN_KEY_ATTRIBUTE_NAME("translate_down_key");
  const char* const KeyboardTransformerDataConverter::ROTATE_LEFT_KEY_ATTRIBUTE_NAME("rotate_left_key");
  const char* const KeyboardTransformerDataConverter::ROTATE_RIGHT_KEY_ATTRIBUTE_NAME("rotate_right_key");
  const char* const KeyboardTransformerDataConverter::TRANSLATION_SPEED_ATTRIBUTE_NAME("translation_speed");
  const char* const KeyboardTransformerDataConverter::ROTATION_SPEED_ATTRIBUTE_NAME("rotation_speed");

  //------------------------------------------------------------------------------------------------
  KeyboardTransformerDataConverter::KeyboardTransformerDataConverter() :
    Inherited(Input::KeyboardTransformer::type_name()),
    m_translateLeftKey(createValueAttribute<Input::Key>(TRANSLATE_LEFT_KEY_ATTRIBUTE_NAME)),
    m_translateRightKey(createValueAttribute<Input::Key>(TRANSLATE_RIGHT_KEY_ATTRIBUTE_NAME)),
    m_translateUpKey(createValueAttribute<Input::Key>(TRANSLATE_UP_KEY_ATTRIBUTE_NAME)),
    m_translateDownKey(createValueAttribute<Input::Key>(TRANSLATE_DOWN_KEY_ATTRIBUTE_NAME)),
    m_rotateLeftKey(createValueAttribute<Input::Key>(ROTATE_LEFT_KEY_ATTRIBUTE_NAME)),
    m_rotateRightKey(createValueAttribute<Input::Key>(ROTATE_RIGHT_KEY_ATTRIBUTE_NAME)),
    m_translationSpeed(createValueAttribute(TRANSLATION_SPEED_ATTRIBUTE_NAME, 1.0f)),
    m_rotationSpeed(createValueAttribute(ROTATION_SPEED_ATTRIBUTE_NAME, 0.01f))
  {
  }

  //------------------------------------------------------------------------------------------------
  void KeyboardTransformerDataConverter::doSetValues(Input::KeyboardTransformer& translator) const
  {
    translator.setTranslateLeftKey(getTranslateLeftKey());
    translator.setTranslateRightKey(getTranslateRightKey());
    translator.setTranslateUpKey(getTranslateUpKey());
    translator.setTranslateDownKey(getTranslateDownKey());
    translator.setRotateLeftKey(getRotateLeftKey());
    translator.setRotateRightKey(getRotateRightKey());
    translator.setTranslationSpeed(getTranslationSpeed());
    translator.setRotationSpeed(getRotationSpeed());
  }
}