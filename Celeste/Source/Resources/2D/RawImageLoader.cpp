#include "SOIL2/SOIL2.h"
#include "Resources/2D/RawImageLoader.h"
#include "Assert/Assert.h"


namespace Celeste::Resources
{
  //------------------------------------------------------------------------------------------------
  RawImageLoader::RawImageLoader(const std::string& fullPathToImageFile) :
    m_data(nullptr),
    m_width(0),
    m_height(0)
  {
    m_data = SOIL_load_image(fullPathToImageFile.c_str(), &m_width, &m_height, 0, SOIL_LOAD_RGBA);
    ASSERT(m_data);
  }

  //------------------------------------------------------------------------------------------------
  RawImageLoader::~RawImageLoader()
  {
    SOIL_free_image_data(m_data);
  }
}