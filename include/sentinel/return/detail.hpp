#pragma once

/**
 * @file
 * @ingroup sentinel_detail
 * @internal
 *
 * @brief Internal backend macros shared by public `RETURN_*` helpers.
 *
 * Public return macros should use this file indirectly through `sentinel/return.hpp` or one of
 * the specific public return headers.
 */

#include <optional>
#include <expected>

#include "platform.hpp"

#include "sentinel/config.hpp"

#include "sentinel/detail/source_location.hpp"
#include "sentinel/detail/log_core.hpp"
#include "sentinel/detail/check_core.hpp"

/**
 * @def SENTINEL_RETURN_IMPL_VOID(tag, call, log_function)
 * @ingroup sentinel_detail
 * @internal
 *
 * @brief Implements public helpers that return no value on failure.
 * @param tag Platform log tag.
 * @param call Expression executed once and checked for failure.
 * @param log_function Platform log function used when logging is enabled.
 *
 * @return Returns from the current function with `return;` when `call` fails.
 */

/**
 * @def SENTINEL_RETURN_IMPL_VOID_FMT(tag, call, log_function, format, ...)
 * @ingroup sentinel_detail
 * @internal
 *
 * @brief Implements formatted public helpers that return no value on failure.
 * @param tag Platform log tag.
 * @param call Expression executed once and checked for failure.
 * @param log_function Platform log function used when logging is enabled.
 * @param format Backend-defined additional log format string.
 * @param ... Additional format arguments.
 *
 * @return Returns from the current function with `return;` when `call` fails.
 */

/**
 * @def SENTINEL_RETURN_IMPL_VALUE(tag, call, log_function, ret_value)
 * @ingroup sentinel_detail
 * @internal
 *
 * @brief Implements public helpers that return a provided value on failure.
 * @param tag Platform log tag.
 * @param call Expression executed once and checked for failure.
 * @param log_function Platform log function used when logging is enabled.
 * @param ret_value Value returned from the current function when `call` fails.
 *
 * @return Returns `ret_value` when `call` fails.
 */

/**
 * @def SENTINEL_RETURN_IMPL_VALUE_FMT(tag, call, log_function, ret_value, format, ...)
 * @ingroup sentinel_detail
 * @internal
 *
 * @brief Implements formatted public helpers that return a provided value on failure.
 * @param tag Platform log tag.
 * @param call Expression executed once and checked for failure.
 * @param log_function Platform log function used when logging is enabled.
 * @param ret_value Value returned from the current function when `call` fails.
 * @param format Backend-defined additional log format string.
 * @param ... Additional format arguments.
 *
 * @return Returns `ret_value` when `call` fails.
 */

/**
 * @def SENTINEL_RETURN_IMPL_SAME(tag, call, log_function)
 * @ingroup sentinel_detail
 * @internal
 *
 * @brief Implements public helpers that return the failed result itself.
 * @param tag Platform log tag.
 * @param call Expression executed once and checked for failure.
 * @param log_function Platform log function used when logging is enabled.
 *
 * @return Returns `result_check` when `call` fails.
 */

/**
 * @def SENTINEL_RETURN_IMPL_SAME_FMT(tag, call, log_function, format, ...)
 * @ingroup sentinel_detail
 * @internal
 *
 * @brief Implements formatted public helpers that return the failed result itself.
 * @param tag Platform log tag.
 * @param call Expression executed once and checked for failure.
 * @param log_function Platform log function used when logging is enabled.
 * @param format Backend-defined additional log format string.
 * @param ... Additional format arguments.
 *
 * @return Returns `result_check` when `call` fails.
 */

/**
 * @def SENTINEL_RETURN_IMPL_SAME_UNEXPECTED(tag, call, log_function)
 * @ingroup sentinel_detail
 * @internal
 *
 * @brief Implements public helpers that return `std::unexpected(result_check)`.
 * @param tag Platform log tag.
 * @param call Expression executed once and checked for failure.
 * @param log_function Platform log function used when logging is enabled.
 *
 * @return Returns `std::unexpected(result_check)` when `call` fails.
 */

