#include <catch2/catch_test_macros.hpp>

#include <cinttypes>
#include <cstdio>
#include <expected>
#include <optional>
#include <string>
#include <system_error>
#include <utility>
#include <vector>

#include "sentinel/detail/check_core.hpp"
#include "sentinel/detail/log_core.hpp"

#include "support/types.hpp"


namespace
{
  constexpr auto TestLogLineBufferSize = 256;

  struct CapturedLog
  {
    std::vector<std::string> tags;
    std::vector<std::string> formats;
    std::vector<std::string> messages;

    template <class... Args>
      void operator()(const char* tag, const char* format, Args&&... args)
      {
        char message[TestLogLineBufferSize]{};

        std::snprintf(message, sizeof(message), format, std::forward<Args>(args)...);

        tags.emplace_back(tag);
        formats.emplace_back(format);
        messages.emplace_back(message);
      }
  };
}

TEST_CASE("sentinel error_traits controls failure detection", "[error_traits]")
{
  REQUIRE_FALSE(sentinel::detail::failed(sentinel::test::TraitError{0}));
  REQUIRE(sentinel::detail::failed(sentinel::test::TraitError{7}));
}

TEST_CASE("sentinel error_traits controls log value and message", "[error_traits]")
{
  CapturedLog log;

  sentinel::detail::log_failed(log, "test", "function", 123, "call()", sentinel::test::TraitError{7});

  REQUIRE(log.messages.size() == 1);
  REQUIRE(log.tags[0] == "test");
  REQUIRE(log.formats[0] == "%s(%d): call %s error 0x%04" PRIX32 " [%s]");
  REQUIRE(log.messages[0] == "function(123): call call() error 0x0007 [trait failure]");
}

TEST_CASE("plain enum errors are still supported through ADL strerr", "[error_traits]")
{
  CapturedLog log;

  sentinel::detail::log_failed(log, "test", "function", 123, "call()", sentinel::test::PlainError::Failure);

  REQUIRE(log.messages.size() == 1);
  REQUIRE(log.formats[0] == "%s(%d): call %s error 0x%04" PRIX32 " [%s]");
  REQUIRE(log.messages[0] == "function(123): call call() error 0x002A [failure]");
}

TEST_CASE("sentinel log_failed formats check-like values", "[error_traits]")
{
  CapturedLog log;

  int value{};
  sentinel::detail::log_failed(log, "test", "function", 10, "false", false);
  sentinel::detail::log_failed(log, "test", "function", 11, "ptr", static_cast<int*>(nullptr));
  sentinel::detail::log_failed(log, "test", "function", 12, "nullptr", nullptr);
  sentinel::detail::log_failed(log, "test", "function", 13, "optional", std::optional<int>{});
  sentinel::detail::log_failed(log, "test", "function", 14, "ptr", &value);

  REQUIRE(log.messages.size() == 5);
  REQUIRE(log.messages[0] == "function(10): check false");
  REQUIRE(log.messages[1] == "function(11): check ptr");
  REQUIRE(log.messages[2] == "function(12): check nullptr");
  REQUIRE(log.messages[3] == "function(13): check optional");
  REQUIRE(log.messages[4] == "function(14): check ptr");
}

TEST_CASE("sentinel log_failed formats std error containers", "[error_traits]")
{
  CapturedLog log;

  auto err        = std::make_error_code(std::errc::invalid_argument);
  auto expected   = std::expected<int, std::error_code>{std::unexpected(err)};
  auto unexpected = std::unexpected(err);

  sentinel::detail::log_failed(log, "test", "function", 20, "err", err);
  sentinel::detail::log_failed(log, "test", "function", 21, "expected", expected);
  sentinel::detail::log_failed(log, "test", "function", 22, "unexpected", unexpected);

  REQUIRE(log.messages.size() == 3);

  char errPrefix[TestLogLineBufferSize]{};
  char expectedPrefix[TestLogLineBufferSize]{};
  char unexpectedPrefix[TestLogLineBufferSize]{};

  std::snprintf(errPrefix, sizeof(errPrefix), "function(20): call err error %s:0x%04" PRIX32 " [", err.category().name(), static_cast<std::uint32_t>(err.value()));
  std::snprintf(expectedPrefix, sizeof(expectedPrefix), "function(21): call expected error %s:0x%04" PRIX32 " [", err.category().name(), static_cast<std::uint32_t>(err.value()));
  std::snprintf(unexpectedPrefix, sizeof(unexpectedPrefix), "function(22): call unexpected error %s:0x%04" PRIX32 " [", err.category().name(), static_cast<std::uint32_t>(err.value()));

  REQUIRE(log.messages[0].find(errPrefix) == 0);
  REQUIRE(log.messages[1].find(expectedPrefix) == 0);
  REQUIRE(log.messages[2].find(unexpectedPrefix) == 0);
}

TEST_CASE("sentinel log_failed_fmt appends additional message after failure details", "[error_traits]")
{
  CapturedLog log;

  sentinel::detail::log_failed_fmt(log, "test", "function", 30, "call()", sentinel::test::TraitError{7}, "value %d", 42);

  REQUIRE(log.messages.size() == 2);
  REQUIRE(log.messages[0] == "function(30): call call() error 0x0007 [trait failure]");
  REQUIRE(log.messages[1] == "value 42");
}
