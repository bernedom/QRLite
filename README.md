# QRLite
An android app to make collages from pictures - No internet connection required, no ads, no machine learning, no tracking, no bloatware.

This app is built in with C++ using the Qt framework.

## Features

## Development environment

This project ships a [devcontainer](https://containers.dev/) configuration (`.devcontainer/devcontainer.json`).
The container is based on the [`bernedom/qtandroidbuilder`](https://hub.docker.com/r/bernedom/qtandroidbuilder) image, which comes pre-installed with Qt 6, the Android NDK & SDK, Conan 2, CMake, and Ninja.

Opening the project in VS Code with the [Dev Containers extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) is the recommended way to get a fully working build environment without any manual setup.

## Build Requirements

* conan2 as dependency manager
* cmake 3.24 or newer
* ninja (if using the ninja generator)
* Android NDK & SDK (if building for android)

> **Note – git submodules:** This project uses `cmake-conan` as a git submodule.
> When cloning, make sure to initialise it:
>
> ```
> git clone --recurse-submodules <repo-url>
> ```
>
> Or, if you have already cloned without submodules:
>
> ```
> git submodule update --init --recursive
> ```

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

Use `cmake --list-presets` to see all available build presets.

**Desktop (Linux):**

```
cmake --preset ci-ninja-desktop-debug
cmake --build build
```

**Android (single ABI, e.g. arm64-v8a):**

```
cmake --preset ci-ninja-android-arm64-v8a-debug
cmake --build build_android_arm64-v8a
```

To build the Android APK explicitly, pass the `apk` target:

```
cmake --build build_android_arm64-v8a --target apk
```

Available Android ABI presets: `armeabi-v7a`, `arm64-v8a`, `x86_64`.
Replace `debug` with `release` for release builds.

### Running the android emulator

Install the system images for the android emulator using the sdkmanager then create an AVD using the avdmanager:

```
sudo /opt/android/cmdline-tools/cmdline-tools/bin/sdkmanager --install "system-images;android-33;google_apis;x86_64"
avdmanager create avd -n test -k "system-images;android-33;google_apis;x86_64"
```

Check <https://github.com/amrsa1/Android-Emulator-images> for more details.

Then start the emulator:

```
/opt/android/emulator/emulator -avd test
``` 

### Uploading and deploying to android play store

To upload the app to the play store, you need to generate a signed bundle or apk.

1. First generate a keystore if you do not have one already: `keytool -genkeypair -alias upload -keyalg RSA -keysize 2048 -validity 9125 -keystore upload-key.jks`
2. Export the public certificate from the keystore: `keytool -export -rfc -alias upload -file upload_certificate.pem -keystore upload-key.jks`
3. sign the aab `jarsigner -keystore ./upload-key.jks ./build_android_bundle/QRLiteApp/android-build/build/outputs/bundle/release/android-build-release.aab upload`
4. Verify the signature: `jarsigner -verify -verbose -certs ./build_android_bundle/QRLiteApp/android-build/build/outputs/bundle/release/android-build-release.aab

For CI/CD store the upload kez as base64 encoded secret and decode it during the workflow run:

```
base64 -w0 upload-key.jks > upload-key.jks.b64 
```

### Sign the apk

To sign the apk for release, use the following command:

```
apksigner sign --ks  upload-key.jks ./build_android_armeabi-v7a/QRLiteApp/android-build/QRLite.apk
```

## Backlog

* If permissions for camera are not (yet) granted, do not initialized camera

* Functionality to read QR codes from images
    * Select from gallery
    * select from file system
* Write QR codes (later)

## Tech enhancements
* Add benchmark for QR code reading
* Pull prebuilt artifacts from CI for multi-aab


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
    /opt/Qt/6.11.1/android_x86_64/bin/qt-cmake --preset ci-ninja-android-all-archs-debug
3. build using cmake

