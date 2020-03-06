#pragma once

#include "UID/StringId.h"
#include "FileSystem/Directory.h"
#include "Memory/Allocators/PoolAllocator.h"
#include "Memory/ObserverPtr.h"

#include <vector>
#include <memory>
#include <unordered_map>


namespace Celeste::Resources
{
  template <typename T>
  class ResourceLoader
  {
    public:
      ResourceLoader(size_t length) : ResourceLoader(length, "") { }
      ResourceLoader(size_t length, const Path& resourceDirectoryPath);

      bool isResourceLoaded(const Path& relativeOrFullPath) const;

      /// Returns a handle to the inputted resource using the full path or relative path from this loader's resource directory.
      /// Will load the resource if it has not already been loaded.
      observer_ptr<T> loadResource(const Path& relativeOrFullPath);

      /// Unloads the inputted resource from this loader using either the full path or path relative to this loader's resource directory.
      /// Can also pass a handle to the resource to unload, which will become a nullptr handle after a successful call.
      /// Will do nothing if the resource has not been loaded.
      void unloadResource(T& resource);
      void unloadResource(const Path& relativeOrFullPath);

      void loadAllResources(const std::string& fileExtension);
      void unloadAllResources();

      inline const Path& getResourceDirectoryPath() const { return m_resourceDirectory.getDirectoryPath(); }
      inline void setResourceDirectoryPath(const Path& path) { m_resourceDirectory = Directory(path); }

      /// The number of elements in the map
      inline size_t size() const { return m_map.size(); }

    protected:
      using Map = std::unordered_map<StringId, observer_ptr<T>>;
      using Pool = PoolAllocator<T>;

      Map m_map;
      Pool m_pool;

    private:
      observer_ptr<T> loadResourceFromFile(const File& fullFilePath);

      Directory m_resourceDirectory;
  };

  //------------------------------------------------------------------------------------------------
  template <typename T>
  ResourceLoader<T>::ResourceLoader(size_t length, const Path& resourceDirectoryFullPath) :
    m_resourceDirectory(resourceDirectoryFullPath),
    m_pool(length)
  {
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  bool ResourceLoader<T>::isResourceLoaded(const Path& relativeOrFullPath) const
  {
    // Check relative path first
    StringId name = internString(relativeOrFullPath.as_string());
    if (m_map.find(name) != m_map.end())
    {
      return true;
    }

    // Then attempt to check the full path too
    name = internString(Path(m_resourceDirectory.getDirectoryPath().as_string(), relativeOrFullPath).as_string());
    return m_map.find(name) != m_map.end();
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  observer_ptr<T> ResourceLoader<T>::loadResource(const Path& relativeOrFullPath)
  {
    File file(relativeOrFullPath);
    if (!file.exists())
    {
      // If the file did not exist it must be relative, so we make it a full path
      file = File(Path(m_resourceDirectory.getDirectoryPath().as_string(), relativeOrFullPath));
      if (!file.exists())
      {
        // If the file still does not exist, we return null handle
        return observer_ptr<T>();
      }
    }

    StringId name = internString(file.getFilePath().as_string());
    if (m_map.find(name) != m_map.end())
    {
      // If the name already exists in our dictionary just return it rather than loading it
      return m_map[name];
    }

    // Load the resource from the file and add it to the map
    observer_ptr<T> resource = loadResourceFromFile(file);
    if (resource != nullptr)
    {
      m_map[name] = resource;
    }

    return resource;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  T* ResourceLoader<T>::loadResourceFromFile(const File& fullPath)
  {
    // Create handle object
    if (!m_pool.canAllocate(1))
    {
      ASSERT_FAIL_MSG("Resource Loader pool allocator out of memory.  Consider increasing the size.");
      return nullptr;
    }

    // If we have room left in the pool we just allocate a new entry
    T* item = new (m_pool.allocate()) T();
    ASSERT_NOT_NULL(item);

    // Pass the full file path into the load function so resources can also obtain the file they are being loaded from
    if (!item->loadFromFile(fullPath.getFilePath()))
    {
      item->unload();
      m_pool.deallocate(*item);
      item = nullptr;
    }

    return item;
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void ResourceLoader<T>::unloadResource(T& resource)
  {
    StringId resourceId = resource.getResourceId();

    if (m_map.find(resourceId) == m_map.end())
    {
      ASSERT_FAIL_MSG("Resource not in map or resource Id not set.");
      return;
    }

    // Unload and then deallocate the inputted resource
    resource.unload();
    m_pool.deallocate(resource);

    // Finally, erase from map
    m_map.erase(resourceId);
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void ResourceLoader<T>::unloadResource(const Path& relativeOrFullPath)
  {
    StringId name = internString(relativeOrFullPath.as_string());
    if (m_map.find(name) == m_map.end())
    {
      name = internString(Path(m_resourceDirectory.getDirectoryPath(), relativeOrFullPath).as_string());
      if (m_map.find(name) == m_map.end())
      {
        ASSERT_FAIL_MSG("Resource not in map.  Consider using the unloadResource overload which takes a handle to the resource");
        return;
      }
    }

    unloadResource(*m_map[name]);
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void ResourceLoader<T>::loadAllResources(const std::string& fileExtension)
  {
    if (m_resourceDirectory.exists())
    {
      // Load all resource files
      std::vector<File> files;
      m_resourceDirectory.findFiles(files, fileExtension, true);

      for (const File& file : files)
      {
        loadResource(file.getFilePath().relativeTo(m_resourceDirectory.getDirectoryPath()));
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  template <typename T>
  void ResourceLoader<T>::unloadAllResources()
  {
    for (T& resource : m_pool)
    {
      // Guaranteed non-null by iterator
      if (resource.getResourceId() == (StringId)0)
      {
        // Only iterate over resources that are loaded
        continue;
      }

      // Find the handle for the resource
      auto it = m_map.find(resource.getResourceId());
      if (it == m_map.end())
      {
        ASSERT_FAIL_MSG("Resource not in map or resource Id not set.");
        return;
      }

      // Unload using the handle
      // Takes care of deallocation too
      unloadResource(resource);
    }

    m_map.clear();
  }
}