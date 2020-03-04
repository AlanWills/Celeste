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
    DECLARE_MANAGED_COMPONENT_DATA_CONVERTER(ButtonDataConverter, UI::Button, CelesteDllExport)

    public:
      using CallbackDataConverters = typename XML::DataConverterListElement<CallbackDataConverter>::Items;

      inline const Path& getDefaultTexturePath() const { return m_defaultTexturePath.getValue(); }
      inline const Path& getHighlightedTexturePath() const { return m_highlightedTexturePath.getValue(); }
      inline const Path& getClickedTexturePath() const { return m_clickedTexturePath.getValue(); }
      inline const Path& getHighlightedSoundPath() const { return m_highlightedSoundPath.getValue(); }
      inline const Path& getClickedSoundPath() const { return m_clickedSoundPath.getValue(); }

      inline CelesteDllExport static const Path& getDefaultTextureDefaultPath() { return m_defaultTextureDefaultPath; }
      inline CelesteDllExport static void setDefaultTextureDefaultPath(const Path& path) { m_defaultTextureDefaultPath = path; }

      inline CelesteDllExport static const Path& getHighlightedTextureDefaultPath() { return m_highlightedTextureDefaultPath; }
      inline CelesteDllExport static void setHighlightedTextureDefaultPath(const Path& path) { m_highlightedTextureDefaultPath = path; }

      inline CelesteDllExport static const Path& getClickedTextureDefaultPath() { return m_clickedTextureDefaultPath; }
      inline CelesteDllExport static void setClickedTextureDefaultPath(const Path& path) { m_clickedTextureDefaultPath = path; }

      inline CelesteDllExport static const Path& getHighlightedSoundDefaultPath() { return m_highlightedSoundDefaultPath; }
      inline CelesteDllExport static void setHighlightedSoundDefaultPath(const Path& path) { m_highlightedSoundDefaultPath = path; }

      inline CelesteDllExport static const Path& getClickedSoundDefaultPath() { return m_clickedSoundDefaultPath; }
      inline CelesteDllExport static void setClickedSoundDefaultPath(const Path& path) { m_clickedSoundDefaultPath = path; }

      CelesteDllExport static const char* const DEFAULT_TEXTURE_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const HIGHLIGHTED_TEXTURE_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const CLICKED_TEXTURE_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const HIGHLIGHTED_SOUND_ATTRIBUTE_NAME;
      CelesteDllExport static const char* const CLICKED_SOUND_ATTRIBUTE_NAME;

    private:
      using Inherited = ComponentDataConverter;

      XML::ReferenceAttribute<Path>& m_defaultTexturePath;
      XML::ReferenceAttribute<Path>& m_highlightedTexturePath;
      XML::ReferenceAttribute<Path>& m_clickedTexturePath;
      XML::ReferenceAttribute<Path>& m_highlightedSoundPath;
      XML::ReferenceAttribute<Path>& m_clickedSoundPath;

      static Path m_defaultTextureDefaultPath;
      static Path m_highlightedTextureDefaultPath;
      static Path m_clickedTextureDefaultPath;
      static Path m_highlightedSoundDefaultPath;
      static Path m_clickedSoundDefaultPath;
  };
}