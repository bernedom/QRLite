cmake_minimum_required(VERSION 3.21)

project(
  QRLite
  VERSION 1.0.0
  LANGUAGES CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set(CMAKE_FIND_DEBUG_MODE TRUE)
find_package(
  Qt6
  COMPONENTS Core Gui Multimedia Qml Quick
  REQUIRED)
# set(CMAKE_FIND_DEBUG_MODE FALSE)

message(
  STATUS
    "QT
    has
    been
    found
    ${Qt6_FOUND}")

find_package(ZXing REQUIRED)

if(NOT ANDROID)
  find_package(Catch2)
endif()

include(CTest)

get_target_property(ZXINGdirs ZXing::ZXing INTERFACE_INCLUDE_DIRECTORIES)
message(
  STATUS
    "ZXing
    include
    dirs:
    ${ZXINGdirs}
    ")

add_subdirectory(QRLiteLib)
add_subdirectory(QRLiteApp)
