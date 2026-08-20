#pragma once

/**
 * @file
 * @ingroup sentinel_detail
 * @internal
 *
 * @brief Internal failure detection overload set.
 */

#include <memory>
#include <concepts>
#include <type_traits>
#include <system_error>
#include <optional>
#include <expected>

#include "sentinel/error_traits.hpp"


namespace sentinel::detail
{
  /**
   * @ingroup sentinel_detail
   * @internal
   *
   * @brief Treats `false` as failure.
   *
   * @param value Boolean check result.
   *
   * @return `true` when `value` is `false`; otherwise `false`.
   */
  inline bool failed(bool value)
  {
    return !value;
  }

  /**
   * @ingroup sentinel_detail
   * @internal
   *
   * @brief Treats `nullptr` as failure.
   *
   * @return Always `true`.
   */
  inline bool failed(std::nullptr_t)
  {
    return true;
  }

  /**
   * @ingroup sentinel_detail
   * @internal
   *
   * @brief Treats a null raw pointer as failure.
   *
   * @tparam T Pointee type.
   *
   * @param ptr Pointer to check.
   *
   * @return `true` when `ptr` is null; otherwise `false`.
   */
  template <class T>
    inline bool failed(T* ptr)
    {
      return ptr == nullptr;
    }

  /**
   * @ingroup sentinel_detail
   * @internal
   *
   * @brief Treats an empty `std::unique_ptr` as failure.
   *
   * @tparam T Pointee type.
   * @tparam D Deleter type.
   *
   * @param ptr Pointer to check.
   *
   * @return `true` when `ptr` is empty; otherwise `false`.
   */
  template <class T, class D>
    inline bool failed(const std::unique_ptr<T, D>& ptr)
    {
      return ptr == nullptr;
    }

  /**
   * @ingroup sentinel_detail
   * @internal
   *
   * @brief Treats an empty `std::shared_ptr` as failure.
   *
   * @tparam T Pointee type.
   *
   * @param ptr Pointer to check.
   *
   * @return `true` when `ptr` is empty; otherwise `false`.
   */
  template <class T>
    inline bool failed(const std::shared_ptr<T>& ptr)
    {
      return ptr == nullptr;
    }

  /**
   * @ingroup sentinel_detail
   * @internal
   *
   * @brief Treats a plain enum as failure when its underlying value is non-zero.
   *
   * @tparam T Enum type without `sentinel::error_traits<T>`.
   *
   * @param value Enum value to check.
   *
   * @return `true` when the enum underlying value is non-zero; otherwise `false`.
   */
  template <class T> requires std::is_enum_v<T> && (!ErrorTraits<T>)
    inline bool failed(T value)
    {
      return static_cast<std::underlying_type_t<T>>(value) != 0;
    }

  /**
   * @ingroup sentinel_detail
   * @internal
   *
   * @brief Delegates failure detection to `sentinel::error_traits<T>`.
   *
   * @tparam T Type adapted by `sentinel::error_traits<T>`.
   *
   * @param value Status value to check.
   *
   * @return Result of `sentinel::error_traits<T>::failed(value)`.
   */
  template <class T> requires ErrorTraits<T>
    inline bool failed(T value)
    {
      return sentinel::error_traits<std::remove_cvref_t<T>>::failed(value);
    }

  /**
   * @ingroup sentinel_detail
   * @internal
   *
   * @brief Rejects plain integral status values without explicit `error_traits`.
   *
   * @tparam T Integral type without `sentinel::error_traits<T>`.
   */
  template <class T> requires std::is_integral_v<T> && (!std::same_as<std::remove_cvref_t<T>, bool>) && (!ErrorTraits<T>)
    inline bool failed(T) = delete;

  /**
   * @ingroup sentinel_detail
   * @internal
   *
   * @brief Treats an empty `std::optional` as failure.
   *
   * @tparam T Stored value type.
   *
   * @param value Optional value to check.
   *
   * @return `true` when `value` has no stored value; otherwise `false`.
   */
  template <class T>
    inline bool failed(const std::optional<T>& value)
    {
      return !value.has_value();
    }

  /**
   * @ingroup sentinel_detail
   * @internal
   *
   * @brief Treats a non-empty `std::error_code` as failure.
   *
   * @param err Error code to check.
   *
   * @return `true` when `err` contains an error; otherwise `false`.
   */
  inline bool failed(const std::error_code& err)
  {
    return static_cast<bool>(err);
  }

  /**
   * @ingroup sentinel_detail
   * @internal
   *
   * @brief Treats an `std::expected` without a value as failure.
   *
   * @tparam T Expected value type.
   * @tparam E Error value type.
   *
   * @param value Expected value to check.
   *
   * @return `true` when `value` contains an error; otherwise `false`.
   */
  template <class T, class E>
    inline bool failed(const std::expected<T, E>& value)
    {
      return !value.has_value();
    }

  /**
   * @ingroup sentinel_detail
   * @internal
   *
   * @brief Treats any `std::unexpected` as failure.
   *
   * @tparam E Error value type.
   *
   * @return Always `true`.
   */
  template <class E>
    inline bool failed(const std::unexpected<E>&)
    {
      return true;
    }
}
