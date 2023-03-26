#include <windows.h>


auto APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd) -> int {
  return MessageBox(nullptr, L"Hello, world!", L"caption", 0);
}