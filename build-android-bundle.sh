#!/bin/bash

cmake --preset ci-ninja-android-armeabi-v7a-debug
cmake --preset ci-ninja-android-arm64-v8a-debug
cmake --preset ci-ninja-android-x86_64-debug

cmake --build ./build_android_armeabi-v7a
cmake --build ./build_android_arm64-v8a
cmake --build ./build_android_x86_64

/opt/Qt/6.6.1/android_x86_64/bin/qt-cmake --preset ci-ninja-android-all-archs-debug

cmake --build ./build_android_bundle/ --target aab