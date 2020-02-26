#pragma once

#include "Shader.h"


namespace Celeste
{
  namespace Resources
  {
    class VertexShader : public Shader
    {
      protected:
        GLenum getShaderType() const override { return GL_VERTEX_SHADER; }
        const GLchar* getShaderTypeString() const override { return "VERTEX"; }
    };
  }
}