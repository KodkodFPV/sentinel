#pragma once

/**
 * @file
 * @ingroup sentinel_detail
 * @internal
 *
 * @brief Internal formatting helpers for failure logging.
 */

#include <cinttypes>
#include <memory>
#include <type_traits>
#include <utility>
#include <concepts>
#include <system_error>
#include <optional>
#include <expected>

#include "sentinel/detail/check_core.hpp"
#include "sentinel/error_traits.hpp"


/**
 * @def SENTINEL_LOG_FUNCTION(log_function)
 * @ingroup sentinel_detail
 * @internal
 *
 * @brief Wraps a platform log function into a forwarding callable.
 *
 * @param log_function Platform logging function to call.
 *
 * @return A forwarding lambda that passes all arguments to `log_function`.
 */
#define SENTINEL_LOG_FUNCTION(log_function)                                        \
  [](auto&&... sentinel_log_args)                                                  \
  {                                                                                \
    log_function(std::forward<decltype(sentinel_log_args)>(sentinel_log_args)...); \
  }

namespace sentinel::detail
{
  inline constexpr std::uint32_t error_value_hex(std::int32_t value)
  {
    return static_cast<std::uint32_t>(value);
  }

  /**
   * @ingroup sentinel_detail
   * @internal
   *
   * @brief Detects plain enum-like errors that expose `strerr(value)`.
   *
   * @tparam T Candidate enum error type.
   */
  template <class T>
    concept PlainError =
      !ErrorTraits<T> &&
      std::is_enum_v<T> &&
      requires(T err)
      {
        { strerr(err) } -> std::convertible_to<const char*>;
      };

  /**
   * @ingroup sentinel_detail
   * @internal
   *
   * @brief Logs a failed boolean check.
   *
   * @tparam LogF Platform log callable type.
   *
   * @param log Platform log callable.
   * @param tag Platform log tag.
   * @param function Function name where the failure was detected.
   * @param line Source line where the failure was detected.
   * @param call Stringified expression that produced the failure.
   *
   * @note Returns no value.
   */
  template <class LogF>
    inline void log_failed(LogF&&       log,
                           const char*  tag,
                           const char*  function,
                           std::int32_t line,
                           const char*  call,
                           bool)
    {
      std::forward<LogF>(log)(tag, "%s(%d): check %s", function, line, call);
    }

  /**
   * @ingroup sentinel_detail
   * @internal
   *
   * @brief Logs a failed raw pointer check.
   *
   * @tparam LogF Platform log callable type.
   * @tparam T Pointee type.
   *
   * @param log Platform log callable.
   * @param tag Platform log tag.
   * @param function Function name where the failure was detected.
   * @param line Source line where the failure was detected.
   * @param call Stringified expression that produced the failure.
   *
   * @note Returns no value.
   */
  template <class LogF, class T>
    inline void log_failed(LogF&&       log,
                           const char*  tag,
                           const char*  function,
                           std::int32_t line,
                           const char*  call,
                           T*)
    {
      std::forward<LogF>(log)(tag, "%s(%d): check %s", function, line, call);
    }

  /**
   * @ingroup sentinel_detail
   * @internal
   *
   * @brief Logs a failed `nullptr` check.
   *
   * @tparam LogF Platform log callable type.
   *
   * @param log Platform log callable.
   * @param tag Platform log tag.
   * @param function Function name where the failure was detected.
   * @param line Source line where the failure was detected.
   * @param call Stringified expression that produced the failure.
   *
   * @note Returns no value.
   */
  template <class LogF>
    inline void log_failed(LogF&&       log,
                           const char*  tag,
                           const char*  function,
                           std::int32_t line,
                           const char*  call,
                           std::nullptr_t)
    {
      std::forward<LogF>(log)(tag, "%s(%d): check %s", function, line, call);
    }

