cmake_minimum_required(VERSION 3.25)

include(Catch)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

add_executable(QRLiteTests)
target_link_libraries(QRLiteTests PRIVATE QRLite::QRLiteLib
                                          Catch2::Catch2WithMain)
target_sources(QRLiteTests PRIVATE src/test_assets.qrc src/project_test.cpp)

# add the include directory for the source code
target_include_directories(QRLiteTests
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)
target_compile_features(QRLiteTests PRIVATE cxx_std_20)

# add_test(NAME QRLiteUnitTests COMMAND QRLiteTests)
catch_discover_tests(QRLiteTests)
