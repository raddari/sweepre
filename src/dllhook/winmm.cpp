#include "winmm.h"

#include <array>
#include <format>
#include <optional>
#include <string>
#include <string_view>


namespace {

auto show_error(LPCWSTR text, LPCWSTR caption) {
  MessageBoxW(nullptr, text, caption, MB_OK | MB_ICONERROR);
}

auto show_error(LPCSTR text, LPCSTR caption) {
  MessageBoxA(nullptr, text, caption, MB_OK | MB_ICONERROR);
}

auto get_system_directory() -> std::wstring_view {
  static std::optional<std::wstring> path = std::nullopt;
  if (!path) {
    std::array<WCHAR, 512> buffer{};
    GetSystemDirectory(buffer.data(), buffer.size());
    path.emplace(buffer.data());
  }
  return *path;
}

auto load_system_library(std::wstring_view name) -> HINSTANCE {
  auto system_dir = get_system_directory();
  auto module_name = std::format(LR"({}\{})", system_dir, name);

  auto* module = LoadLibrary(module_name.c_str());
  if (!module) {
    auto err_text = std::format(L"Could not find system library {}.\n\nTried path: {}", name, module_name);
    show_error(err_text.c_str(), L"LoadLibrary");
  }
  return module;
}

template <class Fn>
auto get_proc_address(HINSTANCE lib, LPCSTR proc_name) -> Fn {
  auto* proc = (Fn) GetProcAddress(lib, proc_name);
  if (!proc) {
    auto err_text = std::format("Could not find {}. Functionality may be missing.", proc_name);
    show_error(err_text.c_str(), "GetProcAddress");
  }
  return proc;
}

} // namespace

auto WINAPI PlaySoundW(LPCWSTR pszSound, HMODULE hmod, DWORD fdwSound) -> BOOL {
  auto* winmm = load_system_library(L"winmm.dll");

  using FnPlaySoundW = BOOL(WINAPI*)(LPCWSTR, HMODULE, DWORD);
  auto* PlaySoundW_real = get_proc_address<FnPlaySoundW>(winmm, "PlaySoundW");
  if (!PlaySoundW_real) {
    return FALSE;
  }
  return PlaySoundW_real(pszSound, hmod, fdwSound);
}
