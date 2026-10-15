cmake_minimum_required(VERSION 3.24)
project(MyTests)

# Find gtest via Conan-generated files
find_package(GTest REQUIRED)

add_executable(my_tests test.cpp)

# Link the Conan-provided targets
target_link_libraries(my_tests PRIVATE GTest::gtest GTest::gtest_main)

# Optional: Auto-discover tests for CTest
include(GoogleTest)
gtest_discover_tests(my_tests)   