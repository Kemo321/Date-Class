cmake_minimum_required(VERSION 3.10)
project(DateProject)

set(CMAKE_CXX_STANDARD 17)

# Include the directory where the headers are located
include_directories(${PROJECT_SOURCE_DIR}/src)

# Add your main project source files
add_library(DateLib src/Date.cpp)

if (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wno-deprecated-copy)
endif()

# Add Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Add the test executable
add_executable(DateTests tests/test_date.cpp)

# Link Google Test and your library
target_link_libraries(DateTests DateLib gtest_main)

include(GoogleTest)
gtest_discover_tests(DateTests)
