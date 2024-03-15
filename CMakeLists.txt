cmake_minimum_required(VERSION 3.28.1)
project(c C)

file(GLOB_RECURSE source_files "src/*.c")

add_executable(c ${source_files})

set_target_properties(c PROPERTIES OUTPUT_NAME "${PROJECT_SOURCE_DIR}/bin/c")
target_include_directories(c PRIVATE lib)