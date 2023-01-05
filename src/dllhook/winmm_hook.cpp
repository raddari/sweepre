#include "winmm_hook.h"


using FnPlaySoundW = BOOL(WINAPI*)(LPCWSTR, HMODULE, DWORD);

static HINSTANCE hSweepreLib{nullptr};
static FnPlaySoundW forward_PlaySoundW{nullptr};

auto WINAPI PlaySoundW(LPCWSTR pszSound, HMODULE hmod, DWORD fdwSound) -> BOOL {
  if (!hSweepreLib) [[unlikely]] {
    hSweepreLib = LoadLibrary(L"sweepre");
    // TODO(raddari): find a way to load winmm.dll from system directory
    HINSTANCE hWinLib = LoadLibraryEx(L"WINMM", nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
    forward_PlaySoundW = reinterpret_cast<FnPlaySoundW>(GetProcAddress(hWinLib, "PlaySoundW"));
  }
  return TRUE;
}
