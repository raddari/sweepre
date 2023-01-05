#pragma once

#include <windows.h>


#pragma comment(linker, "/export:PlaySoundW=_PlaySoundW@12")
EXTERN_C BOOL WINAPI PlaySoundW(LPCWSTR pszSound, HMODULE hmod, DWORD fdwSound);
