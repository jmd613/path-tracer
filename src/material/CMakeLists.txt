add_library(material STATIC Material.h)
target_include_directories(material PUBLIC .)
set_target_properties(material PROPERTIES LINKER_LANGUAGE CXX)