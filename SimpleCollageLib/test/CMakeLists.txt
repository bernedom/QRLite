cmake_minimum_required(VERSION 3.25)

include(Catch)
add_executable(SimpleCollageTests)
target_link_libraries(SimpleCollageTests PRIVATE SimpleCollage::SimpleCollageLib Catch2::Catch2WithMain)
target_sources(SimpleCollageTests PRIVATE)

# add the include directory for the source code
target_include_directories(SimpleCollageTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)
target_compile_features(SimpleCollageTests PRIVATE cxx_std_20)

# add_test(NAME SimpleCollageUnitTests COMMAND SimpleCollageTests)
catch_discover_tests(SimpleCollageTests)