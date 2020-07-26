#include "Objects/ScriptableObject.h"
#include "Resources/ResourceManager.h"
#include "XML/tinyxml2_ext.h"
#include "Registries/ScriptableObjectRegistry.h"
#include "crossguid/guid.hpp"


namespace Celeste
{
  using namespace Resources;

  //------------------------------------------------------------------------------------------------
  ScriptableObject::ScriptableObject() :
    m_fields(),
    m_scriptableObjects(),
    m_name(),
    m_guid(xg::newGuid())
  {
  }

  //------------------------------------------------------------------------------------------------
  ScriptableObject::~ScriptableObject() = default;

  //------------------------------------------------------------------------------------------------
  bool ScriptableObject::deserialize(const tinyxml2::XMLElement* element)
  {
    ASSERT(element);
    if (element == nullptr)
    {
      ASSERT_FAIL();
      return false;
    }

    // Read and load name
    const char* name = element->Attribute("name");
    m_name.assign(name != nullptr ? name : "");

    // Read and load guid
    const char* guid = element->Attribute("guid");
    m_guid = guid != nullptr ? xg::Guid(guid) : xg::newGuid();

    if (!m_guid.isValid())
    {
      ASSERT_FAIL_MSG("Invalid or missing guid.  This will cause object references to not be set up correctly.");
      m_guid = xg::newGuid();
    }

    // Now deserialize all the field information
    for (const auto& field : m_fields)
    {
      if (!field->deserialize(element))
      {
        ASSERT_FAIL();
        return false;
      }
    }

    ElementLookup elementLookup;
    auto childrenWalker = XML::children(element);
    auto childrenIt = childrenWalker.begin();
    auto childrenEnd = childrenWalker.end();

    // We go through all the child xml elements which represent any other scriptable objects owned by this
    // scriptable object.  We can match up their guid with any guid references found.
    for (; childrenIt != childrenEnd; ++childrenIt)
    {
      const tinyxml2::XMLElement* childElement = *childrenIt;
      const char* childGuid = childElement->Attribute("guid");
      if (childGuid != nullptr)
      {
        elementLookup.emplace(ElementInformation(childGuid), childElement);
      }
    }

    // We will now go through and deserialize each scriptable object
    // The scriptable object is either a reference, in which case it's value will be in the elements lookup
    // or it is a path to another scriptable object asset, in which it's value won't be in the elements lookup.
    // Instead we can set it's value by loading in the appropriate scriptable object asset.

    for (EmbeddedScriptableObject& embeddedScriptableObject : m_scriptableObjects)
    {
      std::unique_ptr<ScriptableObject>& scriptableObject = std::get<0>(embeddedScriptableObject);

      const char* scriptableObjectValue = element->Attribute(scriptableObject->getName().c_str());
      if (scriptableObjectValue != nullptr)
      {
        // We have a value set for this scriptable object, so we check to see whether it is a reference or embedded within this scriptable object
        if (elementLookup.find(scriptableObjectValue) != elementLookup.end())
        {
          // We have an embedded scriptable object, so we can actually deserialize it now using the corresponding scriptable object element

          // Now find the element info in the lookup which will give us the scriptable object's proper element containing it's data
          ElementLookup::const_iterator elementInfo = std::find_if(elementLookup.begin(), elementLookup.end(), [scriptableObjectValue](const std::pair<ElementInformation, const XMLElement*>& info) -> bool
            {
              return info.first == scriptableObjectValue;
            });

          if (elementInfo == elementLookup.end())
          {
            ASSERT_FAIL();
            return false;
          }

          // Now load the data onto the scriptable object at the same index as this information element
          if (!scriptableObject->deserialize((*elementInfo).second))
          {
            ASSERT_FAIL();
            return false;
          }
        }
        else
        {
          // We have a scriptable object loadable from the resources so we load it's value into the scriptable object
          observer_ptr<Data> data = getResourceManager().load<Data>(scriptableObjectValue);
          if (data == nullptr)
          {
            ASSERT_FAIL();
            return false;
          }

          if (!scriptableObject->deserialize(data->getDocumentRoot()))
          {
            ASSERT_FAIL();
            return false;
          }

          std::get<1>(embeddedScriptableObject) = scriptableObjectValue;
        }

        // Store the scriptable object value
        // So when serializing we know it's a scriptable object which requires a link to a field/separate file
        // rather than an SO managed manually by a derived class or added at runtime
        std::get<1>(embeddedScriptableObject) = scriptableObjectValue;
      }
    }

    return doDeserialize(element);
  }

  //------------------------------------------------------------------------------------------------
  std::unique_ptr<ScriptableObject> ScriptableObject::create(const std::string& typeName, const std::string& name)
  {
    return std::move(ScriptableObjectRegistry::createScriptableObject(typeName, name));
  }

