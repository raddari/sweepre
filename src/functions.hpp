#pragma once

#include "retypes.hpp"

#include <type_traits>
#include <windows.h>


namespace re {

auto WINAPI set_hiscore(HWND hDlg, i32 dlg_index, i32 time, LPCWSTR name) -> void;
auto WINAPI draw_tile(i32 col, i32 row) -> void;
auto WINAPI draw_field(HDC hdc) -> void;
auto WINAPI draw_field() -> void;
auto WINAPI draw_digit(HDC hdc, i32 xpos, i32 digit) -> void;
auto WINAPI draw_flag_counter(HDC hdc) -> void;
auto WINAPI draw_flag_counter() -> void;
auto WINAPI draw_timer(HDC hdc) -> void;
auto WINAPI draw_timer() -> void;
auto WINAPI draw_smiley(HDC hdc, i32 smiley_state) -> void;
auto WINAPI draw_smiley(i32 smiley_state) -> void;
auto WINAPI set_pen_mode(HDC hdc, i8 white) -> void;
auto WINAPI draw_border(HDC hdc, i32 x1, i32 y1, i32 x2, i32 y2, i32 thickness, i32 color) -> void;
auto WINAPI draw_borders(HDC hdc) -> void;
auto WINAPI redraw(HDC hdc) -> void;
auto WINAPI redraw() -> void;
auto WINAPI tile_value(i32 col, i32 row) -> i32;
auto WINAPI modify_flag_counter(i32 amount) -> void;
auto WINAPI can_play_sounds() -> i32;
auto WINAPI play_sound(UINT sound_id) -> void;
auto WINAPI rand_int(i32 bound) -> i32;
auto WINAPI show_error_dialog(UINT error_id) -> void;
auto WINAPI load_string(UINT string_id, LPWSTR buffer, i32 max_size) -> void;

} // namespace re

namespace re::exe {

template <class Signature, class FuncPtr = std::add_pointer_t<Signature>>
  requires std::is_function_v<Signature>
constexpr inline auto func(u32 address) -> FuncPtr {
  return reinterpret_cast<FuncPtr>(address);
}

#define EXE_FUNC(address, ident, signature) inline const auto ident = func<signature>((address))

EXE_FUNC(0x10016ba, set_hiscore, void WINAPI(HWND, i32, i32, LPCWSTR));
EXE_FUNC(0x1002646, draw_tile, void WINAPI(i32, i32));
EXE_FUNC(0x10026a7, draw_field_h, void WINAPI(HDC));
EXE_FUNC(0x100272e, draw_field, void WINAPI());
EXE_FUNC(0x1002752, draw_digit, void WINAPI(HDC, i32, i32));
EXE_FUNC(0x1002785, draw_flag_counter_h, void WINAPI(HDC));
EXE_FUNC(0x1002801, draw_flag_counter, void WINAPI());
EXE_FUNC(0x1002825, draw_timer_h, void WINAPI(HDC));
EXE_FUNC(0x10028b5, draw_timer, void WINAPI());
EXE_FUNC(0x10028d9, draw_smiley_h, void WINAPI(HDC, i32));
EXE_FUNC(0x1002913, draw_smiley, void WINAPI(i32));
EXE_FUNC(0x100293d, set_pen_mode, void WINAPI(HDC, i8));
EXE_FUNC(0x1002971, draw_border, void WINAPI(HDC, i32, i32, i32, i32, i32, i32));
EXE_FUNC(0x1002a22, draw_borders, void WINAPI(HDC));
EXE_FUNC(0x1002ac3, redraw_h, void WINAPI(HDC));
EXE_FUNC(0x1002af0, redraw, void WINAPI());
EXE_FUNC(0x1002f3b, tile_value, i32 WINAPI(i32, i32));
EXE_FUNC(0x100346a, modify_flag_counter, void WINAPI(i32));
EXE_FUNC(0x10038c2, can_play_sounds, i32 WINAPI());
EXE_FUNC(0x10038ed, play_sound, void WINAPI(UINT));
EXE_FUNC(0x1003940, rand_int, i32 WINAPI(i32));
EXE_FUNC(0x1003950, show_error_dialog, void WINAPI(UINT));
EXE_FUNC(0x10039e7, load_string, void WINAPI(UINT, LPWSTR, i32));

#undef EXE_FUNC

} // namespace re::exe
