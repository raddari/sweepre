#include "functions.hpp"

#include "globals.hpp"

#include <array>


auto WINAPI re::show_error_dialog(UINT error_id) -> void {
  WCHAR text[128];
  WCHAR caption[128];

  if (error_id < 999) {
    LoadString(re::exe::app_module, error_id & 0xffff, text, 128);
  } else {
    LoadString(re::exe::app_module, 6, caption, 128);
    wsprintf(text, caption, error_id & 0xffff);
  }

  LoadString(re::exe::app_module, 3, caption, 128);
  MessageBox(nullptr, text, caption, MB_ICONERROR);
}
