set(CMAKE_AUTOMOC ON)

cmake_minimum_required(VERSION 3.16)
project(hadess-sensorfw-proxy)

include(GNUInstallDirs)
find_package(PkgConfig REQUIRED)

pkg_check_modules(GIO REQUIRED gio-2.0)
pkg_check_modules(GUDEV REQUIRED gudev-1.0)

find_package(Qt6Network REQUIRED)

add_subdirectory(sensorfw-core)

add_executable(
    hadess-sensorfw-proxy

    iio-sensor-proxy.cpp
    iio-sensor-proxy-resources.cpp
    orientation.cpp
)

target_link_libraries(hadess-sensorfw-proxy PUBLIC
    sensorfw-core
)

target_include_directories(hadess-sensorfw-proxy PUBLIC
    ${GIO_INCLUDE_DIRS}
    ${GUDEV_INCLUDE_DIRS}
)

install(TARGETS hadess-sensorfw-proxy RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
