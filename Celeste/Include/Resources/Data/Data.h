#pragma once

#include "FileSystem/File.h"
#include "Resources/Resource.h"
#include "XML/tinyxml2_ext.h"
#include "Assert/Assert.h"
#include "UID/StringId.h"


namespace Celeste
{
  namespace Resources
  {
    class Data : public Resource
    {
      public:
        CelesteDllExport Data();

        // XMLDocument does not support copying, so neither can this
        Data(const Data& data) = delete;

        bool getDocumentError() const { return m_document.Error(); }

        tinyxml2::XMLDocument& getDocument() { return m_document; }
        const tinyxml2::XMLDocument& getDocument() const { return m_document; }

        XMLElement* getDocumentRoot() { return m_document.RootElement(); }
        const XMLElement* getDocumentRoot() const { return m_document.RootElement(); }

        bool saveToFile(const Path& fullFilePath) { return getDocument().SaveFile(fullFilePath.c_str()) == XML_SUCCESS; }

        /// Use the resource ID to save to the same file path it was loaded from
        bool overwriteFile() { return getResourceId() == static_cast<StringId>(0) ? false : saveToFile(deinternString(getResourceId())); }

        CelesteDllExport bool hasElement(const std::string& elementName) const;

        //------------------------------------------------------------------------------------------------
        template <typename T>
        XML::XMLValueError getElementData(const std::string& elementName, T& output) const
        {
          return XML::getChildElementData<T>(m_document.RootElement(), elementName, output);
        }

        //------------------------------------------------------------------------------------------------
        template <typename T>
        XML::XMLValueError getElementDataAsVector(const std::string& elementName, const std::string& itemElementName, std::vector<T>& output) const
        {
          return XML::getChildElementDataAsVector<T>(m_document.RootElement(), elementName, itemElementName, output);
        }

      protected:
        bool doLoadFromFile(const Path& fullFilePath) override
        {
          return m_document.LoadFile(fullFilePath.as_string().c_str()) == XML_SUCCESS;
        }

        void doUnload() override { }

      private:
        typedef Resource Inherited;

        tinyxml2::XMLDocument m_document;
    };
  }
}