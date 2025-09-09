# QRLite
An android app to make collages from pictures - No internet connection required, no ads, no machine learning, no tracking, no bloatware.

This app is built in with C++ using the Qt framework.

## Features

## Build Requirements

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
