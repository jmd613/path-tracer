add_library(geometry STATIC Sphere.h Sphere.cc IHittable.h)
target_include_directories(geometry PUBLIC .)
target_link_libraries(geometry PUBLIC math material)
