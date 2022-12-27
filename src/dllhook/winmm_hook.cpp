#include "winmm_hook.h"


auto DLLEXPORT WINAPI PlaySoundW(LPCWSTR pszSound, HMODULE hmod, DWORD fdwSound) -> BOOL {
  static HINSTANCE hWinLib{nullptr};
  if (!hWinLib) [[unlikely]] {

  }
  return TRUE;
}
