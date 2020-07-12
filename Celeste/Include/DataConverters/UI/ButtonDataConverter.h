#pragma once

#include "DataConverters/Objects/ComponentDataConverter.h"
#include "DataConverters/Callbacks/CallbackDataConverter.h"
#include "XML/Attributes/DataAttribute.h"
#include "XML/Elements/DataConverterListElement.h"
#include "FileSystem/Path.h"


namespace Celeste::UI
{
  class Button;
}

namespace Celeste
{
  class ButtonDataConverter : public ComponentDataConverter
  {
    DECLARE_COMPONENT_DATA_CONVERTER(ButtonDataConverter, UI::Button, CelesteDllExport)

    public:
      using CallbackDataConverters = typename XML::DataConverterListElement<CallbackDataConverter>::Items;

      inline const Path& getIdleTexturePath() const { return m_idleTexturePath.getValue(); }
      inline const Path& getHighlightedTexturePath() const { return m_highlightedTexturePath.getValue(); }
      inline const Path& getClickedTexturePath() const { return m_clickedTexturePath.getValue(); }
      inline const Path& getHighlightedSoundPath() const { return m_highlightedSoundPath.getValue(); }
      inline const Path& getClickedSoundPath() const { return m_clickedSoundPath.getValue(); }

      CelesteDllExport static const char* const IDLE_TEXTURE_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const HIGHLIGHTED_TEXTURE_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const CLICKED_TEXTURE_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const HIGHLIGHTED_SOUND_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const CLICKED_SOUND_ATTRIBUTE_NAME;

    private:
      using Inherited = ComponentDataConverter;

      XML::ReferenceAttribute<Path>& m_idleTexturePath;
      XML::ReferenceAttribute<Path>& m_highlightedTexturePath;
      XML::ReferenceAttribute<Path>& m_clickedTexturePath;
      XML::ReferenceAttribute<Path>& m_highlightedSoundPath;
      XML::ReferenceAttribute<Path>& m_clickedSoundPath;
  };
}