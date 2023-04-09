cmake_minimum_required(VERSION 3.25)
project(sweepre LANGUAGES CXX)

set(DLL_HOOK_NAME "winmm" CACHE STRING "Output name for hooking library")

set(DLL_HOOK_LIB ${DLL_HOOK_NAME})
add_library(${DLL_HOOK_LIB} SHARED)
target_compile_definitions(${DLL_HOOK_LIB} PUBLIC
    UNICODE
    WIN32_LEAN_AND_MEAN
    NOMINMAX
    )

target_compile_features(${DLL_HOOK_LIB} PRIVATE
    cxx_std_23
    )

install(TARGETS ${DLL_HOOK_LIB}
    RUNTIME DESTINATION "."
    )

add_subdirectory(src)
