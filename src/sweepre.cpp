#include "functions.hpp"
#include "retypes.hpp"

#include <cstdio>
#include <format>
#include <iostream>
#include <windows.h>


template <class Address, class HookFn>
auto apply_hook(Address target, HookFn replacement) -> bool {
#pragma pack(push, 1)
  struct HookLayout {
    const u8 jmp{0xe9};
    u32 address{};
  };
#pragma pack(pop, 1)
  static_assert(sizeof(HookLayout) == 5, "Hook struct not packed");

  auto hook = HookLayout{.address{(u32) replacement - (u32) target - 5}};
  auto* handle = GetCurrentProcess();
  return WriteProcessMemory(handle, (LPVOID) target, &hook, sizeof(hook), nullptr);
}

static auto apply_hooks() -> void {
  auto hook = [](auto address, auto replacement) -> void {
    if (apply_hook(address, replacement)) {
      std::cout << std::format("$ hooked fn: 0x{:08x} =>> 0x{:08x}\n", (u32) address, (u32) replacement);
    } else {
      std::cout << std::format("! hook failed: 0x{:08x}\n", (u32) address);
    }
  };

  hook(0x1003950, re::show_error_dialog);
  hook(re::exe::redraw_h, (void(WINAPI*)(HDC)) re::redraw);
  hook(re::exe::draw_flag_counter_h, (void(WINAPI*)(HDC)) re::draw_flag_counter);
  hook(re::exe::draw_timer_h, (void(WINAPI*)(HDC)) re::draw_timer);
  hook(re::exe::draw_field_h, (void(WINAPI*)(HDC)) re::draw_field);
  hook(re::exe::set_hiscore, re::set_hiscore);
  hook(re::exe::set_pen_mode, re::set_pen_mode);
  hook(re::exe::draw_border, re::draw_border);
  hook(re::exe::draw_borders, re::draw_borders);
  hook(re::exe::tile_value, re::tile_value);
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
