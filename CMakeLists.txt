cmake_minimum_required(VERSION 3.22.1)

project(DIPDAB)

add_subdirectory(src/lodepng)

add_executable(main src/main.cpp)
add_subdirectory(src)
target_link_libraries(main PUBLIC lodepng)
target_include_directories(main PUBLIC 
  "${PROJECT_SOURCE_DIR}/src"
  "${PROJECT_SOURCE_DIR}/src/lodepng"
  )

