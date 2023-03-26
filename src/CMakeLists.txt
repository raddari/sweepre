target_sources(${DLL_HOOK_LIB} PRIVATE
  dllhook/winmm.cpp
  dllhook/winmm.h
  functions.cpp
  functions.hpp
  globals.hpp
  retypes.hpp
  sweepre.cpp
)

target_sources(${SWEEPRE_EXE} PRIVATE
  main.cpp
)
