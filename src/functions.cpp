#include "functions.hpp"

#include "globals.hpp"

#include <algorithm>
#include <cstdlib>
#include <mmsystem.h>


auto WINAPI re::set_hiscore(HWND hDlg, i32 dlg_index, i32 time, LPCWSTR name) -> void {
  WCHAR text[32];

  wsprintf(text, exe::hiscore_format, time);
  SetDlgItemText(hDlg, dlg_index, text);
  SetDlgItemText(hDlg, dlg_index + 1, name);
}

auto WINAPI re::draw_field(HDC hdc) -> void {
  auto y = 55;
  for (auto row = 1; row <= exe::field_height; ++row) {
    auto x = 12;
    for (auto col = 1; col <= exe::field_width; ++col) {
      auto tile = exe::minefield[row * 32 + col];
      BitBlt(hdc, x, y, 16, 16, exe::tile_bmps[tile & 0x1f], 0, 0, SRCCOPY);
      x += 16;
    }
    y += 16;
  }
}

auto WINAPI re::draw_field() -> void {
  auto* hdc = GetDC(exe::window_handle);
  exe::draw_field_h(hdc);
  ReleaseDC(exe::window_handle, hdc);
}

auto WINAPI re::draw_digit(HDC hdc, i32 xpos, i32 digit) -> void {
  auto* bits = (u8*) exe::digit_bmpinfo + exe::digit_bmps[digit];
  SetDIBitsToDevice(hdc, xpos, 16, 13, 23, 0, 0, 0, 23, bits, exe::digit_bmpinfo, DIB_RGB_COLORS);
}

auto WINAPI re::draw_flag_counter(HDC hdc) -> void {
  auto layout = GetLayout(hdc);
  if ((layout & 1) != 0) {
    SetLayout(hdc, 0);
  }

  auto left_digit = exe::flag_counter / 100;
  auto absolute = exe::flag_counter;
  if (exe::flag_counter < 0) {
    left_digit = 11;
    absolute = -absolute;
  }

  exe::draw_digit(hdc, 17, left_digit);
  exe::draw_digit(hdc, 30, (absolute % 100) / 10);
  exe::draw_digit(hdc, 43, (absolute % 100) % 10);

  if ((layout & 1) != 0) {
    SetLayout(hdc, layout);
  }
}

auto WINAPI re::draw_flag_counter() -> void {
  auto* hdc = GetDC(exe::window_handle);
  exe::draw_flag_counter_h(hdc);
  ReleaseDC(exe::window_handle, hdc);
}

auto WINAPI re::draw_timer(HDC hdc) -> void {
  auto layout = GetLayout(hdc);
  if ((layout & 1) != 0) {
    SetLayout(hdc, 0);
  }

  auto elapsed = exe::game_timer;
  auto tens = elapsed % 100;
  auto inside_width = exe::window_width - exe::border_width;
  exe::draw_digit(hdc, inside_width - 56, elapsed / 100);
  exe::draw_digit(hdc, inside_width - 43, tens / 10);
  exe::draw_digit(hdc, inside_width - 30, tens % 10);

  if ((layout & 1) != 0) {
    SetLayout(hdc, layout);
  }
}

auto WINAPI re::draw_timer() -> void {
  auto* hdc = GetDC(exe::window_handle);
  exe::draw_timer_h(hdc);
  ReleaseDC(exe::window_handle, hdc);
}

// TODO: implement
auto WINAPI re::draw_smiley(HDC hdc, i32 smiley_state) -> void {}

auto WINAPI re::draw_smiley(i32 smiley_state) -> void {
  auto* hdc = GetDC(exe::window_handle);
  exe::draw_smiley_h(hdc, smiley_state);
  ReleaseDC(exe::window_handle, hdc);
}

auto WINAPI re::set_pen_mode(HDC hdc, i8 white) -> void {
  if ((white & 1) == 0) {
    SetROP2(hdc, R2_COPYPEN);
    SelectObject(hdc, exe::border_pen);
  } else {
    SetROP2(hdc, R2_WHITE);
  }
}

