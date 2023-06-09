#pragma once

#include "retypes.hpp"

#include <type_traits>
#include <windows.h>


namespace re::exe {

template <class T>
constexpr auto global(u32 address) -> T& {
  return *reinterpret_cast<T*>(address);
}

#define EXE_REF(address, ident, type) inline auto& ident = global<type>((address))

EXE_REF(0x1005158, border_pen, HPEN);
EXE_REF(0x1005160, smiley_state, i32);
EXE_REF(0x1005194, flag_counter, i32);
EXE_REF(0x1005334, field_width, i32);
EXE_REF(0x1005338, field_height, i32);
// padding[33]:   0x1005340 - 0x1005360
// playable[766]: 0x1005361 - 0x100555E
// padding[33]:   0x100555F - 0x100557F
EXE_REF(0x1005340, minefield, u8[832]);
EXE_REF(0x10056b8, opt_sound, i32);
EXE_REF(0x10056cc, beginner_hiscore, i32);
EXE_REF(0x10056d0, intermediate_hiscore, i32);
EXE_REF(0x10056d4, expert_hiscore, i32);
EXE_REF(0x100579c, game_timer, i32);
EXE_REF(0x100595c, digit_bmpinfo, BITMAPINFO*);
// Each element is an offset into #smiley_bmpinfo specifying the start of the digit's color table
EXE_REF(0x1005960, smiley_bmps, i32[5]);
EXE_REF(0x1005a00, smiley_bmpinfo, BITMAPINFO*);
EXE_REF(0x1005a20, tile_bmps, HDC[16]);
// Each element is an offset into #digit_bmpinfo specifying the start of the digit's color table
EXE_REF(0x1005a60, digit_bmps, i32[12]);
EXE_REF(0x1005a90, border_width, i32);
EXE_REF(0x1005ae0, hiscore_format, WCHAR[32]);
EXE_REF(0x1005b20, window_height, i32);
EXE_REF(0x1005b24, window_handle, HWND);
EXE_REF(0x1005b2c, window_width, i32);
EXE_REF(0x1005b30, module_handle, HMODULE);

#undef EXE_REF

} // namespace re::exe
