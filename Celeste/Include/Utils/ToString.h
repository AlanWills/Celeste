#pragma once

#include "CelesteDllExport.h"
#include "Assert/Assert.h"

#include <string>

namespace Celeste 
{
  namespace adl_helper 
  {
    using std::to_string;

    template<class T>
    inline std::string as_string(T t) 
    {
      return to_string(t);
    }

    template<>
    inline std::string as_string(std::string t)
    {
      return t;
    }
  }

  //------------------------------------------------------------------------------------------------
  template<class T>
  inline std::string to_string(T t) 
  {
    return adl_helper::as_string(t);
  }

  //------------------------------------------------------------------------------------------------
  template<class T>
  bool from_string(const std::string& /*text*/, T& /*output*/)
  {
    STATIC_ASSERT_FAIL("Provide implementation of from_string for type");
    return false;
  }
}