cmake_minimum_required(VERSION 3.10)

include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.23.251.tar.gz"
    SHA1 "5659b15dc0884d4b03dbd95710e6a1fa0fc3258d"
    LOCAL
)

project(print VERSION 0.1.0.0 LANGUAGES CXX)

set(PRINT_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(PRINT_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(PRINT_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(PRINT_VERSION_TWEAK 0)
set(PRINT_VERSION ${PRINT_VERSION_MAJOR}.${PRINT_VERSION_MINOR}.${PRINT_VERSION_PATCH}.${PRINT_VERSION_TWEAK})
set(PRINT_VERSION_STRING "v${PRINT_VERSION}")

option(BUILD_TESTS "Build tests" OFF)
option(BUILD_COVERAGE "Build with coverage flags" OFF)

if(BUILD_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-O0 -g --coverage)
  add_link_options(--coverage)
endif()

add_subdirectory(formatter_lib)
add_subdirectory(formatter_ex_lib)
add_subdirectory(solver_lib)
add_subdirectory(print_lib)
add_subdirectory(hello_world_application)
add_subdirectory(solver_application)
add_subdirectory(demo)
add_subdirectory(banking)

if(BUILD_TESTS)
  enable_testing()

  hunter_add_package(GTest)
  if(NOT TARGET GTest::gtest_main)
    find_package(GTest CONFIG REQUIRED)
  endif()

  file(GLOB TEST_SOURCES CONFIGURE_DEPENDS tests/*.cpp)
  add_executable(check ${TEST_SOURCES})
  target_link_libraries(check PRIVATE banking::banking GTest::gtest_main GTest::gmock_main)
  target_compile_features(check PRIVATE cxx_std_14)

  include(GoogleTest)
  gtest_discover_tests(check)
  add_test(NAME check COMMAND check)
endif()

include(CPackConfig.cmake)
