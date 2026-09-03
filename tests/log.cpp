#include <cstdint>
#include <utility>
#include <cstdio>
#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include <sentinel/log.hpp>


namespace
{
  constexpr auto TestLogLineBufferSize = 256;

  struct CapturedLines
  {
    std::vector<std::string> lines;

    template <class... Args>
      void operator()(const char*, const char* format, Args&&... args)
      {
        char line[TestLogLineBufferSize]{};

        std::snprintf(line, sizeof(line), format, std::forward<Args>(args)...);
        lines.emplace_back(line);
      }
  };

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

  int trackedValue(int& calls)
  {
    ++calls;
    return 7;
  }
}

TEST_CASE("sentinel log macros evaluate message expressions", "[log]")
{
  int calls{};

  LOG_INFO("test", trackedMessage(calls));
  LOG_WARNING("test", trackedMessage(calls));
  LOG_ERROR("test", trackedMessage(calls));
  LOG_DEBUG("test", trackedMessage(calls));
  LOG_VERBOSE("test", trackedMessage(calls));

  REQUIRE(calls == 5);
}

TEST_CASE("sentinel log failure macros evaluate values once", "[log]")
{
  int calls{};

  LOG_INFO_FAILURE("test", tracked(false, calls));
  LOG_WARNING_FAILURE("test", tracked(false, calls));
  LOG_ERROR_FAILURE("test", tracked(false, calls));
  LOG_DEBUG_FAILURE("test", tracked(false, calls));
  LOG_VERBOSE_FAILURE("test", tracked(false, calls));

  REQUIRE(calls == 5);
}

TEST_CASE("sentinel log on failure macros evaluate successful calls once", "[log]")
{
  int calls{};

  LOG_INFO_ON_FAILURE("test", tracked(true, calls));
  LOG_WARNING_ON_FAILURE("test", tracked(true, calls));
  LOG_ERROR_ON_FAILURE("test", tracked(true, calls));
  LOG_DEBUG_ON_FAILURE("test", tracked(true, calls));
  LOG_VERBOSE_ON_FAILURE("test", tracked(true, calls));

  REQUIRE(calls == 5);
}

TEST_CASE("sentinel log on failure macros evaluate failed calls once", "[log]")
{
  int calls{};

  LOG_INFO_ON_FAILURE("test", tracked(false, calls));
  LOG_WARNING_ON_FAILURE("test", tracked(false, calls));
  LOG_ERROR_ON_FAILURE("test", tracked(false, calls));
  LOG_DEBUG_ON_FAILURE("test", tracked(false, calls));
  LOG_VERBOSE_ON_FAILURE("test", tracked(false, calls));

  REQUIRE(calls == 5);
}

TEST_CASE("sentinel formatted log macros compile and evaluate failure calls", "[log]")
{
  int calls{};

  LOG_INFO("test", "value %d", 1);
  LOG_WARNING("test", "value %d", 2);
  LOG_ERROR("test", "value %d", 3);
  LOG_DEBUG("test", "value %d", 4);
  LOG_VERBOSE("test", "value %d", 5);

  LOG_INFO_FAILURE("test", tracked(false, calls), "value %d", 6);
  LOG_WARNING_FAILURE("test", tracked(false, calls), "value %d", 7);
  LOG_ERROR_FAILURE("test", tracked(false, calls), "value %d", 8);
  LOG_DEBUG_FAILURE("test", tracked(false, calls), "value %d", 9);
  LOG_VERBOSE_FAILURE("test", tracked(false, calls), "value %d", 10);

  LOG_INFO_ON_FAILURE("test", tracked(false, calls), "value %d", 11);
  LOG_WARNING_ON_FAILURE("test", tracked(false, calls), "value %d", 12);
  LOG_ERROR_ON_FAILURE("test", tracked(false, calls), "value %d", 13);
  LOG_DEBUG_ON_FAILURE("test", tracked(false, calls), "value %d", 14);
  LOG_VERBOSE_ON_FAILURE("test", tracked(false, calls), "value %d", 15);

  REQUIRE(calls == 10);
}

TEST_CASE("sentinel direct log macros evaluate variadic arguments according to silent mode", "[log]")
{
  int formatCalls{};
  int valueCalls{};

  LOG_INFO("test", trackedMessage(formatCalls), trackedValue(valueCalls));
  LOG_WARNING("test", trackedMessage(formatCalls), trackedValue(valueCalls));
  LOG_ERROR("test", trackedMessage(formatCalls), trackedValue(valueCalls));
  LOG_DEBUG("test", trackedMessage(formatCalls), trackedValue(valueCalls));
  LOG_VERBOSE("test", trackedMessage(formatCalls), trackedValue(valueCalls));

  REQUIRE(formatCalls == 5);

#if CHECKS_SILENT
  REQUIRE(valueCalls == 0);
#else
  REQUIRE(valueCalls == 5);
#endif
}

