#include <catch2/catch_test_macros.hpp>

#include <string>
#include <string_view>

#include "sentinel/detail/check_core.hpp"
#include "sentinel/detail/log_core.hpp"

#include "support/types.hpp"


TEST_CASE("sentinel error_traits controls failure detection", "[error_traits]")
{
  REQUIRE_FALSE(sentinel::detail::failed(sentinel::test::TraitError{0}));
  REQUIRE(sentinel::detail::failed(sentinel::test::TraitError{7}));
}

TEST_CASE("sentinel error_traits controls log value and message", "[error_traits]")
{
  int calls{};
  std::string_view tag;
  std::string_view format;

  auto log =
    [&](const char* logTag, const char* logFormat, auto&&...)
    {
      ++calls;
      tag    = logTag;
      format = logFormat;
    };

  sentinel::detail::log_failed(log, "test", "function", 123, "call()", sentinel::test::TraitError{7});

  REQUIRE(calls == 1);
  REQUIRE(std::string{tag} == "test");
  REQUIRE(std::string{format} == "%s(%d): call %s error 0x%.4X [%s]");
}

TEST_CASE("plain enum errors are still supported through ADL strerr", "[error_traits]")
{
  int calls{};
  std::string_view format;

  auto log =
    [&](const char*, const char* logFormat, auto&&...)
    {
      ++calls;
      format = logFormat;
    };

  sentinel::detail::log_failed(log, "test", "function", 123, "call()", sentinel::test::PlainError::Failure);

  REQUIRE(calls == 1);
  REQUIRE(std::string{format} == "%s(%d): call %s error 0x%.4X [%s]");
}
