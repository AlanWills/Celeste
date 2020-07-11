#pragma once

#include "DataConverters/Objects/ComponentDataConverter.h"
#include "Input/Key.h"
#include "Deserialization/InputDeserializers.h"


namespace Celeste::Input
{
  class KeyboardTransformer;
}

namespace Celeste
{
  class KeyboardTransformerDataConverter : public ComponentDataConverter
  {
    DECLARE_COMPONENT_DATA_CONVERTER(KeyboardTransformerDataConverter, Input::KeyboardTransformer, CelesteDllExport)

    public:
      inline int getTranslateLeftKey() const { return m_translateLeftKey.getValue().m_key; }
      inline int getTranslateRightKey() const { return m_translateRightKey.getValue().m_key; }
      inline int getTranslateUpKey() const { return m_translateUpKey.getValue().m_key; }
      inline int getTranslateDownKey() const { return m_translateDownKey.getValue().m_key; }
      inline int getRotateLeftKey() const { return m_rotateLeftKey.getValue().m_key; }
      inline int getRotateRightKey() const { return m_rotateRightKey.getValue().m_key; }
      inline float getTranslationSpeed() const { return m_translationSpeed.getValue(); }
      inline float getRotationSpeed() const { return m_rotationSpeed.getValue(); }

      CelesteDllExport static const char* const TRANSLATE_LEFT_KEY_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const TRANSLATE_RIGHT_KEY_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const TRANSLATE_UP_KEY_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const TRANSLATE_DOWN_KEY_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const ROTATE_LEFT_KEY_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const ROTATE_RIGHT_KEY_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const TRANSLATION_SPEED_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const ROTATION_SPEED_ATTRIBUTE_NAME;

    private:
      using Inherited = ComponentDataConverter;

      XML::ValueAttribute<Input::Key>& m_translateLeftKey;
      XML::ValueAttribute<Input::Key>& m_translateRightKey;
      XML::ValueAttribute<Input::Key>& m_translateUpKey;
      XML::ValueAttribute<Input::Key>& m_translateDownKey;
      XML::ValueAttribute<Input::Key>& m_rotateLeftKey;
      XML::ValueAttribute<Input::Key>& m_rotateRightKey;

      XML::ValueAttribute<float>& m_translationSpeed;
      XML::ValueAttribute<float>& m_rotationSpeed;
  };
}