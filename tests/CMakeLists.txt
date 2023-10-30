include(FetchContent)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(compressTests 
  compressTests.cpp)

add_executable(findUniqueTests
  findUniqueTests.cpp)

target_link_libraries(compressTests
PRIVATE
  GTest::GTest
  compress_and_find_lib)

target_link_libraries(findUniqueTests
  PRIVATE
    GTest::GTest
    compress_and_find_lib)

add_test(compress_gtests compressTests)
add_test(compress_gtests findUniqueTests)