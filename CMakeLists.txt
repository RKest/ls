cmake_minimum_required(VERSION 3.23)

project(LSTree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

include(cmake/find_libs.cmake)
include(GoogleTest)
enable_testing()

add_subdirectory(src)
add_subdirectory(tests)

add_executable(main include/ls/types/Range.hpp)

target_link_libraries(main PRIVATE ls_tree)