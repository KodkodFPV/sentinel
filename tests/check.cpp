#include <catch2/catch_test_macros.hpp>

#include <cstdint>
#include <expected>
#include <memory>
#include <optional>
#include <system_error>
#include <type_traits>

#include "sentinel/detail/check_core.hpp"

#include "support/types.hpp"


namespace
{
  template <class T>
    concept Checkable = requires(T value)
    {
      sentinel::detail::failed(value);
    };

  enum class RawEnumError : std::uint8_t
  {
    Ok      = 0x00,
    Failure = 0x01,
  };

  enum class SignedEnumError : std::int8_t
  {
    Ok       = 0,
    Negative = -1,
    Positive = 1,
  };

  static_assert(Checkable<bool>);
  static_assert(Checkable<RawEnumError>);
  static_assert(Checkable<SignedEnumError>);
  static_assert(Checkable<sentinel::test::TraitError>);
  static_assert(Checkable<const sentinel::test::TraitError&>);
  static_assert(Checkable<std::expected<void, std::error_code>>);
  static_assert(!Checkable<int>);
  static_assert(!Checkable<unsigned>);
}

TEST_CASE("sentinel::detail::failed checks plain values", "[check]")
{
  REQUIRE(sentinel::detail::failed(false));
  REQUIRE_FALSE(sentinel::detail::failed(true));

  REQUIRE_FALSE(sentinel::detail::failed(RawEnumError::Ok));
  REQUIRE(sentinel::detail::failed(RawEnumError::Failure));

  REQUIRE_FALSE(sentinel::detail::failed(SignedEnumError::Ok));
  REQUIRE(sentinel::detail::failed(SignedEnumError::Negative));
  REQUIRE(sentinel::detail::failed(SignedEnumError::Positive));

  REQUIRE_FALSE(sentinel::detail::failed(sentinel::test::TraitError{0}));
  REQUIRE(sentinel::detail::failed(sentinel::test::TraitError{42}));

  const auto traitOk      = sentinel::test::TraitError{0};
  const auto traitFailure = sentinel::test::TraitError{42};

  REQUIRE_FALSE(sentinel::detail::failed(traitOk));
  REQUIRE(sentinel::detail::failed(traitFailure));
}

TEST_CASE("sentinel::detail::failed checks pointer-like values", "[check]")
{
  int value{};
  int* ptr{&value};
  int* nullPtr{};

  REQUIRE_FALSE(sentinel::detail::failed(ptr));
  REQUIRE(sentinel::detail::failed(nullPtr));
  REQUIRE(sentinel::detail::failed(nullptr));

  REQUIRE_FALSE(sentinel::detail::failed(std::make_unique<int>(1)));
  REQUIRE(sentinel::detail::failed(std::unique_ptr<int>{}));

  REQUIRE_FALSE(sentinel::detail::failed(std::make_shared<int>(1)));
  REQUIRE(sentinel::detail::failed(std::shared_ptr<int>{}));
}

TEST_CASE("sentinel::detail::failed checks optional and error containers", "[check]")
{
  REQUIRE_FALSE(sentinel::detail::failed(std::optional<int>{1}));
  REQUIRE(sentinel::detail::failed(std::optional<int>{}));

  REQUIRE_FALSE(sentinel::detail::failed(std::error_code{}));
  REQUIRE(sentinel::detail::failed(std::make_error_code(std::errc::invalid_argument)));

  REQUIRE_FALSE(sentinel::detail::failed(std::expected<int, std::error_code>{7}));
  REQUIRE(sentinel::detail::failed(std::expected<int, std::error_code>{std::unexpected(std::make_error_code(std::errc::io_error))}));

  REQUIRE_FALSE(sentinel::detail::failed(std::expected<void, std::error_code>{}));
  REQUIRE(sentinel::detail::failed(std::expected<void, std::error_code>{std::unexpected(std::make_error_code(std::errc::io_error))}));

  REQUIRE(sentinel::detail::failed(std::unexpected(std::make_error_code(std::errc::io_error))));
}
