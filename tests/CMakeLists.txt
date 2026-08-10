include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.12.0
)

FetchContent_MakeAvailable(Catch2)

set(sentinel_test_sources
  check.cpp
  error_traits.cpp
  log.cpp
  return.cpp
)

function(add_sentinel_unit_test target)
  add_executable(${target}
    ${sentinel_test_sources}
  )

  target_link_libraries(${target}
    PRIVATE
      sentinel::sentinel
      Catch2::Catch2WithMain
  )

  target_compile_features(${target}
    PRIVATE
      cxx_std_23
  )

  target_compile_options(${target}
    PRIVATE
      $<$<CXX_COMPILER_ID:MSVC>:/Zc:preprocessor>
  )
endfunction()

add_sentinel_unit_test(sentinel.test.unit)
add_executable(sentinel::test::unit ALIAS sentinel.test.unit)

add_sentinel_unit_test(sentinel.test.silent)
add_executable(sentinel::test::silent ALIAS sentinel.test.silent)

target_compile_definitions(sentinel.test.silent
  PRIVATE
    CHECKS_SILENT=1
)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)

catch_discover_tests(sentinel.test.unit)
catch_discover_tests(sentinel.test.silent)