  //------------------------------------------------------------------------------------------------
  std::unique_ptr<ScriptableObject> ScriptableObject::load(const Path& pathToFile)
  {
    return std::move(ScriptableObjectRegistry::loadScriptableObject(pathToFile));
  }

  //------------------------------------------------------------------------------------------------
  void ScriptableObject::save(const Path& pathToFile) const
  {
    if (pathToFile.as_string().empty())
    {
      ASSERT_FAIL();
      return;
    }

    observer_ptr<Data> data = getResourceManager().load<Data>(pathToFile);
    if (data == nullptr)
    {
      data = getResourceManager().create(pathToFile);
      if (data == nullptr)
      {
        ASSERT_FAIL();
        return;
      }
    }

    XMLDocument& document = data->getDocument();
    document.Clear();

    tinyxml2::XMLElement* objectElement = document.NewElement(getTypeName().c_str());
    document.InsertFirstChild(objectElement);
    
    // Having created all the necessary elements, we now recursively serialize the object tree
    serialize(objectElement);
    
    document.InsertFirstChild(document.NewDeclaration());

    // Now, save the data again
    bool result = data->saveToFile(pathToFile);
    ASSERT(result);
    celstl::unused(result);
  }

  //------------------------------------------------------------------------------------------------
  void ScriptableObject::serialize(tinyxml2::XMLElement* element) const
  {
    ASSERT(element);
    if (element != nullptr)
    {
      // Check name of element is set up correctly
      ASSERT(getTypeName() == element->Name());

      // Now serialize the guid and internal name of the object
      element->SetAttribute("name", m_name.c_str());
      element->SetAttribute("guid", m_guid.str().c_str());

      // Then serialize all fields onto the element too
      for (const auto& field : m_fields)
      {
        field->serialize(element);
      }

      for (const EmbeddedScriptableObject& embeddedScriptableObject : m_scriptableObjects)
      {
        // ERROR - COULD HAVE RECURSIVE LOOP
        // NEED TO COLLECT ALL THE OBJECTS BY PASSING A DICTIONARY OR SOMETHING TO GET A LIST OF ALL CHILDREN THAT NEED SERIALIZING

        const std::unique_ptr<ScriptableObject>& scriptableObject = std::get<0>(embeddedScriptableObject);
        const std::string& embeddedLink = std::get<1>(embeddedScriptableObject);

        if (!embeddedLink.empty())
        {          
          // We have an SO that is referenced by an attribute so we need to link it here
          // This is either a path to a separate file, or a guid to a child SO in this file
          element->SetAttribute(scriptableObject->getName().c_str(), embeddedLink.c_str());
        }

        if (embeddedLink.empty() || xg::Guid(embeddedLink).isValid())
        {
          // Need to save the SO in this file
          // Create an actual element for the child object underneath the childrenElement
          tinyxml2::XMLElement* childElement = element->GetDocument()->NewElement(scriptableObject->getTypeName().c_str());
          element->InsertEndChild(childElement);
          scriptableObject->serialize(childElement);
        }
        else
        {
          // Need to save the SO in the file it came from
          scriptableObject->save(embeddedLink);
        }
      }
    }

    doSerialize(element);
  }

  //------------------------------------------------------------------------------------------------
  ScriptableObject& ScriptableObject::deserializeScriptableObject(const tinyxml2::XMLElement* element)
  {
    ASSERT(ScriptableObjectRegistry::hasScriptableObject(element->Name()));
    std::unique_ptr<ScriptableObject> scriptableObject = ScriptableObjectRegistry::createScriptableObject(element->Name(), "");

    if (!scriptableObject->deserialize(element))
    {
      ASSERT_FAIL();
    }

    return addScriptableObject(std::move(scriptableObject));
  }

  //------------------------------------------------------------------------------------------------
  void ScriptableObject::removeScriptableObject(const ScriptableObject& scriptableObject)
  {
    for (size_t i = m_scriptableObjects.size(); i > 0; --i)
    {
      if (std::get<0>(m_scriptableObjects[i - 1]).get() == &scriptableObject)
      {
        m_scriptableObjects.erase(m_scriptableObjects.begin() + i - 1);
        return;
      }
    }

    ASSERT_FAIL();
  }

  //------------------------------------------------------------------------------------------------
  void ScriptableObject::removeScriptableObject(size_t removeIndex)
  {
    ASSERT(removeIndex < m_scriptableObjects.size());
    if (removeIndex < m_scriptableObjects.size())
    {
      m_scriptableObjects.erase(m_scriptableObjects.begin() + removeIndex);
    }
  }
}