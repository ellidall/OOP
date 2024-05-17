FILE(GLOB_RECURSE SRC "*.h" "*.cpp")
add_library(shapes ${SRC})
target_include_directories(shapes PUBLIC .)