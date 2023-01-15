#include "retypes.hpp"

#include <cstdio>
#include <iostream>
#include <windows.h>


namespace re {

template <typename Address, typename HookFn>
auto hook_function(Address target, HookFn replacement) -> bool {

#pragma pack(push, 1)
  struct HookLayout {
    const u8 jmp{0xe9};
    u32 address{};
  };
#pragma pack(pop, 1)
  static_assert(sizeof(HookLayout) == 5, "Hook struct not packed");

  auto fn_start{reinterpret_cast<u32>(replacement) - target - 5};
  auto hook = HookLayout{.address{fn_start}};
  auto* handle = GetCurrentProcess();
  return WriteProcessMemory(handle, reinterpret_cast<LPVOID>(target), &hook, sizeof(hook), nullptr);
}

auto WINAPI load_string(UINT id, LPWSTR buffer, int max_size) -> void {
  LoadString(*reinterpret_cast<HINSTANCE*>(0x01005b30), id & 0xffff, buffer, max_size);
}

}; // namespace re

static auto apply_hooks() -> void {
  auto hook = [](auto address, auto replacement) -> void {
    if (re::hook_function(address, replacement)) {
      std::printf("$ function hooked: %#08x =>> %#08x\n", address, reinterpret_cast<u32>(replacement));
    } else {
      std::printf("! hook failed: %#08x\n", address);
    }
  };

  hook(0x010039e7, re::load_string);
}

auto WINAPI DllMain(HINSTANCE hInstance, DWORD fwdReason, LPVOID lpvReserved) -> BOOL {
  switch (fwdReason) {
  case DLL_PROCESS_ATTACH:
    AllocConsole();
    std::freopen("CONIN$", "r", stdin);
    std::freopen("CONOUT$", "w", stdout);
    std::freopen("CONOUT$", "w", stderr);
    std::cout << "DLL Hooked!\n";
    apply_hooks();
    break;
  case DLL_PROCESS_DETACH:
    std::cout << "DLL Detaching\n";
    FreeConsole();
    break;
  }
  return TRUE;
}
