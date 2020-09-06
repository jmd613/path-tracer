add_library(material STATIC Material.cc)
target_include_directories(material PUBLIC .)
target_link_libraries(material PUBLIC math geometry)