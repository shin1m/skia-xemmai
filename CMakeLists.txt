cmake_minimum_required(VERSION 3.30)
project(skia-xemmai VERSION 202504)
find_package(xemmai 202504 REQUIRED)
set(SKIA ${PROJECT_SOURCE_DIR}/skia)
add_library(skia SHARED IMPORTED)
target_include_directories(skia INTERFACE ${SKIA})
set_property(TARGET skia PROPERTY IMPORTED_LOCATION ${SKIA}/out/Shared/libskia.so)
add_subdirectory(src)
enable_testing()
add_subdirectory(test)
set_property(TARGET skia-xemmai PROPERTY INSTALL_RPATH "\$ORIGIN/..")
install(TARGETS skia-xemmai DESTINATION lib/xemmai-${xemmai_VERSION_MAJOR})
