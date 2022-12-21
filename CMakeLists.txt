cmake_minimum_required(VERSION 3.20)
project(sweepre)

set(SWEEPRE_LIB ${PROJECT_NAME})

add_library(${SWEEPRE_LIB} STATIC)

add_subdirectory(src)
