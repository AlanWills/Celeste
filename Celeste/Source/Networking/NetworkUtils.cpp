#include "Networking/NetworkUtils.h"
#include "UtilityHeaders/NetworkHeaders.h"
#include "Debug/Assert.h"


namespace Celeste
{
  namespace Networking
  {
    //------------------------------------------------------------------------------------------------
    bool initialize()
    {
      // Initialize Winsock
      WSADATA wsaData;

      bool result = WSAStartup(MAKEWORD(2, 2), &wsaData) == 0;
      ASSERT(result == 0);
      return result;
    }

    //------------------------------------------------------------------------------------------------
    void exit()
    {
      WSACleanup();
    }
  }
}