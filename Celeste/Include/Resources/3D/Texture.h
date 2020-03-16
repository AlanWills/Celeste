#pragma once

#include <string>


namespace Celeste
{
  namespace Resources
  {
    struct Texture
    {
      unsigned int m_id;
      std::string m_type;
      std::string m_path;
    };
  }
}