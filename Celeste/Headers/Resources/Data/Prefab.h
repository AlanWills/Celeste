#pragma once

#include "Resources/Resource.h"
#include "XML/Elements/DataConverterListElement.h"
#include "DataConverters/Objects/GameObjectDataConverter.h"


namespace Celeste
{
  class GameObject;
}

namespace Celeste::Resources
{
  class Prefab : public Resource
  {
    private:
      using GameObjectList = XML::DataConverterListElement<GameObjectDataConverter>;
      using GameObjectDataConverters = typename GameObjectList::Items;

    public:
      CelesteDllExport Prefab();
      Prefab(const Prefab&) = delete;
      Prefab(Prefab&&) = default;
      ~Prefab() = default;

      Prefab& operator=(const Prefab&) = delete;

      inline const GameObjectDataConverters& getGameObjects() const { return m_gameObjects->getItems(); }
      CelesteDllExport observer_ptr<GameObject> instantiate() const;

    protected:
      CelesteDllExport bool doLoadFromFile(const Path& path) override;
      CelesteDllExport void doUnload() override;

    private:
      using Inherited = Resource;

      std::unique_ptr<GameObjectList> m_gameObjects;
  };
}