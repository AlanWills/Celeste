#include "Resources/Data/Data.h"
#include "XML/tinyxml2_ext.h"

using namespace tinyxml2;
using namespace Celeste::XML;


namespace Celeste
{
  namespace Resources
  {
    //------------------------------------------------------------------------------------------------
    Data::Data() :
      m_document()
    {
    }

    //------------------------------------------------------------------------------------------------
    bool Data::hasElement(const std::string& elementName) const
    {
      return hasChildElement(m_document.RootElement(), elementName);
    }
  }
}