/**
 * @def SENTINEL_RETURN_IMPL_SAME_UNEXPECTED_FMT(tag, call, log_function, format, ...)
 * @ingroup sentinel_detail
 * @internal
 *
 * @brief Implements formatted public helpers that return `std::unexpected(result_check)`.
 * @param tag Platform log tag.
 * @param call Expression executed once and checked for failure.
 * @param log_function Platform log function used when logging is enabled.
 * @param format Backend-defined additional log format string.
 * @param ... Additional format arguments.
 *
 * @return Returns `std::unexpected(result_check)` when `call` fails.
 */

/**
 * @def SENTINEL_RETURN_IMPL_ERROR_FROM_UNEXPECTED(tag, call, log_function)
 * @ingroup sentinel_detail
 * @internal
 *
 * @brief Implements public helpers that return `.error()` from a failed expected-like result.
 * @param tag Platform log tag.
 * @param call Expression executed once and checked for failure.
 * @param log_function Platform log function used when logging is enabled.
 *
 * @return Returns `result_check.error()` when `call` fails.
 */

/**
 * @def SENTINEL_RETURN_IMPL_ERROR_FROM_UNEXPECTED_FMT(tag, call, log_function, format, ...)
 * @ingroup sentinel_detail
 * @internal
 *
 * @brief Implements formatted helpers that return `.error()` from a failed expected-like result.
 * @param tag Platform log tag.
 * @param call Expression executed once and checked for failure.
 * @param log_function Platform log function used when logging is enabled.
 * @param format Backend-defined additional log format string.
 * @param ... Additional format arguments.
 *
 * @return Returns `result_check.error()` when `call` fails.
 */

/**
 * @def SENTINEL_RETURN_IMPL_UNEXPECTED_FROM_UNEXPECTED(tag, call, log_function)
 * @ingroup sentinel_detail
 * @internal
 *
 * @brief Implements public helpers that rewrap `.error()` into `std::unexpected`.
 * @param tag Platform log tag.
 * @param call Expression executed once and checked for failure.
 * @param log_function Platform log function used when logging is enabled.
 *
 * @return Returns `std::unexpected(result_check.error())` when `call` fails.
 */

/**
 * @def SENTINEL_RETURN_IMPL_UNEXPECTED_FROM_UNEXPECTED_FMT(tag, call, log_function, format, ...)
 * @ingroup sentinel_detail
 * @internal
 *
 * @brief Implements formatted helpers that rewrap `.error()` into `std::unexpected`.
 * @param tag Platform log tag.
 * @param call Expression executed once and checked for failure.
 * @param log_function Platform log function used when logging is enabled.
 * @param format Backend-defined additional log format string.
 * @param ... Additional format arguments.
 *
 * @return Returns `std::unexpected(result_check.error())` when `call` fails.
 */


