#pragma once

#include "retypes.hpp"

#include <type_traits>
#include <windows.h>


namespace re::exe {

template <class T>
constexpr auto global(u32 address) -> T& {
  return *reinterpret_cast<T*>(address);
}

#define EXE_REF inline auto&
EXE_REF smiley_state = global<i32>(0x1005160);
EXE_REF flag_counter = global<i32>(0x1005194);
EXE_REF game_timer = global<i32>(0x100579c);
EXE_REF border_width = global<i32>(0x1005a90);
EXE_REF window_handle = global<HWND>(0x1005b24);
EXE_REF window_width = global<i32>(0x01005b2c);
EXE_REF module_handle = global<HMODULE>(0x1005b30);
#undef EXE_REF

} // namespace re::exe
