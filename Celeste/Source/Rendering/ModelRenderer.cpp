#include "Rendering/ModelRenderer.h"
#include "UtilityHeaders/ComponentHeaders.h"
#include "Resources/ResourceManager.h"

using namespace Celeste::Resources;


namespace Celeste::Rendering
{
  REGISTER_UNMANAGED_COMPONENT(ModelRenderer, 10)

  //------------------------------------------------------------------------------------------------
  ModelRenderer::ModelRenderer(GameObject& gameObject) :
    Inherited(gameObject),
    m_model(nullptr)
  {
  }

  //------------------------------------------------------------------------------------------------
  void ModelRenderer::setModel(const Path& relativePathToModel)
  {
    observer_ptr<Resources::Model> model = getResourceManager().load<Resources::Model>(relativePathToModel);
    if (model != nullptr)
    {
      setModel(model);
    }
  }

  //------------------------------------------------------------------------------------------------
  void ModelRenderer::render(const Resources::Program& program) const
  {
    if (m_model != nullptr)
    {
      for (const auto& mesh : m_model->getMeshes())
      {
        mesh.bind(program);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh.getIndices().size()), GL_UNSIGNED_INT, 0);
        mesh.unbind();
      }
    }
  }
}