#if CHECKS_SILENT

  #define SENTINEL_RETURN_IMPL_VOID(tag, call, log_function) \
    do                                                       \
    {                                                        \
      (void)(tag);                                           \
      auto&& result_check = (call);                          \
      if (sentinel::detail::failed(result_check))            \
        [[unlikely]]                                         \
        return;                                              \
    } while(0)

  #define SENTINEL_RETURN_IMPL_VOID_FMT(tag, call, log_function, format, ...) \
    do                                                                        \
    {                                                                         \
      (void)(tag);                                                            \
      (void)(format);                                                         \
      auto&& result_check = (call);                                           \
      if (sentinel::detail::failed(result_check))                             \
        [[unlikely]]                                                          \
        return;                                                               \
    } while(0)

  #define SENTINEL_RETURN_IMPL_VALUE(tag, call, log_function, ret_value) \
    do                                                                   \
    {                                                                    \
      (void)(tag);                                                       \
      auto&& result_check = (call);                                      \
      if (sentinel::detail::failed(result_check))                        \
        [[unlikely]]                                                     \
        return (ret_value);                                              \
    } while(0)

  #define SENTINEL_RETURN_IMPL_VALUE_FMT(tag, call, log_function, ret_value, format, ...) \
    do                                                                                    \
    {                                                                                     \
      (void)(tag);                                                                        \
      (void)(format);                                                                     \
      auto&& result_check = (call);                                                       \
      if (sentinel::detail::failed(result_check))                                         \
        [[unlikely]]                                                                      \
        return (ret_value);                                                               \
    } while(0)

  #define SENTINEL_RETURN_IMPL_SAME(tag, call, log_function) \
    do                                                       \
    {                                                        \
      (void)(tag);                                           \
      auto&& result_check = (call);                          \
      if (sentinel::detail::failed(result_check))            \
        [[unlikely]]                                         \
        return (result_check);                               \
    } while(0)

  #define SENTINEL_RETURN_IMPL_SAME_FMT(tag, call, log_function, format, ...) \
    do                                                                        \
    {                                                                         \
      (void)(tag);                                                            \
      (void)(format);                                                         \
      auto&& result_check = (call);                                           \
      if (sentinel::detail::failed(result_check))                             \
        [[unlikely]]                                                          \
        return (result_check);                                                \
    } while(0)

  #define SENTINEL_RETURN_IMPL_SAME_UNEXPECTED(tag, call, log_function) \
    do                                                                  \
    {                                                                   \
      (void)(tag);                                                      \
      auto&& result_check = (call);                                     \
      if (sentinel::detail::failed(result_check))                       \
        [[unlikely]]                                                    \
        return std::unexpected(result_check);                           \
    } while(0)

  #define SENTINEL_RETURN_IMPL_SAME_UNEXPECTED_FMT(tag, call, log_function, format, ...) \
    do                                                                                   \
    {                                                                                    \
      (void)(tag);                                                                       \
      (void)(format);                                                                    \
      auto&& result_check = (call);                                                      \
      if (sentinel::detail::failed(result_check))                                        \
        [[unlikely]]                                                                     \
        return std::unexpected(result_check);                                            \
    } while(0)

  #define SENTINEL_RETURN_IMPL_ERROR_FROM_UNEXPECTED(tag, call, log_function) \
    do                                                                        \
    {                                                                         \
      (void)(tag);                                                            \
      auto&& result_check = (call);                                           \
      if (sentinel::detail::failed(result_check))                             \
        [[unlikely]]                                                          \
        return result_check.error();                                          \
    } while(0)

  #define SENTINEL_RETURN_IMPL_ERROR_FROM_UNEXPECTED_FMT(tag, call, log_function, format, ...) \
    do                                                                                         \
    {                                                                                          \
      (void)(tag);                                                                             \
      (void)(format);                                                                          \
      auto&& result_check = (call);                                                            \
      if (sentinel::detail::failed(result_check))                                              \
        [[unlikely]]                                                                           \
        return result_check.error();                                                           \
    } while(0)

  #define SENTINEL_RETURN_IMPL_UNEXPECTED_FROM_UNEXPECTED(tag, call, log_function) \
    do                                                                             \
    {                                                                              \
      (void)(tag);                                                                 \
      auto&& result_check = (call);                                                \
      if (sentinel::detail::failed(result_check))                                  \
        [[unlikely]]                                                               \
        return std::unexpected(result_check.error());                              \
    } while(0)

  #define SENTINEL_RETURN_IMPL_UNEXPECTED_FROM_UNEXPECTED_FMT(tag, call, log_function, format, ...) \
    do                                                                                              \
    {                                                                                               \
      (void)(tag);                                                                                  \
      (void)(format);                                                                               \
      auto&& result_check = (call);                                                                 \
      if (sentinel::detail::failed(result_check))                                                   \
        [[unlikely]]                                                                                \
        return std::unexpected(result_check.error());                                               \
    } while(0)

