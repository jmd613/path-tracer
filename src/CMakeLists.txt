add_subdirectory(math)
add_subdirectory(gfx)
add_subdirectory(geometry)
add_subdirectory(material)

add_executable(ray-tracer main.cc geometry/Sphere.h geometry/Sphere.cc geometry/IHittable.h Scene.h Scene.cc Camera.h)
target_link_libraries(ray-tracer PUBLIC math gfx material geometry)