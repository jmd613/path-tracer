add_subdirectory(math)
add_subdirectory(gfx)

add_executable(ray-tracer main.cc)
target_link_libraries(ray-tracer PUBLIC math gfx)