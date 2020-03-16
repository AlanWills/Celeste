#pragma once

#include "CelesteDllExport.h"
#include "Resources/Resource.h"

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Celeste
{
  namespace Resources
  {
    // General purpose shader object. Compiles from file, generates
    // compile/link-time error messages and hosts several utility 
    // functions for easy management.
    class Shader : public Resource
    {
      public:
        CelesteDllExport Shader();
        CelesteDllExport ~Shader();

        void loadFromCode(const std::string& shaderCode) { m_shaderSource = shaderCode; }

        /// Creates the shader from the loaded source code and returns a handle to the newly created shader
        /// The calling code should be responsible for deleting this.
        CelesteDllExport GLuint create();

      protected:
        /// Loads the shader code from the inputted shader file
        bool doLoadFromFile(const Path& shaderFilePath) override
        {
          // Retrieve the shader source code from filePath
          File(shaderFilePath).read(m_shaderSource);
          return !m_shaderSource.empty();
        }

        /// Performs cleaning up of the gl shader if necessary
        CelesteDllExport void doUnload() override;

        CelesteDllExport virtual GLenum getShaderType() const = 0;
        CelesteDllExport virtual const GLchar* getShaderTypeString() const = 0;

        GLuint getShaderHandle() const { return m_shader; }
        const std::string& getShaderSource() const { return m_shaderSource; }

      private:
        typedef Resource Inherited;

        bool checkCompileErrors();

        std::string m_shaderSource;

        // The shader handle
        GLuint m_shader;
    };
  }
}