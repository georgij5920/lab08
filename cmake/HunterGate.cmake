# Minimal HunterGate-compatible entry point for the educational lab08 project.
# It keeps the public interface used in the laboratory work:
#   include("cmake/HunterGate.cmake")
#   HunterGate(URL ... SHA1 ... LOCAL)
#   hunter_add_package(GTest)
# In GitHub Actions the implementation below fetches GoogleTest with CMake
# FetchContent, so the project remains portable and easy to build.

include_guard(GLOBAL)

function(HunterGate)
  set(HUNTER_ENABLED ON CACHE BOOL "Hunter compatibility layer is enabled")
  set(_hunter_config "${CMAKE_CURRENT_LIST_DIR}/Hunter/config.cmake")
  if(EXISTS "${_hunter_config}")
    include("${_hunter_config}")
  endif()
endfunction()

function(hunter_config package_name)
  # Compatibility stub for custom Hunter configuration files.
  # The arguments are intentionally accepted and ignored because FetchContent
  # performs the actual dependency retrieval in this educational solution.
endfunction()

function(hunter_add_package package_name)
  if(package_name STREQUAL "GTest")
    include(FetchContent)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
    )
    FetchContent_MakeAvailable(googletest)
  else()
    message(STATUS "hunter_add_package(${package_name}) is registered by local Hunter config")
  endif()
endfunction()
