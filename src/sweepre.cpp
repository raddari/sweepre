#include <iostream>
#include <windows.h>


auto WINAPI DllMain(HINSTANCE hInstance, DWORD fwdReason, LPVOID lpvReserved) -> BOOL {
  switch (fwdReason) {
    case DLL_PROCESS_ATTACH:
      AllocConsole();
      std::freopen("CONOUT$", "wb", stdout);
      std::cout << "DLL Hooked!\n";
      break;
    case DLL_PROCESS_DETACH:
      std::cout << "DLL Detaching\n";
      FreeConsole();
      break;
  }
  return TRUE;
}
