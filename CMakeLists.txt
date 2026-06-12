cmake_minimum_required(VERSION 3.30)
project(skia-xemmai VERSION 202508)
find_package(xemmai 202508 REQUIRED)
# skia 9f02102df29835c04b4d82a0847596909f40d892
# is_official_build=true is_component_build=true skia_use_egl=true
set(SKIA ${PROJECT_SOURCE_DIR}/skia)
add_library(skia SHARED IMPORTED)
target_include_directories(skia INTERFACE ${SKIA})
set_property(TARGET skia PROPERTY IMPORTED_LOCATION ${SKIA}/out/Shared/libskia.so)
add_subdirectory(src)
enable_testing()
add_subdirectory(test)
set_property(TARGET skia-xemmai PROPERTY INSTALL_RPATH "\$ORIGIN/..")
install(TARGETS skia-xemmai DESTINATION lib/xemmai-${xemmai_VERSION_MAJOR})
