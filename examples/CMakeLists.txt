cmake_minimum_required(VERSION 3.0)
project(read_hdd_serial VERSION 0.0.1.1 LANGUAGES C CXX)

include_directories("./" "../src")

link_directories("../src")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O2 -Wno-pragmas -Wno-unused-result")

set(SOURCE_FILES
    read_hdd_serial.cc
   )

## TARGET
add_executable(read_hdd_serial ${SOURCE_FILES})
target_link_libraries(read_hdd_serial ${CMAKE_DL_LIBS} udev_dynamic_wrapper)

install(TARGETS read_hdd_serial DESTINATION ../out)
