#pragma once

#include "retypes.hpp"

#include <type_traits>
#include <windows.h>


namespace re::exe {

template <class T>
constexpr auto global(u32 address) -> T& {
  return *reinterpret_cast<T*>(address);
}

inline const auto app_module = global<HMODULE>(0x1005b30);

} // namespace re::exe
