#include <optional>
#include <expected>
#include <system_error>

#include <catch2/catch_test_macros.hpp>

#include <sentinel/return.hpp>


namespace
{
  bool trackedBool(bool value, int& calls)
  {
    ++calls;
    return value;
  }

  std::error_code trackedError(bool fail, int& calls)
  {
    ++calls;

    if (fail)
      return std::make_error_code(std::errc::invalid_argument);

    return {};
  }

  std::expected<int, std::error_code> trackedExpected(bool fail, int& calls)
  {
    ++calls;

    if (fail)
      return std::unexpected(std::make_error_code(std::errc::io_error));

    return 7;
  }

  const char* trackedFormat(int& calls)
  {
    ++calls;
    return "value %d";
  }

  int trackedValue(int& calls)
  {
    ++calls;
    return 42;
  }

  void returnVoid(bool fail, int& calls)
  {
    RETURN_VOID_WITH_ERROR("test", trackedBool(!fail, calls));

    ++calls;
  }

  bool returnFalse(bool fail, int& calls)
  {
    RETURN_FALSE_WITH_WARNING("test", trackedBool(!fail, calls));

    return true;
  }

  std::optional<int> returnNullopt(bool fail, int& calls)
  {
    RETURN_NULLOPT_WITH_INFO("test", trackedBool(!fail, calls));

    return 7;
  }

  std::error_code returnSame(bool fail, int& calls)
  {
    RETURN_SAME_WITH_ERROR("test", trackedError(fail, calls));

    return {};
  }

  std::error_code returnOther(bool fail, int& calls)
  {
    RETURN_OTHER_WITH_WARNING("test", trackedBool(!fail, calls), std::make_error_code(std::errc::permission_denied));

    return {};
  }

  std::expected<int, std::error_code> returnSameUnexpected(bool fail, int& calls)
  {
    RETURN_SAME_UNEXPECTED_WITH_INFO("test", trackedError(fail, calls));

    return 7;
  }

  std::expected<int, std::error_code> returnOtherUnexpected(bool fail, int& calls)
  {
    RETURN_OTHER_UNEXPECTED_WITH_ERROR("test", trackedBool(!fail, calls), std::make_error_code(std::errc::permission_denied));

    return 7;
  }

  std::error_code returnErrorFromUnexpected(bool fail, int& calls)
  {
    RETURN_ERR_FROM_UNEXPECTED_WITH_WARNING("test", trackedExpected(fail, calls));

    return {};
  }

  std::expected<int, std::error_code> returnUnexpectedFromUnexpected(bool fail, int& calls)
  {
    RETURN_UNEXPECTED_FROM_UNEXPECTED_WITH_INFO("test", trackedExpected(fail, calls));

    return 7;
  }

  bool returnFalseFormatted(bool fail, int& callCalls, int& formatCalls, int& argumentCalls)
  {
    RETURN_FALSE_WITH_ERROR_FMT("test", trackedBool(!fail, callCalls), trackedFormat(formatCalls), trackedValue(argumentCalls));

    return true;
  }

  std::optional<int> returnNulloptFormatted(bool fail, int& callCalls, int& formatCalls, int& argumentCalls)
  {
    RETURN_NULLOPT_WITH_WARNING_FMT("test", trackedBool(!fail, callCalls), trackedFormat(formatCalls), trackedValue(argumentCalls));

    return 7;
  }

  std::error_code returnSameFormatted(bool fail, int& callCalls, int& formatCalls, int& argumentCalls)
  {
    RETURN_SAME_WITH_INFO_FMT("test", trackedError(fail, callCalls), trackedFormat(formatCalls), trackedValue(argumentCalls));

    return {};
  }

  std::expected<int, std::error_code> returnSameUnexpectedFormatted(bool fail, int& callCalls, int& formatCalls, int& argumentCalls)
  {
    RETURN_SAME_UNEXPECTED_WITH_ERROR_FMT("test", trackedError(fail, callCalls), trackedFormat(formatCalls), trackedValue(argumentCalls));

    return 7;
  }

