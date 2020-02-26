#pragma once

#include "CelesteDllExport.h" 

#include <string>


namespace Celeste 
{
  namespace adl_helper 
  {
    using std::to_string;

    template<class T>
    std::string as_string(T t) 
    {
      return to_string(t);
    }
  }

  //------------------------------------------------------------------------------------------------
  template<class T>
  std::string to_string(T t) 
  {
    return adl_helper::as_string(t);
  }
}