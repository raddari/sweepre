cmake_minimum_required(VERSION 3.25)
project(sweepre LANGUAGES CXX)

set(DLL_HOOK_NAME "WINMM" CACHE STRING "Output name for hooking DLL")

set(SWEEPRE_LIB ${PROJECT_NAME})
add_library(${SWEEPRE_LIB} SHARED)
target_compile_definitions(${SWEEPRE_LIB}
  PUBLIC UNICODE
  PUBLIC WIN32_LEAN_AND_MEAN
)

set(DLL_HOOK_LIB ${DLL_HOOK_NAME})
add_library(${DLL_HOOK_LIB} SHARED)
target_compile_definitions(${DLL_HOOK_LIB}
  PUBLIC UNICODE
  PUBLIC WIN32_LEAN_AND_MEAN
)

install(TARGETS ${SWEEPRE_LIB} ${DLL_HOOK_LIB}
  RUNTIME DESTINATION "."
)

add_subdirectory(src)
add_subdirectory(src/dllhook)