  std::error_code returnErrorFromUnexpectedFormatted(bool fail, int& callCalls, int& formatCalls, int& argumentCalls)
  {
    RETURN_ERR_FROM_UNEXPECTED_WITH_WARNING_FMT("test", trackedExpected(fail, callCalls), trackedFormat(formatCalls), trackedValue(argumentCalls));

    return {};
  }

  std::expected<int, std::error_code> returnUnexpectedFromUnexpectedFormatted(bool fail, int& callCalls, int& formatCalls, int& argumentCalls)
  {
    RETURN_UNEXPECTED_FROM_UNEXPECTED_WITH_INFO_FMT("test", trackedExpected(fail, callCalls), trackedFormat(formatCalls), trackedValue(argumentCalls));

    return 7;
  }

  void checkFormattedEvaluationCounts(bool fail, int formatCalls, int argumentCalls)
  {
#if CHECKS_SILENT
    REQUIRE(formatCalls == 6);
    REQUIRE(argumentCalls == 0);
#else
    REQUIRE(formatCalls == (fail ? 6 : 0));
    REQUIRE(argumentCalls == (fail ? 6 : 0));
#endif
  }
}

TEST_CASE("sentinel return macros continue on success", "[return]")
{
  int calls{};

  returnVoid(false, calls);
  REQUIRE(calls == 2);

  calls = 0;
  REQUIRE(returnFalse(false, calls));
  REQUIRE(calls == 1);

  calls = 0;
  REQUIRE(returnNullopt(false, calls) == std::optional<int>{7});
  REQUIRE(calls == 1);

  calls = 0;
  REQUIRE_FALSE(returnSame(false, calls));
  REQUIRE(calls == 1);

  calls = 0;
  REQUIRE_FALSE(returnOther(false, calls));
  REQUIRE(calls == 1);

  calls = 0;
  REQUIRE(returnSameUnexpected(false, calls).value() == 7);
  REQUIRE(calls == 1);

  calls = 0;
  REQUIRE(returnOtherUnexpected(false, calls).value() == 7);
  REQUIRE(calls == 1);

  calls = 0;
  REQUIRE_FALSE(returnErrorFromUnexpected(false, calls));
  REQUIRE(calls == 1);

  calls = 0;
  REQUIRE(returnUnexpectedFromUnexpected(false, calls).value() == 7);
  REQUIRE(calls == 1);
}

TEST_CASE("sentinel return macros return requested value on failure", "[return]")
{
  int calls{};

  returnVoid(true, calls);
  REQUIRE(calls == 1);

  calls = 0;
  REQUIRE_FALSE(returnFalse(true, calls));
  REQUIRE(calls == 1);

  calls = 0;
  REQUIRE_FALSE(returnNullopt(true, calls).has_value());
  REQUIRE(calls == 1);

  calls = 0;
  REQUIRE(returnSame(true, calls) == std::make_error_code(std::errc::invalid_argument));
  REQUIRE(calls == 1);

  calls = 0;
  REQUIRE(returnOther(true, calls) == std::make_error_code(std::errc::permission_denied));
  REQUIRE(calls == 1);

  calls = 0;
  auto sameUnexpected = returnSameUnexpected(true, calls);
  REQUIRE_FALSE(sameUnexpected.has_value());
  REQUIRE(sameUnexpected.error() == std::make_error_code(std::errc::invalid_argument));
  REQUIRE(calls == 1);

  calls = 0;
  auto otherUnexpected = returnOtherUnexpected(true, calls);
  REQUIRE_FALSE(otherUnexpected.has_value());
  REQUIRE(otherUnexpected.error() == std::make_error_code(std::errc::permission_denied));
  REQUIRE(calls == 1);

  calls = 0;
  REQUIRE(returnErrorFromUnexpected(true, calls) == std::make_error_code(std::errc::io_error));
  REQUIRE(calls == 1);

  calls = 0;
  auto unexpectedFromUnexpected = returnUnexpectedFromUnexpected(true, calls);
  REQUIRE_FALSE(unexpectedFromUnexpected.has_value());
  REQUIRE(unexpectedFromUnexpected.error() == std::make_error_code(std::errc::io_error));
  REQUIRE(calls == 1);
}