  /**
   * @ingroup sentinel_detail
   * @internal
   *
   * @brief Logs a failed `std::unique_ptr` check.
   *
   * @tparam LogF Platform log callable type.
   * @tparam T Pointee type.
   * @tparam D Deleter type.
   *
   * @param log Platform log callable.
   * @param tag Platform log tag.
   * @param function Function name where the failure was detected.
   * @param line Source line where the failure was detected.
   * @param call Stringified expression that produced the failure.
   *
   * @note Returns no value.
   */
  template <class LogF, class T, class D>
    inline void log_failed(LogF&&       log,
                           const char*  tag,
                           const char*  function,
                           std::int32_t line,
                           const char*  call,
                           const std::unique_ptr<T, D>&)
    {
      std::forward<LogF>(log)(tag, "%s(%d): check %s", function, line, call);
    }

  /**
   * @ingroup sentinel_detail
   * @internal
   *
   * @brief Logs a failed `std::shared_ptr` check.
   *
   * @tparam LogF Platform log callable type.
   * @tparam T Pointee type.
   *
   * @param log Platform log callable.
   * @param tag Platform log tag.
   * @param function Function name where the failure was detected.
   * @param line Source line where the failure was detected.
   * @param call Stringified expression that produced the failure.
   *
   * @note Returns no value.
   */
  template <class LogF, class T>
    inline void log_failed(LogF&&                   log,
                           const char*              tag,
                           const char*              function,
                           std::int32_t             line,
                           const char*              call,
                           const std::shared_ptr<T>&)
    {
      std::forward<LogF>(log)(tag, "%s(%d): check %s", function, line, call);
    }

  /**
   * @ingroup sentinel_detail
   * @internal
   *
   * @brief Logs a failed `std::optional` check.
   *
   * @tparam LogF Platform log callable type.
   * @tparam T Stored value type.
   *
   * @param log Platform log callable.
   * @param tag Platform log tag.
   * @param function Function name where the failure was detected.
   * @param line Source line where the failure was detected.
   * @param call Stringified expression that produced the failure.
   *
   * @note Returns no value.
   */
  template <class LogF, class T>
    inline void log_failed(LogF&&       log,
                           const char*  tag,
                           const char*  function,
                           std::int32_t line,
                           const char*  call,
                           const std::optional<T>&)
    {
      std::forward<LogF>(log)(tag, "%s(%d): check %s", function, line, call);
    }

  /**
   * @ingroup sentinel_detail
   * @internal
   *
   * @brief Logs a plain enum error using `strerr(value)`.
   *
   * @tparam LogF Platform log callable type.
   * @tparam T Plain enum error type that satisfies `PlainError`.
   *
   * @param log Platform log callable.
   * @param tag Platform log tag.
   * @param function Function name where the failure was detected.
   * @param line Source line where the failure was detected.
   * @param call Stringified expression that produced the failure.
   * @param err Error value to format.
   *
   * @note Returns no value.
   */
  template <class LogF, PlainError T>
    inline void log_failed(LogF&&       log,
                           const char*  tag,
                           const char*  function,
                           std::int32_t line,
                           const char*  call,
                           T            err)
    {
      std::forward<LogF>(log)(tag,
                              "%s(%d): call %s error 0x%04" PRIX32 " [%s]",
                              function,
                              line,
                              call,
                              error_value_hex(static_cast<std::int32_t>(err)),
                              strerr(err));
    }

  /**
   * @ingroup sentinel_detail
   * @internal
   *
   * @brief Logs a trait-backed error using `sentinel::error_traits<T>`.
   *
   * @tparam LogF Platform log callable type.
   * @tparam T Error type adapted by `sentinel::error_traits<T>`.
   *
   * @param log Platform log callable.
   * @param tag Platform log tag.
   * @param function Function name where the failure was detected.
   * @param line Source line where the failure was detected.
   * @param call Stringified expression that produced the failure.
   * @param err Error value to format.
   *
   * @note Returns no value.
   */
  template <class LogF, ErrorTraits T>
    inline void log_failed(LogF&&       log,
                           const char*  tag,
                           const char*  function,
                           std::int32_t line,
                           const char*  call,
                           T            err)
    {
      std::forward<LogF>(log)(tag,
                              "%s(%d): call %s error 0x%04" PRIX32 " [%s]",
                              function,
                              line,
                              call,
                              error_value_hex(sentinel::error_traits<std::remove_cvref_t<T>>::value(err)),
                              sentinel::error_traits<std::remove_cvref_t<T>>::message(err));
    }

