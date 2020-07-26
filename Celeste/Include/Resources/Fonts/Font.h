#pragma once

#include "CelesteDllExport.h"
#include "UtilityHeaders/GLHeaders.h"
#include "ft2build.h"
#include "Resources/Resource.h"
#include "FontInstance.h"
#include "Character.h"
#include FT_FREETYPE_H 

#include <unordered_map>


namespace Celeste::Resources
{
  class Font : public Resource
  {
    public:
      CelesteDllExport std::unique_ptr<FontInstance> createInstance(float height);

    protected:
      size_t getNumberOfHeightsLoaded() const { return m_charactersLookup.size(); }

      bool doLoadFromFile(const Path& /*pathToFile*/) override { return true; }
      CelesteDllExport void doUnload() override;

    private:
      using Characters = std::unordered_map<char, Character>;
      using CharactersLookup = std::unordered_map<float, Characters>;
      using Inherited = Resource;

      /// Load the characters, create textures for the inputted height and add to the characters lookup.
      /// If the characters already exist for the inputted height, do nothing.
      void loadCharacters(float height);

      CharactersLookup m_charactersLookup;
  };
}