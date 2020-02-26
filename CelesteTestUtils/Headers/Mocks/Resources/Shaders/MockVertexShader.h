#pragma once

#include "Resources/Shaders/VertexShader.h"


namespace CelesteTestUtils
{

class MockVertexShader : public Celeste::Resources::VertexShader
{
  public:
    ~MockVertexShader()
    {
      if (glIsShader)
      {
        glDeleteShader(getShaderHandle_Public());
      }
    }

    GLuint getShaderHandle_Public() const { return getShaderHandle(); }
};

}