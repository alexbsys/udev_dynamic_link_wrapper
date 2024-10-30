
cmake_minimum_required(VERSION 3.0)

project(udev_dynamic_wrapper VERSION 0.0.1.1 LANGUAGES C CXX)

set (SOURCE_FILES
  dynamic_modules_loader.cc
  udev_module_provider.cc
)

add_library(udev_dynamic_wrapper STATIC ${SOURCE_FILES})

install(TARGETS udev_dynamic_wrapper DESTINATION ../out)