auto WINAPI re::draw_border(HDC hdc, i32 x1, i32 y1, i32 x2, i32 y2, i32 thickness, i32 color) -> void {
  exe::set_pen_mode(hdc, (i8) color);
  for (auto i = thickness; i > 0; --i) {
    y2 -= 1;
    MoveToEx(hdc, x1, y2, nullptr);
    LineTo(hdc, x1, y1);
    x1 += 1;
    LineTo(hdc, x2, y1);
    x2 -= 1;
    y1 += 1;
  }

  if (color < 2) {
    exe::set_pen_mode(hdc, (i8) color ^ 1);
  }

  for (auto i = thickness; i > 0; --i) {
    y2 += 1;
    MoveToEx(hdc, x1, y2, nullptr);
    x1 -= 1;
    x2 += 1;
    LineTo(hdc, x2, y2);
    y1 -= 1;
    LineTo(hdc, x2, y1);
  }
}

auto WINAPI re::draw_borders(HDC hdc) -> void {
  auto width = exe::window_width;
  auto height = exe::window_height;

  // outside edge
  exe::draw_border(hdc, 0, 0, width - 1, height + 1, 3, 1);
  // playing field
  exe::draw_border(hdc, 9, 52, width - 10, height - 10, 3, 0);
  // status bar
  exe::draw_border(hdc, 9, 9, width - 10, 45, 2, 0);
  exe::draw_border(hdc, 16, 15, 56, 39, 1, 0);

  auto inside_width = width - exe::border_width;
  exe::draw_border(hdc, inside_width - 57, 15, inside_width - 17, 39, 1, 0);

  width = (width - 24) / 2;
  exe::draw_border(hdc, width - 1, 15, width + 24, 40, 1, 2);
}

auto WINAPI re::redraw(HDC hdc) -> void {
  exe::draw_borders(hdc);
  exe::draw_flag_counter_h(hdc);
  exe::draw_smiley_h(hdc, exe::smiley_state);
  exe::draw_timer_h(hdc);
  exe::draw_field_h(hdc);
}

auto WINAPI re::redraw() -> void {
  auto* hdc = GetDC(exe::window_handle);
  exe::redraw_h(hdc);
  ReleaseDC(exe::window_handle, hdc);
}

auto WINAPI re::tile_value(i32 col, i32 row) -> i32 {
  i32 value = 0;

  // col and row index begin at 1
  auto min_row = std::max(0, row - 1);
  auto max_row = row + 1;
  auto min_col = std::max(0, col - 1);
  auto max_col = col + 1;

  for (auto r = min_row; r <= max_row; ++r) {
    for (auto c = min_col; c <= max_col; ++c) {
      auto tile = exe::minefield[r * 32 + c];
      if ((tile & 0x80) != 0) {
        value += 1;
      }
    }
  }

  return value;
}

auto WINAPI re::modify_flag_counter(i32 amount) -> void {
  exe::flag_counter += amount;
  exe::draw_flag_counter();
}

auto WINAPI re::can_play_sounds() -> i32 {
  auto success = PlaySound(nullptr, nullptr, SND_PURGE);
  return (success != 0) + 2;
}

auto WINAPI re::play_sound(UINT sound_id) -> void {
  i32 resource;

  if (exe::opt_sound == 3) {
    switch (sound_id) {
    case 1:
      resource = 0x1b0;
      break;
    case 2:
      resource = 0x1b1;
      break;
    case 3:
      resource = 0x1b2;
      break;
    default:
      return;
    }
    PlaySound(MAKEINTRESOURCE(resource), exe::module_handle, SND_RESOURCE | SND_ASYNC);
  }
}

auto WINAPI re::rand_int(i32 bound) -> i32 {
  auto rng = rand();
  return rng % bound;
}

auto WINAPI re::show_error_dialog(UINT error_id) -> void {
  WCHAR text[128];
  WCHAR caption[128];

  if (error_id < 999) {
    LoadString(exe::module_handle, error_id & 0xffff, text, 128);
  } else {
    LoadString(exe::module_handle, 6, caption, 128);
    wsprintf(text, caption, error_id & 0xffff);
  }

  LoadString(exe::module_handle, 3, caption, 128);
  MessageBox(nullptr, text, caption, MB_ICONERROR);
}

auto WINAPI re::load_string(UINT string_id, LPWSTR buffer, i32 max_size) -> void {
  auto length = LoadString(exe::module_handle, string_id & 0xffff, buffer, max_size);
  if (length == 0) {
    exe::show_error_dialog(0x3e9);
  }
}
