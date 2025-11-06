cmake_minimum_required(VERSION 3.21)

project(
  QRLite
  VERSION 1.0.0
  LANGUAGES CXX C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CONAN_ARM64_DIR)
  set(CONAN_ARM64_DIR "${CMAKE_SOURCE_DIR}/build_android_arm64-v8a/conan")
endif()
if(NOT CONAN_ARMEABI_V7A_DIR)
  set(CONAN_ARMEABI_V7A_DIR
      "${CMAKE_SOURCE_DIR}/build_android_armeabi-v7a/conan")
endif()
if(NOT CONAN_X86_64_DIR)
  set(CONAN_X86_64_DIR "${CMAKE_SOURCE_DIR}/build_android_x86_64/conan")
endif()

if(ANDROID)
  message(
    STATUS
      "Configuring for multi-arch Android build with ABIS: ${CMAKE_ANDROID_ARCH_ABI}"
  )
  set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE BOTH)
  if(CMAKE_ANDROID_ARCH_ABI STREQUAL "armeabi-v7a")
    list(PREPEND CMAKE_PREFIX_PATH "${QT_PATH_ANDROID_ABI_armeabi-v7a}")
    list(PREPEND CMAKE_PREFIX_PATH "${CONAN_ARMEABI_V7A_DIR}")
    list(PREPEND CMAKE_MODULE_PATH "${CONAN_ARMEABI_V7A_DIR}/cmake")
  elseif(CMAKE_ANDROID_ARCH_ABI STREQUAL "arm64-v8a")
    list(PREPEND CMAKE_PREFIX_PATH "${QT_PATH_ANDROID_ABI_arm64-v8a}")
    list(PREPEND CMAKE_PREFIX_PATH "${CONAN_ARM64_DIR}")
    list(PREPEND CMAKE_MODULE_PATH "${CONAN_ARM64_DIR}/cmake")
  elseif(CMAKE_ANDROID_ARCH_ABI STREQUAL "x86_64")
    list(PREPEND CMAKE_PREFIX_PATH "${QT_PATH_ANDROID_ABI_x86_64}")
    list(PREPEND CMAKE_PREFIX_PATH "${CONAN_X86_64_DIR}")
    list(PREPEND CMAKE_MODULE_PATH "${CONAN_X86_64_DIR}/cmake")

  else()
    message(FATAL_ERROR "Unsupported ANDROID_ABI: ${CMAKE_ANDROID_ARCH_ABI}")
  endif()
  message(STATUS "Manually add to prefix path ${CMAKE_PREFIX_PATH}")
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

message(
  STATUS
    "MODULE PATH ${CMAKE_MODULE_PATH} CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ${CMAKE_FIND_ROOT_PATH_MODE_PACKAGE}"
)
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
