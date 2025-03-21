cmake_minimum_required(VERSION 3.25)

include(Catch)
add_executable(HardRockTests)
target_link_libraries(HardRockTests PRIVATE HardRock::HardRockLib Catch2::Catch2WithMain)
target_sources(HardRockTests PRIVATE)

# add the include directory for the source code
target_include_directories(HardRockTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)
target_compile_features(HardRockTests PRIVATE cxx_std_20)

# add_test(NAME HardRockUnitTests COMMAND HardRockTests)
catch_discover_tests(HardRockTests)