#else

  #define SENTINEL_RETURN_IMPL_VOID(tag, call, log_function) \
    do                                                       \
    {                                                        \
      auto&& result_check = (call);                          \
      if (sentinel::detail::failed(result_check))            \
        [[unlikely]]                                         \
      {                                                      \
        sentinel::detail::log_failed(                        \
          SENTINEL_LOG_FUNCTION(log_function),               \
          tag,                                               \
          FUNCTION_NAME,                                     \
          __LINE__,                                          \
          #call,                                             \
          result_check);                                     \
        return;                                              \
      }                                                      \
    } while(0)

  #define SENTINEL_RETURN_IMPL_VOID_FMT(tag, call, log_function, format, ...) \
    do                                                                        \
    {                                                                         \
      auto&& result_check = (call);                                           \
      if (sentinel::detail::failed(result_check))                             \
        [[unlikely]]                                                          \
      {                                                                       \
        sentinel::detail::log_failed_fmt(                                     \
          SENTINEL_LOG_FUNCTION(log_function),                                \
          tag,                                                                \
          FUNCTION_NAME,                                                      \
          __LINE__,                                                           \
          #call,                                                              \
          result_check,                                                       \
          format __VA_OPT__(,) __VA_ARGS__);                                  \
        return;                                                               \
      }                                                                       \
    } while(0)

  #define SENTINEL_RETURN_IMPL_VALUE(tag, call, log_function, ret_value) \
    do                                                                   \
    {                                                                    \
      auto&& result_check = (call);                                      \
      if (sentinel::detail::failed(result_check))                        \
        [[unlikely]]                                                     \
      {                                                                  \
        sentinel::detail::log_failed(                                    \
          SENTINEL_LOG_FUNCTION(log_function),                           \
          tag,                                                           \
          FUNCTION_NAME,                                                 \
          __LINE__,                                                      \
          #call,                                                         \
          result_check);                                                 \
        return (ret_value);                                              \
      }                                                                  \
    } while(0)

  #define SENTINEL_RETURN_IMPL_VALUE_FMT(tag, call, log_function, ret_value, format, ...) \
    do                                                                                    \
    {                                                                                     \
      auto&& result_check = (call);                                                       \
      if (sentinel::detail::failed(result_check))                                         \
        [[unlikely]]                                                                      \
      {                                                                                   \
        sentinel::detail::log_failed_fmt(                                                 \
          SENTINEL_LOG_FUNCTION(log_function),                                            \
          tag,                                                                            \
          FUNCTION_NAME,                                                                  \
          __LINE__,                                                                       \
          #call,                                                                          \
          result_check,                                                                   \
          format __VA_OPT__(,) __VA_ARGS__);                                              \
        return (ret_value);                                                               \
      }                                                                                   \
    } while(0)

  #define SENTINEL_RETURN_IMPL_SAME(tag, call, log_function) \
    do                                                       \
    {                                                        \
      auto&& result_check = (call);                          \
      if (sentinel::detail::failed(result_check))            \
        [[unlikely]]                                         \
      {                                                      \
        sentinel::detail::log_failed(                        \
          SENTINEL_LOG_FUNCTION(log_function),               \
          tag,                                               \
          FUNCTION_NAME,                                     \
          __LINE__,                                          \
          #call,                                             \
          result_check);                                     \
        return (result_check);                               \
      }                                                      \
    } while(0)

  #define SENTINEL_RETURN_IMPL_SAME_FMT(tag, call, log_function, format, ...) \
    do                                                                        \
    {                                                                         \
      auto&& result_check = (call);                                           \
      if (sentinel::detail::failed(result_check))                             \
        [[unlikely]]                                                          \
      {                                                                       \
        sentinel::detail::log_failed_fmt(                                     \
          SENTINEL_LOG_FUNCTION(log_function),                                \
          tag,                                                                \
          FUNCTION_NAME,                                                      \
          __LINE__,                                                           \
          #call,                                                              \
          result_check,                                                       \
          format __VA_OPT__(,) __VA_ARGS__);                                  \
        return (result_check);                                                \
      }                                                                       \
    } while(0)

  #define SENTINEL_RETURN_IMPL_SAME_UNEXPECTED(tag, call, log_function) \
    do                                                                  \
    {                                                                   \
      auto&& result_check = (call);                                     \
      if (sentinel::detail::failed(result_check))                       \
        [[unlikely]]                                                    \
      {                                                                 \
        sentinel::detail::log_failed(                                   \
          SENTINEL_LOG_FUNCTION(log_function),                          \
          tag,                                                          \
          FUNCTION_NAME,                                                \
          __LINE__,                                                     \
          #call,                                                        \
          result_check);                                                \
        return std::unexpected(result_check);                           \
      }                                                                 \
    } while(0)

  #define SENTINEL_RETURN_IMPL_SAME_UNEXPECTED_FMT(tag, call, log_function, format, ...) \
    do                                                                                   \
    {                                                                                    \
      auto&& result_check = (call);                                                      \
      if (sentinel::detail::failed(result_check))                                        \
        [[unlikely]]                                                                     \
      {                                                                                  \
        sentinel::detail::log_failed_fmt(                                                \
          SENTINEL_LOG_FUNCTION(log_function),                                           \
          tag,                                                                           \
          FUNCTION_NAME,                                                                 \
          __LINE__,                                                                      \
          #call,                                                                         \
          result_check,                                                                  \
          format __VA_OPT__(,) __VA_ARGS__);                                             \
        return std::unexpected(result_check);                                            \
      }                                                                                  \
    } while(0)

  #define SENTINEL_RETURN_IMPL_ERROR_FROM_UNEXPECTED(tag, call, log_function) \
    do                                                                        \
    {                                                                         \
      auto&& result_check = (call);                                           \
      if (sentinel::detail::failed(result_check))                             \
        [[unlikely]]                                                          \
      {                                                                       \
        sentinel::detail::log_failed(                                         \
          SENTINEL_LOG_FUNCTION(log_function),                                \
          tag,                                                                \
          FUNCTION_NAME,                                                      \
          __LINE__,                                                           \
          #call,                                                              \
          result_check);                                                      \
        return result_check.error();                                          \
      }                                                                       \
    } while(0)

  #define SENTINEL_RETURN_IMPL_ERROR_FROM_UNEXPECTED_FMT(tag, call, log_function, format, ...) \
    do                                                                                         \
    {                                                                                          \
      auto&& result_check = (call);                                                            \
      if (sentinel::detail::failed(result_check))                                              \
        [[unlikely]]                                                                           \
      {                                                                                        \
        sentinel::detail::log_failed_fmt(                                                      \
          SENTINEL_LOG_FUNCTION(log_function),                                                 \
          tag,                                                                                 \
          FUNCTION_NAME,                                                                       \
          __LINE__,                                                                            \
          #call,                                                                               \
          result_check,                                                                        \
          format __VA_OPT__(,) __VA_ARGS__);                                                   \
        return result_check.error();                                                           \
      }                                                                                        \
    } while(0)

  #define SENTINEL_RETURN_IMPL_UNEXPECTED_FROM_UNEXPECTED(tag, call, log_function) \
    do                                                                             \
    {                                                                              \
      auto&& result_check = (call);                                                \
      if (sentinel::detail::failed(result_check))                                  \
        [[unlikely]]                                                               \
      {                                                                            \
        sentinel::detail::log_failed(                                              \
          SENTINEL_LOG_FUNCTION(log_function),                                     \
          tag,                                                                     \
          FUNCTION_NAME,                                                           \
          __LINE__,                                                                \
          #call,                                                                   \
          result_check);                                                           \
        return std::unexpected(result_check.error());                              \
      }                                                                            \
    } while(0)

  #define SENTINEL_RETURN_IMPL_UNEXPECTED_FROM_UNEXPECTED_FMT(tag, call, log_function, format, ...) \
    do                                                                                              \
    {                                                                                               \
      auto&& result_check = (call);                                                                 \
      if (sentinel::detail::failed(result_check))                                                   \
        [[unlikely]]                                                                                \
      {                                                                                             \
        sentinel::detail::log_failed_fmt(                                                           \
          SENTINEL_LOG_FUNCTION(log_function),                                                      \
          tag,                                                                                      \
          FUNCTION_NAME,                                                                            \
          __LINE__,                                                                                 \
          #call,                                                                                    \
          result_check,                                                                             \
          format __VA_OPT__(,) __VA_ARGS__);                                                        \
        return std::unexpected(result_check.error());                                               \
      }                                                                                             \
    } while(0)

#endif
