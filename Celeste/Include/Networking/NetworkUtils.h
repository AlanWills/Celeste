#pragma once

#include "CelesteDllExport.h"

#include <string>


namespace Celeste::Networking
{
  CelesteDllExport void initialize();
  CelesteDllExport void sendRequest(const std::string& url, unsigned int port, const std::string& content);
  CelesteDllExport void exit();
}