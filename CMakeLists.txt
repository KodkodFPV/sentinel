cmake_minimum_required(VERSION 3.16)
project(sentinel VERSION 1.0.0 LANGUAGES CXX HOMEPAGE_URL "https://github.com/KodkodFPV/sentinel")

include(FetchContent)

add_library(sentinel INTERFACE)
add_library(sentinel::sentinel ALIAS sentinel)

target_compile_features(sentinel INTERFACE cxx_std_23)

target_include_directories(sentinel
  INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

set(SENTINEL_PLATFORM "none" CACHE STRING "Sentinel platform backend")
set(SENTINEL_PLATFORM_GIT_REPOSITORY "https://github.com/KodkodFPV/sentinel-platform.git" CACHE STRING "Sentinel platform git repository")
set(SENTINEL_PLATFORM_GIT_TAG "main" CACHE STRING "Sentinel platform git tag")

option(SENTINEL_BUILD_TESTS "Build the test suite" OFF)
option(SENTINEL_BUILD_DOCS "Build the Doxygen documentation" OFF)

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.hpp.in"
  "${CMAKE_CURRENT_SOURCE_DIR}/include/sentinel/version.hpp"
  @ONLY
)

message(STATUS "Resolving sentinel-platform with FetchContent")

FetchContent_Declare(sentinel_platform
  GIT_REPOSITORY "${SENTINEL_PLATFORM_GIT_REPOSITORY}"
  GIT_TAG        "${SENTINEL_PLATFORM_GIT_TAG}"
  SOURCE_DIR     "${CMAKE_CURRENT_SOURCE_DIR}/platform"
)

FetchContent_MakeAvailable(sentinel_platform)

set(sentinel_platform_target "sentinel::platform_${SENTINEL_PLATFORM}")

if(NOT TARGET ${sentinel_platform_target})
  message(FATAL_ERROR "Unsupported sentinel platform: ${SENTINEL_PLATFORM}")
endif()

target_link_libraries(sentinel
  INTERFACE
    ${sentinel_platform_target}
)

if(SENTINEL_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

if(SENTINEL_BUILD_DOCS)
  find_package(Doxygen REQUIRED)

  set(SENTINEL_DOXYGEN_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/docs")

  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in"
    "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
    @ONLY
  )

  add_custom_target(sentinel.docs
    COMMAND
      ${DOXYGEN_EXECUTABLE} "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
    WORKING_DIRECTORY
      "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT
      "Generating sentinel Doxygen documentation"
    VERBATIM
  )
endif()
