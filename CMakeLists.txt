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
option(SENTINEL_BUILD_TESTS "Build the test suite" OFF)
option(SENTINEL_BUILD_DOCS "Build the Doxygen documentation" OFF)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/platform/CMakeLists.txt")
  add_subdirectory(platform)
else()
  message(STATUS "sentinel-platform is missing, fetching it into ${CMAKE_CURRENT_SOURCE_DIR}/platform")

  FetchContent_Declare(sentinel_platform
    GIT_REPOSITORY "https://github.com/KodkodFPV/sentinel-platform.git"
    GIT_TAG        main
    SOURCE_DIR     "${CMAKE_CURRENT_SOURCE_DIR}/platform"
  )

  FetchContent_MakeAvailable(sentinel_platform)
endif()

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
