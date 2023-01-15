#pragma once

#include "retypes.hpp"

#include <type_traits>
#include <windows.h>


namespace re::exe {

template <class T>
constexpr auto global(u32 address) -> T& {
  return *reinterpret_cast<T*>(address);
}

inline auto& smiley_state = global<i32>(0x1005160);
inline auto& flag_counter = global<i32>(0x1005194);
inline auto& app_window = global<HWND>(0x1005b24);
inline auto& app_module = global<HMODULE>(0x1005b30);

} // namespace re::exe
