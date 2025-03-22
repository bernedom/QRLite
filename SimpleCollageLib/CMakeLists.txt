cmake_minimum_required(VERSION 3.21)

add_library(SimpleCollageLib STATIC )
add_library(SimpleCollage::SimpleCollageLib ALIAS SimpleCollageLib)
target_include_directories(SimpleCollageLib PUBLIC include)
target_sources(SimpleCollageLib PRIVATE src/blank.cpp)

if(Catch2_FOUND AND BUILD_TESTING)
    add_subdirectory(test)
endif()
