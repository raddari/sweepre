#include "functions.hpp"

#include "globals.hpp"

#include <array>
#include <cstdlib>
#include <mmsystem.h>


auto WINAPI re::set_hiscore(HWND hDlg, i32 dlg_index, i32 time, LPCWSTR name) -> void {
  WCHAR text[32];

  wsprintf(text, exe::hiscore_format, time);
  SetDlgItemText(hDlg, dlg_index, text);
  SetDlgItemText(hDlg, dlg_index + 1, name);
}

auto WINAPI re::draw_field(HDC hdc) -> void {}

auto WINAPI re::draw_field() -> void {
  auto* hdc = GetDC(exe::window_handle);
  exe::draw_field_h(hdc);
  ReleaseDC(exe::window_handle, hdc);
}

auto WINAPI re::draw_digit(HDC hdc, i32 xpos, i32 digit) -> void {}

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
  exe::draw_digit(hdc, (exe::window_width - exe::border_width) - 56, elapsed / 100);
  exe::draw_digit(hdc, (exe::window_width - exe::border_width) - 43, tens / 10);
  exe::draw_digit(hdc, (exe::window_width - exe::border_width) - 30, tens % 10);

  if ((layout & 1) != 0) {
    SetLayout(hdc, layout);
  }
}

auto WINAPI re::draw_timer() -> void {
  auto* hdc = GetDC(exe::window_handle);
  exe::draw_timer_h(hdc);
  ReleaseDC(exe::window_handle, hdc);
}

auto WINAPI re::draw_smiley(HDC hdc, i32 smiley_state) -> void {}

auto WINAPI re::draw_smiley(i32 smiley_state) -> void {
  auto* hdc = GetDC(exe::window_handle);
  exe::draw_smiley_h(hdc, smiley_state);
  ReleaseDC(exe::window_handle, hdc);
}

auto WINAPI re::draw_borders(HDC hdc) -> void {}

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

auto WINAPI re::modify_flag_counter(i32 amount) -> void {
  exe::flag_counter += amount;
  exe::draw_flag_counter();
}

auto WINAPI re::stop_sounds() -> i32 {
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
