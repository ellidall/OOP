cmake_minimum_required(VERSION 3.26)
project(ShapesApp)

enable_testing()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_OUTPUT_PATH "bin")

add_subdirectory(src)

add_executable(ShapesApp main.cpp)

target_link_libraries(ShapesApp PRIVATE .)

add_subdirectory(test)

add_dependencies(ShapesApp run_tests)