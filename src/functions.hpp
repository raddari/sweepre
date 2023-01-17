#pragma once

#include "retypes.hpp"

#include <type_traits>
#include <windows.h>


namespace re {

auto WINAPI draw_field(HDC hdc) -> void;
auto WINAPI draw_field() -> void;
auto WINAPI draw_digit(HDC hdc, i32 xpos, i32 digit) -> void;
auto WINAPI draw_flag_counter(HDC hdc) -> void;
auto WINAPI draw_flag_counter() -> void;
auto WINAPI draw_timer(HDC hdc) -> void;
auto WINAPI draw_timer() -> void;
auto WINAPI draw_smiley(HDC hdc, i32 smiley_state) -> void;
auto WINAPI draw_smiley(i32 smiley_state) -> void;
auto WINAPI draw_borders(HDC hdc) -> void;
auto WINAPI redraw(HDC hdc) -> void;
auto WINAPI redraw() -> void;
auto WINAPI modify_flag_counter(i32 amount) -> void;
auto WINAPI show_error_dialog(UINT error_id) -> void;

} // namespace re

namespace re::exe {

template <class Signature>
constexpr auto func(u32 address) -> Signature {
  return reinterpret_cast<Signature>(address);
}

#define EXE_FUNC inline const auto
EXE_FUNC draw_field_h = func<void(WINAPI*)(HDC)>(0x10026a7);
EXE_FUNC draw_field = func<void(WINAPI*)()>(0x100272e);
EXE_FUNC draw_digit = func<void(WINAPI*)(HDC, i32, i32)>(0x1002752);
EXE_FUNC draw_flag_counter_h = func<void(WINAPI*)(HDC)>(0x1002785);
EXE_FUNC draw_flag_counter = func<void(WINAPI*)()>(0x1002801);
EXE_FUNC draw_timer_h = func<void(WINAPI*)(HDC)>(0x1002825);
EXE_FUNC draw_timer = func<void(WINAPI*)()>(0x10028b5);
EXE_FUNC draw_smiley_h = func<void(WINAPI*)(HDC, i32)>(0x10028d9);
EXE_FUNC draw_smiley = func<void(WINAPI*)(i32)>(0x1002913);
EXE_FUNC draw_borders = func<void(WINAPI*)(HDC)>(0x1002a22);
EXE_FUNC redraw_h = func<void(WINAPI*)(HDC)>(0x1002ac3);
EXE_FUNC redraw = func<void(WINAPI*)()>(0x1002af0);
EXE_FUNC modify_flag_counter = func<void(WINAPI*)(i32)>(0x100346a);
EXE_FUNC show_error_dialog = func<void(WINAPI*)(UINT)>(0x1003950);
#undef EXE_FUNC

} // namespace re::exe