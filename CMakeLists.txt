cmake_minimum_required(VERSION 3.25)
project(sweepre LANGUAGES CXX)

set(DLL_HOOK_NAME "winmm" CACHE STRING "Output name for hooking library")

set(DLL_HOOK_LIB ${DLL_HOOK_NAME})
add_library(${DLL_HOOK_LIB} SHARED)
target_compile_definitions(${DLL_HOOK_LIB} PUBLIC
  UNICODE
  WIN32_LEAN_AND_MEAN
)

set(SWEEPRE_EXE ${PROJECT_NAME})
add_executable(${SWEEPRE_EXE} WIN32)
target_compile_definitions(${SWEEPRE_EXE} PUBLIC
  UNICODE
  WIN32_LEAN_AND_MEAN
)

install(TARGETS ${DLL_HOOK_LIB} ${SWEEPRE_EXE}
  RUNTIME DESTINATION "."
)

add_subdirectory(src)
