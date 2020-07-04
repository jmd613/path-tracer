add_library(gfx STATIC Image.h Image.cc Pixel.h)
target_include_directories(gfx PUBLIC .)
#target_link_libraries(gfx PUBLIC math)