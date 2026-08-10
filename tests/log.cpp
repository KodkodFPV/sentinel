#include <catch2/catch_test_macros.hpp>

#include "sentinel/log.hpp"


namespace
{
  bool tracked(bool value, int& calls)
  {
    ++calls;
    return value;
  }

  const char* trackedMessage(int& calls)
  {
    ++calls;
    return "message";
  }
}

TEST_CASE("sentinel log macros evaluate message expressions", "[log]")
{
  int calls{};

  LOG_ERROR("test", trackedMessage(calls));
  LOG_WARNING("test", trackedMessage(calls));
  LOG_INFO("test", trackedMessage(calls));

  REQUIRE(calls == 3);
}

TEST_CASE("sentinel log failure macros evaluate values once", "[log]")
{
  int calls{};

  LOG_ERROR_FAILURE("test", tracked(false, calls));
  LOG_WARNING_FAILURE("test", tracked(false, calls));
  LOG_INFO_FAILURE("test", tracked(false, calls));

  REQUIRE(calls == 3);
}

TEST_CASE("sentinel log on failure macros evaluate successful calls once", "[log]")
{
  int calls{};

  LOG_ERROR_ON_FAILURE("test", tracked(true, calls));
  LOG_WARNING_ON_FAILURE("test", tracked(true, calls));
  LOG_INFO_ON_FAILURE("test", tracked(true, calls));

  REQUIRE(calls == 3);
}

TEST_CASE("sentinel log on failure macros evaluate failed calls once", "[log]")
{
  int calls{};

  LOG_ERROR_ON_FAILURE("test", tracked(false, calls));
  LOG_WARNING_ON_FAILURE("test", tracked(false, calls));
  LOG_INFO_ON_FAILURE("test", tracked(false, calls));

  REQUIRE(calls == 3);
}

TEST_CASE("sentinel formatted log macros compile and evaluate failure calls", "[log]")
{
  int calls{};

  LOG_ERROR_FMT("test", "value %d", 1);
  LOG_WARNING_FMT("test", "value %d", 2);
  LOG_INFO_FMT("test", "value %d", 3);

  LOG_ERROR_FAILURE_FMT("test", tracked(false, calls), "value %d", 4);
  LOG_WARNING_FAILURE_FMT("test", tracked(false, calls), "value %d", 5);
  LOG_INFO_FAILURE_FMT("test", tracked(false, calls), "value %d", 6);

  LOG_ERROR_ON_FAILURE_FMT("test", tracked(false, calls), "value %d", 7);
  LOG_WARNING_ON_FAILURE_FMT("test", tracked(false, calls), "value %d", 8);
  LOG_INFO_ON_FAILURE_FMT("test", tracked(false, calls), "value %d", 9);

  REQUIRE(calls == 6);
}

TEST_CASE("sentinel ISR log macros compile and evaluate calls", "[log]")
{
  int calls{};

  LOG_ERROR_ISR("test", trackedMessage(calls));
  LOG_WARNING_ISR("test", trackedMessage(calls));
  LOG_INFO_ISR("test", trackedMessage(calls));

  LOG_ERROR_FAILURE_ISR("test", tracked(false, calls));
  LOG_WARNING_FAILURE_ISR("test", tracked(false, calls));
  LOG_INFO_FAILURE_ISR("test", tracked(false, calls));

  LOG_ERROR_ON_FAILURE_ISR("test", tracked(false, calls));
  LOG_WARNING_ON_FAILURE_ISR("test", tracked(false, calls));
  LOG_INFO_ON_FAILURE_ISR("test", tracked(false, calls));

  REQUIRE(calls == 9);
}
