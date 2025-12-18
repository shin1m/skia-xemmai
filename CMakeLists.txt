cmake_minimum_required(VERSION 3.30)
project(skia-xemmai VERSION 202508)
find_package(xemmai 202508 REQUIRED)
# skia 6903a4e65c3ffeb3e7aaa3a94bdc46f1bb1a75b7
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
