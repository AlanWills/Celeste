#include "System/Process.h"

#include <Windows.h>


namespace Celeste
{
  namespace System
  {
    //------------------------------------------------------------------------------------------------
    void Process::start(const std::string& commandLine, const OnProcessCompleteCallback& onProcessComplete)
    {
      // WINDOWS ONLY

      // additional information
      STARTUPINFO si;
      PROCESS_INFORMATION pi;

      // set the size of the structures
      ZeroMemory(&si, sizeof(si));
      si.cb = sizeof(si);
      ZeroMemory(&pi, sizeof(pi));

      LPTSTR commandLineArgs = const_cast<LPTSTR>(commandLine.c_str());

      // start the program up
      CreateProcess(nullptr,   // the path
        commandLineArgs,        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,           // Pointer to STARTUPINFO structure
        &pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
      );

      // Wait until child process exits.
      WaitForSingleObject(pi.hProcess, INFINITE);

      // Close process and thread handles. 
      CloseHandle(pi.hProcess);
      CloseHandle(pi.hThread);

      if (onProcessComplete)
      {
        onProcessComplete();
      }
    }
  }
}