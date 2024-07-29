
add_executable(hello main.cpp)

add_subdirectory(alg)

target_link_libraries(hello common_alg)