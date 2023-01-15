#include "winmm.h"


auto WINAPI PlaySoundW(LPCWSTR pszSound, HMODULE hmod, DWORD fdwSound) -> BOOL {
  // TODO(raddari): find a way to load the real winmm.dll
  return FALSE;
}
