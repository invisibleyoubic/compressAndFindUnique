cmake_minimum_required(VERSION 3.27)

project(compress_and_find)

enable_testing()

set(PROJECT_DIR ${CMAKE_SOURCE_DIR})
set(PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)
set(PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)

set(PROJECT_INCLUDES 
    ${PROJECT_INCLUDE_DIR}/compressor.hpp
    ${PROJECT_INCLUDE_DIR}/decompressor.hpp
    ${PROJECT_INCLUDE_DIR}/findUnique.hpp)

include_directories(${PROJECT_INCLUDE_DIR})

set(PROJECT_SOURCES 
    main.cpp
    ${PROJECT_SOURCE_DIR}/compressor.cpp
    ${PROJECT_SOURCE_DIR}/decompressor.cpp
    ${PROJECT_SOURCE_DIR}/findUnique.cpp)

add_subdirectory(${CMAKE_SOURCE_DIR}/tests)

add_executable(compress_and_find
    ${PROJECT_INCLUDES}
    ${PROJECT_SOURCES})

add_library(compress_and_find_lib
    ${PROJECT_INCLUDES}
    ${PROJECT_SOURCES})

target_include_directories(compress_and_find PUBLIC include)