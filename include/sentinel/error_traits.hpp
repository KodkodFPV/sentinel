#pragma once

/**
 * @file
 * @ingroup sentinel_traits
 *
 * @brief Extension point for platform-specific status types.
 */

#include <cstdint>
#include <type_traits>
#include <concepts>


namespace sentinel
{
  /**
   * @ingroup sentinel_traits
   *
   * @brief Adapts a status type to sentinel failure detection and failure logging.
   *
   * Specialize this template for platform or vendor status types whose success/failure
   * convention cannot be inferred safely by the generic checks.
   *
   * A specialization must provide:
   * - `static bool failed(T value)`;
   * - `static const char* message(T value)`;
   * - `static std::int32_t value(T value)`.
   *
   * @tparam T Status type being adapted.
   */
  template <class T>
    struct error_traits;
}

namespace sentinel::detail
{
  /**
   * @ingroup sentinel_detail
   * @internal
   *
   * @brief Detects whether `sentinel::error_traits<T>` provides the required adapter API.
   *
   * @tparam T Candidate status type.
   */
  template <class T>
    concept ErrorTraits =
      requires(std::remove_cvref_t<T> value)
      {
        { sentinel::error_traits<std::remove_cvref_t<T>>::failed(value) } -> std::convertible_to<bool>;
        { sentinel::error_traits<std::remove_cvref_t<T>>::message(value) } -> std::convertible_to<const char*>;
        { sentinel::error_traits<std::remove_cvref_t<T>>::value(value) } -> std::convertible_to<std::int32_t>;
      };
}