TEST_CASE("sentinel failure log macros evaluate additional message only when logging is enabled", "[log]")
{
  int valueCalls{};
  int formatCalls{};
  int argumentCalls{};

  LOG_INFO_FAILURE("test", tracked(false, valueCalls), trackedMessage(formatCalls), trackedValue(argumentCalls));
  LOG_WARNING_FAILURE("test", tracked(false, valueCalls), trackedMessage(formatCalls), trackedValue(argumentCalls));
  LOG_ERROR_FAILURE("test", tracked(false, valueCalls), trackedMessage(formatCalls), trackedValue(argumentCalls));
  LOG_DEBUG_FAILURE("test", tracked(false, valueCalls), trackedMessage(formatCalls), trackedValue(argumentCalls));
  LOG_VERBOSE_FAILURE("test", tracked(false, valueCalls), trackedMessage(formatCalls), trackedValue(argumentCalls));

  REQUIRE(valueCalls == 5);

#if CHECKS_SILENT
  REQUIRE(formatCalls == 0);
  REQUIRE(argumentCalls == 0);
#else
  REQUIRE(formatCalls == 5);
  REQUIRE(argumentCalls == 5);
#endif
}

TEST_CASE("sentinel conditional failure log macros skip additional message on success", "[log]")
{
  int callCalls{};
  int formatCalls{};
  int argumentCalls{};

  LOG_INFO_ON_FAILURE("test", tracked(true, callCalls), trackedMessage(formatCalls), trackedValue(argumentCalls));
  LOG_WARNING_ON_FAILURE("test", tracked(true, callCalls), trackedMessage(formatCalls), trackedValue(argumentCalls));
  LOG_ERROR_ON_FAILURE("test", tracked(true, callCalls), trackedMessage(formatCalls), trackedValue(argumentCalls));
  LOG_DEBUG_ON_FAILURE("test", tracked(true, callCalls), trackedMessage(formatCalls), trackedValue(argumentCalls));
  LOG_VERBOSE_ON_FAILURE("test", tracked(true, callCalls), trackedMessage(formatCalls), trackedValue(argumentCalls));

  REQUIRE(callCalls == 5);
  REQUIRE(formatCalls == 0);
  REQUIRE(argumentCalls == 0);
}

TEST_CASE("sentinel conditional failure log macros evaluate additional message only when logging is enabled", "[log]")
{
  int callCalls{};
  int formatCalls{};
  int argumentCalls{};

  LOG_INFO_ON_FAILURE("test", tracked(false, callCalls), trackedMessage(formatCalls), trackedValue(argumentCalls));
  LOG_WARNING_ON_FAILURE("test", tracked(false, callCalls), trackedMessage(formatCalls), trackedValue(argumentCalls));
  LOG_ERROR_ON_FAILURE("test", tracked(false, callCalls), trackedMessage(formatCalls), trackedValue(argumentCalls));
  LOG_DEBUG_ON_FAILURE("test", tracked(false, callCalls), trackedMessage(formatCalls), trackedValue(argumentCalls));
  LOG_VERBOSE_ON_FAILURE("test", tracked(false, callCalls), trackedMessage(formatCalls), trackedValue(argumentCalls));

  REQUIRE(callCalls == 5);

#if CHECKS_SILENT
  REQUIRE(formatCalls == 0);
  REQUIRE(argumentCalls == 0);
#else
  REQUIRE(formatCalls == 5);
  REQUIRE(argumentCalls == 5);
#endif
}

TEST_CASE("sentinel ISR log macros compile and evaluate calls", "[log]")
{
  int calls{};

  LOG_INFO_ISR("test", trackedMessage(calls));
  LOG_WARNING_ISR("test", trackedMessage(calls));
  LOG_ERROR_ISR("test", trackedMessage(calls));
  LOG_DEBUG_ISR("test", trackedMessage(calls));
  LOG_VERBOSE_ISR("test", trackedMessage(calls));

  LOG_INFO_FAILURE_ISR("test", tracked(false, calls));
  LOG_WARNING_FAILURE_ISR("test", tracked(false, calls));
  LOG_ERROR_FAILURE_ISR("test", tracked(false, calls));
  LOG_DEBUG_FAILURE_ISR("test", tracked(false, calls));
  LOG_VERBOSE_FAILURE_ISR("test", tracked(false, calls));

  LOG_INFO_ON_FAILURE_ISR("test", tracked(false, calls));
  LOG_WARNING_ON_FAILURE_ISR("test", tracked(false, calls));
  LOG_ERROR_ON_FAILURE_ISR("test", tracked(false, calls));
  LOG_DEBUG_ON_FAILURE_ISR("test", tracked(false, calls));
  LOG_VERBOSE_ON_FAILURE_ISR("test", tracked(false, calls));

  REQUIRE(calls == 15);
}

