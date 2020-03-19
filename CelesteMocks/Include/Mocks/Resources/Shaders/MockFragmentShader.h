#pragma once

#include "Resources/Shaders/FragmentShader.h"


namespace CelesteTestUtils
{

class MockFragmentShader : public Celeste::Resources::FragmentShader
{
public:
  ~MockFragmentShader()
  {
    if (glIsShader)
    {
      glDeleteShader(getShaderHandle_Public());
    }
  }

  GLuint getShaderHandle_Public() const { return getShaderHandle(); }
};

}