#pragma once

#include "Objects/Script.h"
#include "UID/StringId.h"


namespace Celeste::Rendering
{
  class TextRenderer;
}

namespace Celeste::UI
{
  class TextBox : public Script
  {
    DECLARE_SCRIPT(TextBox, CelesteDllExport)

    public:
      CelesteDllExport ~TextBox() override;

      size_t getLineIndex() const { return m_lineIndex; }
      size_t getLetterIndex() const { return m_letterIndex; }

      CelesteDllExport void setLineIndex(size_t lineIndex);
      CelesteDllExport void setLetterIndex(size_t letterIndex);

    protected:
      CelesteDllExport void onSetGameObject(GameObject& gameObject) override;

      StringId getTextInputtedEventHandle() const { return m_textInputtedEventHandle; }
      StringId getKeyPressedEventHandle() const { return m_keyPressedEventHandle; }

    private:
      using Inherited = Script;

      void onTextInputtedCallback(char character);
      void onKeyPressedCallback(int keyPressed);

      observer_ptr<Rendering::TextRenderer> m_textRenderer;
      StringId m_textInputtedEventHandle;
      StringId m_keyPressedEventHandle;

      size_t m_lineIndex;
      size_t m_letterIndex;
  };
}