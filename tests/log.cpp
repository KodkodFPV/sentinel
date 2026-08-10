#include <catch2/catch_test_macros.hpp>

#include "sentinel/log.hpp"


namespace
{
  bool tracked(bool value, int& calls)
  {
    ++calls;
    return value;
  }
}

TEST_CASE("sentinel log macros evaluate call expressions", "[log]")
{
  int calls{};

  LOG_ERROR("test", tracked(false, calls));
  LOG_WARNING("test", tracked(false, calls));
  LOG_INFO("test", tracked(false, calls));

  REQUIRE(calls == 3);
}

TEST_CASE("sentinel log on error macros evaluate successful calls once", "[log]")
{
  int calls{};

  LOG_ERROR_ON_ERR("test", tracked(true, calls));
  LOG_WARNING_ON_ERR("test", tracked(true, calls));
  LOG_INFO_ON_ERR("test", tracked(true, calls));

  REQUIRE(calls == 3);
}

TEST_CASE("sentinel log on error macros evaluate failed calls once", "[log]")
{
  int calls{};

  LOG_ERROR_ON_ERR("test", tracked(false, calls));
  LOG_WARNING_ON_ERR("test", tracked(false, calls));
  LOG_INFO_ON_ERR("test", tracked(false, calls));

  REQUIRE(calls == 3);
}

TEST_CASE("sentinel formatted log macros evaluate call expressions", "[log]")
{
  int calls{};

  LOG_ERROR_FMT("test", tracked(false, calls), "value %d", 1);
  LOG_WARNING_FMT("test", tracked(false, calls), "value %d", 2);
  LOG_INFO_FMT("test", tracked(false, calls), "value %d", 3);

  LOG_ERROR_ON_ERR_FMT("test", tracked(false, calls), "value %d", 4);
  LOG_WARNING_ON_ERR_FMT("test", tracked(false, calls), "value %d", 5);
  LOG_INFO_ON_ERR_FMT("test", tracked(false, calls), "value %d", 6);

  REQUIRE(calls == 6);
}

TEST_CASE("sentinel ISR log macros compile and evaluate calls", "[log]")
{
  int calls{};

  LOG_ERROR_ISR("test", tracked(false, calls));
  LOG_WARNING_ISR("test", tracked(false, calls));
  LOG_INFO_ISR("test", tracked(false, calls));

  LOG_ERROR_ON_ERR_ISR("test", tracked(false, calls));
  LOG_WARNING_ON_ERR_ISR("test", tracked(false, calls));
  LOG_INFO_ON_ERR_ISR("test", tracked(false, calls));

  REQUIRE(calls == 6);
}
