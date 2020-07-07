add_subdirectory(math)
add_subdirectory(gfx)

add_executable(ray-tracer main.cc Sphere.h Sphere.cc IHittable.h Scene.h Scene.cc Camera.h)
target_link_libraries(ray-tracer PUBLIC math gfx)