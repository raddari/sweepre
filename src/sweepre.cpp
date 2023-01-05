#include "retypes.hpp"

#include <concepts>
#include <iomanip>
#include <iostream>
#include <windows.h>


namespace re {

template <typename Address, typename HookFn>
  requires std::is_convertible_v<Address, std::uintptr_t>
auto hook_function(Address target, HookFn replacement) -> bool {
  using std::uintptr_t;

#pragma pack(push, 1)
  struct HookLayout {
    const u8 jmp{0xe9};
    uintptr_t address{};
  };
#pragma pack(pop, 1)
  static_assert(sizeof(HookLayout) == 5, "Hook struct not packed");

  auto fn_start{reinterpret_cast<uintptr_t>(replacement) - target - 5};
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
    using namespace std;
    auto save_flags = ios::fmtflags{cout.flags()};
    cout << hex << showbase << setfill('0') << setw(10);

    if (re::hook_function(address, replacement)) {
      cout << "$ function hooked: " << address << " =>> " << reinterpret_cast<std::uintptr_t>(replacement) << "\n";
    } else {
      cout << "! hook failed: " << address << "\n";
    }

    cout.flags(save_flags);
  };

  hook(0x010039e7, re::load_string);
}

auto WINAPI DllMain(HINSTANCE hInstance, DWORD fwdReason, LPVOID lpvReserved) -> BOOL {
  switch (fwdReason) {
  case DLL_PROCESS_ATTACH:
    AllocConsole();
    std::freopen("CONOUT$", "wb", stdout);
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
