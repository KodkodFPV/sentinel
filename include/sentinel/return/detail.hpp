#pragma once

#include <optional>
#include <expected>

#include "platform.hpp"

#include "sentinel/config.hpp"

#include "sentinel/detail/source_location.hpp"
#include "sentinel/detail/log_core.hpp"
#include "sentinel/detail/check_core.hpp"


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
