add_subdirectory(math)
add_subdirectory(util)

add_executable(ray-tracer main.cc)
target_link_libraries(ray-tracer PUBLIC math util)