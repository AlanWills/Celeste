#include "UI/TextBox.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Input/InputManager.h"
#include "Rendering/TextRenderer.h"

using namespace Celeste::Input;
using namespace Celeste::Rendering;


namespace Celeste::UI
{
  REGISTER_COMPONENT(TextBox, 10);

  //------------------------------------------------------------------------------------------------
  TextBox::TextBox() :
    m_textRenderer(),
    m_textInputtedEventHandle(0),
    m_keyPressedEventHandle(0),
    m_lineIndex(0),
    m_letterIndex(0)
  {
    m_textInputtedEventHandle = getKeyboard().getTextInputtedEvent().subscribe(
      [this](char character)
      {
        onTextInputtedCallback(character);
      });

    m_keyPressedEventHandle = getKeyboard().getKeyPressedEvent().subscribe(
      [this](int key)
      {
        onKeyPressedCallback(key);
      });
  }

  //------------------------------------------------------------------------------------------------
  TextBox::~TextBox()
  {
    getKeyboard().getTextInputtedEvent().unsubscribe(m_textInputtedEventHandle);
    getKeyboard().getKeyPressedEvent().unsubscribe(m_keyPressedEventHandle);
  }

  //------------------------------------------------------------------------------------------------
  void TextBox::onSetGameObject(GameObject& gameObject)
  {
    Inherited::onSetGameObject(gameObject);

    m_textRenderer = gameObject.findComponent<TextRenderer>();

    if (m_textRenderer == nullptr || gameObject.getScreen() == nullptr)
    {
      ASSERT_FAIL();
      return;
    }

    if (m_textRenderer->getLineCount() == 0)
    {
      // If our text renderer has no lines, add an empty one - this is a textbox after all!
      m_textRenderer->addLine();
    }

    setLineIndex(0);
    setLetterIndex(0);
  }

  //------------------------------------------------------------------------------------------------
  void TextBox::onTextInputtedCallback(char character)
  {
    if (isActive() && m_textRenderer != nullptr)
    {
      if (m_textRenderer->getLineCount() == 0)
      {
        m_textRenderer->addLine();
      }

      m_textRenderer->addLetter(m_lineIndex, m_letterIndex, character);
      setLetterIndex(m_letterIndex + 1);
    }
  }

  //------------------------------------------------------------------------------------------------
  void TextBox::onKeyPressedCallback(int keyPressed)
  {
    if (isActive() && m_textRenderer != nullptr)
    {
      switch (keyPressed)
      {
      case GLFW_KEY_ENTER:
      {
        std::string line;

        if (m_letterIndex < m_textRenderer->getLineLength(m_lineIndex))
        {
          // Separate current line
          m_textRenderer->getLine(m_lineIndex, line);
          m_textRenderer->setLine(m_lineIndex, line.substr(0, m_letterIndex));
          line.erase(line.begin(), line.begin() + m_letterIndex);
        }

        m_textRenderer->addLine(line);
        setLineIndex(m_lineIndex + 1);
        setLetterIndex(0);
        break;
      }

      case GLFW_KEY_BACKSPACE:
      {
        if (m_letterIndex > 0)
        {
          m_textRenderer->removeLetter(m_lineIndex, m_letterIndex - 1);
          setLetterIndex(m_letterIndex - 1);
        }
        else if (m_lineIndex > 0)
        {
          size_t letterIndex = m_textRenderer->getLineLength(m_lineIndex - 1);

          if (m_textRenderer->getLineLength(m_lineIndex) > 0)
          {
            std::string currentLine, previousLine;
            m_textRenderer->getLine(m_lineIndex, currentLine);
            m_textRenderer->getLine(m_lineIndex - 1, previousLine);
            m_textRenderer->setLine(m_lineIndex - 1, previousLine + currentLine);
          }

          m_textRenderer->removeLine(m_lineIndex);
          setLineIndex(m_lineIndex - 1);
          setLetterIndex(letterIndex);
        }
        break;
      }

      case GLFW_KEY_DELETE:
      {
        if (m_letterIndex < m_textRenderer->getLineLength(m_lineIndex))
        {
          m_textRenderer->removeLetter(m_lineIndex, m_letterIndex);
        }
        else if (m_lineIndex < (m_textRenderer->getLineCount() - 1))
        {
          if (m_textRenderer->getLineLength(m_lineIndex + 1) > 0)
          {
            std::string currentLine, nextLine;
            m_textRenderer->getLine(m_lineIndex, currentLine);
            m_textRenderer->getLine(m_lineIndex + 1, nextLine);
            m_textRenderer->setLine(m_lineIndex, currentLine + nextLine);
          }

          m_textRenderer->removeLine(m_lineIndex + 1);
        }
        break;
      }

      case GLFW_KEY_LEFT:
      {
        if (m_letterIndex > 0)
        {
          setLetterIndex(m_letterIndex - 1);
        }
        else if (m_lineIndex > 0)
        {
          setLineIndex(m_lineIndex - 1);
          setLetterIndex(m_textRenderer->getLineLength(m_lineIndex));
        }
        break;
      }

      case GLFW_KEY_UP:
      {
        if (m_lineIndex > 0)
        {
          setLineIndex(m_lineIndex - 1);
        }
        break;
      }

      case GLFW_KEY_RIGHT:
      {
        if (m_letterIndex < (m_textRenderer->getLineLength(m_lineIndex)))
        {
          setLetterIndex(m_letterIndex + 1);
        }
        else if (m_lineIndex < (m_textRenderer->getLineCount() - 1))
        {
          setLineIndex(m_lineIndex + 1);
          setLetterIndex(0);
        }
        break;
      }

      case GLFW_KEY_DOWN:
      {
        if (m_lineIndex < (m_textRenderer->getLineCount() - 1))
        {
          setLineIndex(m_lineIndex + 1);
        }
        break;
      }

      case GLFW_KEY_HOME:
      {
        setLetterIndex(0);
        break;
      }

      case GLFW_KEY_END:
      {
        setLetterIndex(m_textRenderer->getLineLength(m_lineIndex));
        break;
      }

      }
    }
  }

  //------------------------------------------------------------------------------------------------
  void TextBox::setLineIndex(size_t lineIndex)
  {
    if (m_textRenderer == nullptr || lineIndex >= m_textRenderer->getLineCount())
    {
      ASSERT_FAIL();
      return;
    }

    m_lineIndex = lineIndex;
    m_letterIndex = (std::min)(m_textRenderer->getLineLength(m_lineIndex), m_letterIndex);
  }

  //------------------------------------------------------------------------------------------------
  void TextBox::setLetterIndex(size_t letterIndex)
  {
    if (m_textRenderer == nullptr || letterIndex > m_textRenderer->getLineLength(m_lineIndex))
    {
      // Strict inequality because we can have the caret past the last letter of the line
      ASSERT_FAIL();
      return;
    }

    m_letterIndex = letterIndex;
  }
}