TEST_CASE("sentinel formatted and ISR return macros compile", "[return]")
{
  auto test =
    []() -> bool
    {
      RETURN_FALSE_WITH_ERROR_FMT("test", true, "value %d", 1);
      RETURN_FALSE_WITH_ERROR_FMT_ISR("test", true, "value %d", 2);
      RETURN_FALSE_WITH_WARNING_FMT("test", true, "value %d", 3);
      RETURN_FALSE_WITH_WARNING_FMT_ISR("test", true, "value %d", 4);
      RETURN_FALSE_WITH_INFO_FMT("test", true, "value %d", 5);
      RETURN_FALSE_WITH_INFO_FMT_ISR("test", true, "value %d", 6);

      RETURN_FALSE_WITH_ERROR_ISR("test", true);
      RETURN_FALSE_WITH_WARNING_ISR("test", true);
      RETURN_FALSE_WITH_INFO_ISR("test", true);

      return true;
    };

  REQUIRE(test());
}

TEST_CASE("sentinel formatted return macros continue on success and evaluate messages by mode", "[return]")
{
  int callCalls{};
  int formatCalls{};
  int argumentCalls{};

  REQUIRE(returnFalseFormatted(false, callCalls, formatCalls, argumentCalls));
  REQUIRE(returnNulloptFormatted(false, callCalls, formatCalls, argumentCalls) == std::optional<int>{7});
  REQUIRE_FALSE(returnSameFormatted(false, callCalls, formatCalls, argumentCalls));
  REQUIRE(returnSameUnexpectedFormatted(false, callCalls, formatCalls, argumentCalls).value() == 7);
  REQUIRE_FALSE(returnErrorFromUnexpectedFormatted(false, callCalls, formatCalls, argumentCalls));
  REQUIRE(returnUnexpectedFromUnexpectedFormatted(false, callCalls, formatCalls, argumentCalls).value() == 7);

  REQUIRE(callCalls == 6);
  checkFormattedEvaluationCounts(false, formatCalls, argumentCalls);
}

TEST_CASE("sentinel formatted return macros return requested value on failure and evaluate messages by mode", "[return]")
{
  int callCalls{};
  int formatCalls{};
  int argumentCalls{};

  REQUIRE_FALSE(returnFalseFormatted(true, callCalls, formatCalls, argumentCalls));
  REQUIRE_FALSE(returnNulloptFormatted(true, callCalls, formatCalls, argumentCalls).has_value());
  REQUIRE(returnSameFormatted(true, callCalls, formatCalls, argumentCalls) == std::make_error_code(std::errc::invalid_argument));

  auto sameUnexpected = returnSameUnexpectedFormatted(true, callCalls, formatCalls, argumentCalls);
  REQUIRE_FALSE(sameUnexpected.has_value());
  REQUIRE(sameUnexpected.error() == std::make_error_code(std::errc::invalid_argument));

  REQUIRE(returnErrorFromUnexpectedFormatted(true, callCalls, formatCalls, argumentCalls) == std::make_error_code(std::errc::io_error));

  auto unexpectedFromUnexpected = returnUnexpectedFromUnexpectedFormatted(true, callCalls, formatCalls, argumentCalls);
  REQUIRE_FALSE(unexpectedFromUnexpected.has_value());
  REQUIRE(unexpectedFromUnexpected.error() == std::make_error_code(std::errc::io_error));

  REQUIRE(callCalls == 6);
  checkFormattedEvaluationCounts(true, formatCalls, argumentCalls);
}
