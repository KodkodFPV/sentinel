#pragma once

#include <cstdint>

#include "sentinel/error_traits.hpp"


namespace sentinel::test
{
  enum class PlainError : std::uint8_t
  {
    Ok      = 0x00,
    Failure = 0x2A,
  };

  inline const char* strerr(PlainError err)
  {
    switch (err)
    {
      case PlainError::Ok:
        return "ok";
      case PlainError::Failure:
        return "failure";
    }

    return "unknown";
  }

  struct TraitError
  {
    std::int32_t code{};
  };
}

namespace sentinel
{
  template <>
    struct error_traits<test::TraitError>
    {
      static bool failed(test::TraitError err)
      {
        return err.code != 0;
      }

      static const char* message(test::TraitError err)
      {
        return err.code == 0 ? "ok" : "trait failure";
      }

      static std::int32_t value(test::TraitError err)
      {
        return err.code;
      }
    };
}