  /**
   * @ingroup sentinel_detail
   * @internal
   *
   * @brief Logs an `std::error_code` failure.
   *
   * @tparam LogF Platform log callable type.
   *
   * @param log Platform log callable.
   * @param tag Platform log tag.
   * @param function Function name where the failure was detected.
   * @param line Source line where the failure was detected.
   * @param call Stringified expression that produced the failure.
   * @param err Error code to format.
   *
   * @note Returns no value.
   */
  template <class LogF>
    inline void log_failed(LogF&&                 log,
                           const char*            tag,
                           const char*            function,
                           std::int32_t           line,
                           const char*            call,
                           const std::error_code& err)
    {
      std::forward<LogF>(log)(tag,
                              "%s(%d): call %s error %s:0x%04" PRIX32 " [%s]",
                              function,
                              line,
                              call,
                              err.category().name(),
                              error_value_hex(static_cast<std::int32_t>(err.value())),
                              err.message().c_str());
    }

  /**
   * @ingroup sentinel_detail
   * @internal
   *
   * @brief Logs an `std::expected` failure by delegating to its error value.
   *
   * @tparam LogF Platform log callable type.
   * @tparam T Expected value type.
   * @tparam E Error value type.
   *
   * @param log Platform log callable.
   * @param tag Platform log tag.
   * @param function Function name where the failure was detected.
   * @param line Source line where the failure was detected.
   * @param call Stringified expression that produced the failure.
   * @param value Failed expected value.
   *
   * @note Returns no value.
   */
  template <class LogF, class T, class E>
    inline void log_failed(LogF&&                     log,
                           const char*                tag,
                           const char*                function,
                           std::int32_t               line,
                           const char*                call,
                           const std::expected<T, E>& value)
    {
      log_failed(std::forward<LogF>(log), tag, function, line, call, value.error());
    }

  /**
   * @ingroup sentinel_detail
   * @internal
   *
   * @brief Logs an `std::unexpected` failure by delegating to its error value.
   *
   * @tparam LogF Platform log callable type.
   * @tparam E Error value type.
   *
   * @param log Platform log callable.
   * @param tag Platform log tag.
   * @param function Function name where the failure was detected.
   * @param line Source line where the failure was detected.
   * @param call Stringified expression that produced the failure.
   * @param value Unexpected error wrapper.
   *
   * @note Returns no value.
   */
  template <class LogF, class E>
    inline void log_failed(LogF&&                    log,
                           const char*               tag,
                           const char*               function,
                           std::int32_t              line,
                           const char*               call,
                           const std::unexpected<E>& value)
    {
      log_failed(std::forward<LogF>(log), tag, function, line, call, value.error());
    }

  /**
   * @ingroup sentinel_detail
   * @internal
   *
   * @brief Logs a failure and then logs an additional formatted message.
   *
   * @tparam LogF Platform log callable type.
   * @tparam T Failure value type.
   * @tparam Args Format argument types.
   *
   * @param log Platform log callable.
   * @param tag Platform log tag.
   * @param function Function name where the failure was detected.
   * @param line Source line where the failure was detected.
   * @param call Stringified expression that produced the failure.
   * @param value Failure value to format.
   * @param format Backend-defined format string for the additional message.
   * @param args Format arguments for `format`.
   *
   * @note Returns no value.
   */
  template <class LogF, class T, class... Args>
    inline void log_failed_fmt(LogF&&       log,
                               const char*  tag,
                               const char*  function,
                               std::int32_t line,
                               const char*  call,
                               const T&     value,
                               const char*  format,
                               Args&&...    args)
    {
      log_failed(log, tag, function, line, call, value);
      std::forward<LogF>(log)(tag, format, std::forward<Args>(args)...);
    }
}
