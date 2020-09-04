add_library(math STATIC Vec3.h Vec3.cc Ray.h Util.h)
target_include_directories(math PUBLIC .)