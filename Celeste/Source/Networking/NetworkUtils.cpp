#include "Networking/NetworkUtils.h"
#include "UtilityHeaders/NetworkHeaders.h"
#include "Debug/Assert.h"


namespace Celeste
{
  namespace Networking
  {
    //------------------------------------------------------------------------------------------------
    void initialize()
    {
      // Initialize Winsock
      WSADATA wsaData;
      int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

      ASSERT(result == 0);
    }

    //------------------------------------------------------------------------------------------------
    void exit()
    {
      WSACleanup();
    }
  }
}