TEST_CASE("sentinel hexdump formatter emits grouped rows", "[log]")
{
  const std::uint8_t data[] = {
    0x48, 0x47, 0x49, 0x43, 0x00, 0x01, 0x20, 0x7E,
    0x7F, 0x80, 0xFF, 0x41, 0x42, 0x43, 0x44, 0x45,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F
  };

  CapturedLines log;

  sentinel::detail::log_hexdump(log, "test", "Firmware header", data, sizeof(data));

  REQUIRE(log.lines.size() == 3);
  REQUIRE(log.lines[0] == "Firmware header, size 32");
  REQUIRE(log.lines[1] == "          00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F  10 11 12 13 14 15 16 17  18 19 1A 1B 1C 1D 1E 1F");
  REQUIRE(log.lines[2] == "00000000: 48 47 49 43 00 01 20 7E  7F 80 FF 41 42 43 44 45  30 31 32 33 34 35 36 37  38 39 3A 3B 3C 3D 3E 3F  |HGIC.. ~ ...ABCDE 01234567 89:;<=>?|");
}

TEST_CASE("sentinel hexdump formatter pads incomplete rows", "[log]")
{
  const std::uint8_t data[] = {
    0x48, 0x00, 0x20, 0x7E, 0x7F, 0x41, 0x42, 0x43,
    0x44, 0x45
  };

  CapturedLines log;

  sentinel::detail::log_hexdump(log, "test", "Short data", data, sizeof(data));

  REQUIRE(log.lines.size() == 3);

  auto asciiBegin = log.lines[2].find('|');
  REQUIRE(asciiBegin != std::string::npos);

  auto ascii = log.lines[2].substr(asciiBegin);
  auto prefix = std::string("|H. ~.ABC DE");

  REQUIRE(ascii.size() > prefix.size());
  REQUIRE(ascii.substr(0, prefix.size()) == prefix);

  auto paddingSize = ascii.size() - prefix.size() - 1;
  REQUIRE(ascii.substr(prefix.size(), paddingSize) == std::string(paddingSize, ' '));
  REQUIRE(ascii.back() == '|');
}

TEST_CASE("sentinel hexdump formatter handles empty and null data", "[log]")
{
  CapturedLines emptyLog;

  sentinel::detail::log_hexdump(emptyLog, "test", "Empty data", nullptr, 0);

  REQUIRE(emptyLog.lines.size() == 1);
  REQUIRE(emptyLog.lines[0] == "Empty data, size 0");

  CapturedLines nullLog;

  sentinel::detail::log_hexdump(nullLog, "test", "Null data", nullptr, 4);

  REQUIRE(nullLog.lines.size() == 2);
  REQUIRE(nullLog.lines[0] == "Null data, size 4");
  REQUIRE(nullLog.lines[1] == "          <null>");
}

TEST_CASE("sentinel hexdump formatter emits multiple rows and aligned final row", "[log]")
{
  const std::uint8_t data[] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27
  };

  CapturedLines log;

  sentinel::detail::log_hexdump(log, "test", "Two rows", data, sizeof(data));

  REQUIRE(log.lines.size() == 4);
  REQUIRE(log.lines[2] == "00000000: 00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F  10 11 12 13 14 15 16 17  18 19 1A 1B 1C 1D 1E 1F  |........ ........ ........ ........|");

  auto finalASCIIBegin = log.lines[3].find('|');
  auto finalASCIIEnd   = log.lines[3].rfind('|');
  auto finalHEXPrefix  = std::string{"00000020: 20 21 22 23 24 25 26 27"};

  REQUIRE(log.lines[3].substr(0, finalHEXPrefix.size()) == finalHEXPrefix);
  REQUIRE(finalASCIIBegin != std::string::npos);
  REQUIRE(finalASCIIEnd != std::string::npos);
  REQUIRE(finalASCIIEnd > finalASCIIBegin);

  auto finalASCII = log.lines[3].substr(finalASCIIBegin + 1, finalASCIIEnd - finalASCIIBegin - 1);

  REQUIRE(finalASCII.size() == 35);
  REQUIRE(finalASCII.substr(0, 8) == " !\"#$%&'");
  REQUIRE(finalASCII.substr(8) == std::string(27, ' '));
}

TEST_CASE("sentinel hexdump log macros compile", "[log]")
{
  const std::uint8_t data[] = {0x48, 0x47, 0x49, 0x43};

  LOG_HEXDUMP_INFO("test", "data", data, sizeof(data));
  LOG_HEXDUMP_WARNING("test", "data", data, sizeof(data));
  LOG_HEXDUMP_ERROR("test", "data", data, sizeof(data));
  LOG_HEXDUMP_DEBUG("test", "data", data, sizeof(data));
  LOG_HEXDUMP_VERBOSE("test", "data", data, sizeof(data));

  LOG_HEXDUMP_INFO_ISR("test", "data", data, sizeof(data));
  LOG_HEXDUMP_WARNING_ISR("test", "data", data, sizeof(data));
  LOG_HEXDUMP_ERROR_ISR("test", "data", data, sizeof(data));
  LOG_HEXDUMP_DEBUG_ISR("test", "data", data, sizeof(data));
  LOG_HEXDUMP_VERBOSE_ISR("test", "data", data, sizeof(data));
}
