#pragma once

#include <windows.h>

#define DLLEXPORT __declspec(dllexport)


#pragma comment(linker, "/export:PlaySoundW=_PlaySoundW@12")
EXTERN_C DLLEXPORT BOOL WINAPI PlaySoundW(LPCWSTR pszSound, HMODULE hmod, DWORD fdwSound);
