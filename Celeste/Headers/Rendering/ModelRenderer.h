#pragma once

#include "Objects/Script.h"
#include "Resources/3D/Model.h"


namespace Celeste::Rendering
{
  class ModelRenderer : public Script
  {
    DECLARE_UNMANAGED_COMPONENT(ModelRenderer, CelesteDllExport)

    public:
      CelesteDllExport void render(const Resources::Program& shaderProgram) const;

      CelesteDllExport void setModel(const Path& modelRelativePath);
      inline void setModel(observer_ptr<Resources::Model> model) { m_model = model; }
      inline observer_ptr<Resources::Model> getModel() const { return m_model; }

    private:
      using Inherited = Script;

      observer_ptr<Resources::Model> m_model;
  };
}