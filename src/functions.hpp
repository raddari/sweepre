#pragma once

#include "retypes.hpp"

#include <type_traits>
#include <windows.h>


namespace re {

auto WINAPI show_error_dialog(UINT error_id) -> void;

} // namespace re

namespace re::exe {

template <class Signature>
constexpr auto func(u32 address) -> Signature {
  return reinterpret_cast<Signature>(address);
}

inline const auto show_error_dialog = func<void(WINAPI*)(UINT)>(0x1003950);

} // namespace re::exe
