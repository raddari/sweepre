#pragma once

#include <windef.h>

#define DLLEXPORT __declspec(dllexport)


EXTERN_C BOOL DLLEXPORT WINAPI
PlaySoundW(LPCWSTR pszSound, HMODULE hmod, DWORD fdwSound);
