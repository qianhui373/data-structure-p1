cmake_minimum_required(VERSION 3.9...3.19)
project(Project1 CXX)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
  # warning level 4 and all warnings as errors
  add_compile_options(/W4 /WX)
else()
  # lots of warnings and all warnings as errors
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()
  
# add cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# build test driver executable
add_executable(unit_tests catch.hpp unit_tests.cpp
  test_nintegrate.cpp
  nintegrate.cpp)

# enable testing
include(CTest)
enable_testing()

# register Catch tests with cmake
include(Catch)
catch_discover_tests(unit_tests)
