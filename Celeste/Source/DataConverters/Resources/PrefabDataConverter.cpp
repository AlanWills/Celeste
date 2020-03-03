#include "DataConverters/Resources/PrefabDataConverter.h"
#include "Resources/ResourceUtils.h"
#include "Resources/ResourceManager.h"
#include "Resources/Data/Prefab.h"


namespace Celeste
{
  //------------------------------------------------------------------------------------------------
  const char* const PrefabDataConverter::PATH_ATTRIBUTE_NAME("path");

  //------------------------------------------------------------------------------------------------
  PrefabDataConverter::PrefabDataConverter(const std::string& elementName) :
    Inherited(elementName),
    m_path(createReferenceAttribute<Path>(PATH_ATTRIBUTE_NAME, "", DeserializationRequirement::kRequired)),
    m_prefab()
  {
  }

  //------------------------------------------------------------------------------------------------
  observer_ptr<GameObject> PrefabDataConverter::allocateGameObject() const
  {
#if _DEBUG
    if (m_prefab == nullptr)
    {
      ASSERT_FAIL();
      return nullptr;
    }
#endif

    // Can add overloading of name, tag, position here if we want to
    return getPrefab()->instantiate();
  }

  //------------------------------------------------------------------------------------------------
  bool PrefabDataConverter::doConvertFromXML(const tinyxml2::XMLElement* prefabElement)
  {
    Inherited::doConvertFromXML(prefabElement);

    m_prefab = Resources::getResourceManager().load<Resources::Prefab>(getPath());
    ASSERT(m_prefab != nullptr);

    return m_prefab != nullptr;
  }
}