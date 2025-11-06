# QRLite
An android app to make collages from pictures - No internet connection required, no ads, no machine learning, no tracking, no bloatware.

This app is built in with C++ using the Qt framework.

## Features

## Build Requirements

* conan2 as dependency manager
* cmake 3.24 or newer
* ninja (if using the ninja generator)
* Android NDK & SDK (if building for android)

Conan Profiles supported in the devcontainer:

Desktop (Linux):
```
[settings]
arch=x86_64
build_type=Release
compiler=gcc
compiler.cppstd=gnu17
compiler.libcxx=libstdc++11
compiler.version=13
os=Linux
```

Android 
```
[settings]
arch=x86_64
build_type=Release
compiler=clang
compiler.cppstd=gnu17
compiler.libcxx=libstdc++11
compiler.version=18
os=Linux
```
### Dependencies

* Qt 6
* Android NDK & SDK
* zxing-cpp
* Catch2 (for unit tests)

This project uses conan as a dependency provider for CMake. Please refer to the [conan documentation](https://docs.conan.io/en/latest/) for installation instructions.

### Build instructions

Use `cmake --list-presets` to see available build presets.

```
cmake --preset Ninja-Debug
cmake --build --preset Ninja-Debug
``` 

To build the android apk built the target `apk`:

```
cmake --build --preset Ninja-Debug --target apk
```

### Running the android emulator

Install the system images for the android emulator using the sdkmanager then create an AVD using the avdmanager:

```
sudo /opt/android/cmdline-tools/cmdline-tools/bin/sdkmanager --install "system-images;android-33;google_apis;x86_64"
avdmanager create avd -n test -k "system-images;android-33;google_apis;x86_64"
```

Check <https://github.com/amrsa1/Android-Emulator-images> for more details.

Then start the emulator:

```

## Backlog

* Configure AndroidManifest.xml for correct permissions
* If permissions for camera are not (yet) granted, do not initialized camera

* Functionality to read QR codes from images
    * Select from gallery
    * select from file system
* Write QR codes (later)

## Tech enhancements
* Add benchmark for QR code reading


### Extended features for later releases

* Sanity checks for urls etc
* Auto detect types like WLAN access, vCard, mailto, ...
* Open proper app for detected types
* allow to select camera
* turn on/off flashlight

## build multi arch android aab

1. configure all individual archs in debug mode:
    1. cmake --preset ci-ninja-android-armeabi-v7a-debug
    2. cmake --preset ci-ninja-android-arm64-v8a-debug
    3. cmake --preset ci-ninja-android-x86_64-debug
2. build all individual archs in debug mode:
    1. cmake --build ./build_android_armeabi-v7a
    2. cmake --build ./build_android_arm64-v8a
    3. cmake --build ./build_android_x86_64
2. collect all archs bundle in debug mode using qt-cmake
    /opt/Qt/6.6.1/android_x86_64/bin/qt-cmake --preset ci-ninja-android-all-archs-debug
3. build using cmake

