#pragma once

#include "Resources/Shaders/Shader.h"


namespace CelesteMocks
{

class MockShader : public Celeste::Resources::Shader
{
  public:
    GLenum getShaderType() const { return 0; }
    const GLchar* getShaderTypeString() const { return "MOCK"; }

    const std::string& getShaderSource_Public() const { return getShaderSource(); }
};

}