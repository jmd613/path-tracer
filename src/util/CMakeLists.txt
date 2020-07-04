add_library(util STATIC Image.h Image.cc)
target_include_directories(util PUBLIC .)
target_link_libraries(util PUBLIC math)