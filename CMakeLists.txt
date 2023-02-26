cmake_minimum_required(VERSION 3.22.1)

project(DIPDAB)

add_subdirectory(src/lodepng)

add_executable(MAIN src/decode_png.cpp)
target_link_libraries(MAIN PUBLIC lodepng)
target_include_directories(MAIN PUBLIC 
  "${PROJECT_SOURCE_DIR}/src/lodepng"
  )

