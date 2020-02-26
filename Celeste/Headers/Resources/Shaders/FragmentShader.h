#pragma once

#include "Shader.h"


namespace Celeste
{
  namespace Resources
  {
    class FragmentShader : public Shader
    {
      protected:
        GLenum getShaderType() const override { return GL_FRAGMENT_SHADER; }
        const GLchar* getShaderTypeString() const override { return "FRAGMENT"; }
    };
  }
}