cmake_minimum_required(VERSION 3.21)

project(
  QRLiteApp
  VERSION 1.0.0
  LANGUAGES CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(ANDROID)
  message(STATUS "Configuring for multi-arch Android build")
  if(CMAKE_ANDROID_ARCH_ABI STREQUAL "armeabi-v7a")
    list(PREPEND CMAKE_PREFIX_PATH "${QT_PATH_ANDROID_ABI_armeabi-v7a}")
    list(PREPEND CMAKE_PREFIX_PATH "${CONAN_ARMEABI_V7A_DIR}")

  elseif(CMAKE_ANDROID_ARCH_ABI STREQUAL "arm64-v8a")
    list(PREPEND CMAKE_PREFIX_PATH "${QT_PATH_ANDROID_ABI_arm64-v8a}")
    list(PREPEND CMAKE_PREFIX_PATH "${CONAN_ARM64_DIR}")
  elseif(CMAKE_ANDROID_ARCH_ABI STREQUAL "x86_64")
    list(PREPEND CMAKE_PREFIX_PATH "${QT_PATH_ANDROID_ABI_x86_64}")
    list(PREPEND CMAKE_PREFIX_PATH "${CONAN_X86_64_DIR}")
  else()
    message(FATAL_ERROR "Unsupported ANDROID_ABI: ${CMAKE_ANDROID_ARCH_ABI}")
  endif()
endif()

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
