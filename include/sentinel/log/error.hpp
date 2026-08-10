#pragma once

#include "platform.hpp"

#include "sentinel/config.hpp"

#include "sentinel/detail/log_core.hpp"
#include "sentinel/detail/source_location.hpp"


#if CHECKS_SILENT

  #define LOG_ERROR(tag, call) \
    do                         \
    {                          \
      (void)(tag);             \
      (void)(call);            \
    } while(0)

  #define LOG_ERROR_ISR(tag, call) \
    do                             \
    {                              \
      (void)(tag);                 \
      (void)(call);                \
    } while(0)

  #define LOG_ERROR_FMT(tag, call, format, ...) \
    do                                          \
    {                                           \
      (void)(tag);                              \
      (void)(call);                             \
      (void)(format);                           \
    } while(0)

  #define LOG_ERROR_FMT_ISR(tag, call, format, ...) \
    do                                              \
    {                                               \
      (void)(tag);                                  \
      (void)(call);                                 \
      (void)(format);                               \
    } while(0)

  #define LOG_ERROR_ON_ERR(tag, call) \
    do                                \
    {                                 \
      (void)(tag);                    \
      (void)(call);                   \
    } while(0)

  #define LOG_ERROR_ON_ERR_ISR(tag, call) \
    do                                    \
    {                                     \
      (void)(tag);                        \
      (void)(call);                       \
    } while(0)

  #define LOG_ERROR_ON_ERR_FMT(tag, call, format, ...) \
    do                                                 \
    {                                                  \
      (void)(tag);                                     \
      (void)(call);                                    \
      (void)(format);                                  \
    } while(0)

  #define LOG_ERROR_ON_ERR_FMT_ISR(tag, call, format, ...) \
    do                                                     \
    {                                                      \
      (void)(tag);                                         \
      (void)(call);                                        \
      (void)(format);                                      \
    } while(0)

#else

  #define LOG_ERROR(tag, call)            \
    do                                    \
    {                                     \
      sentinel::detail::log_failed(       \
        SENTINEL_LOG_FUNCTION(            \
          sentinel::platform::log_error), \
        tag,                              \
        FUNCTION_NAME,                    \
        __LINE__,                         \
        #call,                            \
        (call));                          \
    } while(0)

  #define LOG_ERROR_ISR(tag, call)            \
    do                                        \
    {                                         \
      sentinel::detail::log_failed(           \
        SENTINEL_LOG_FUNCTION(                \
          sentinel::platform::log_error_isr), \
        tag,                                  \
        FUNCTION_NAME,                        \
        __LINE__,                             \
        #call,                                \
        (call));                              \
    } while(0)

  #define LOG_ERROR_FMT(tag, call, format, ...) \
    do                                          \
    {                                           \
      sentinel::detail::log_failed_fmt(         \
        SENTINEL_LOG_FUNCTION(                  \
          sentinel::platform::log_error),       \
        tag,                                    \
        FUNCTION_NAME,                          \
        __LINE__,                               \
        #call,                                  \
        (call),                                 \
        format __VA_OPT__(,) __VA_ARGS__);      \
    } while(0)

  #define LOG_ERROR_FMT_ISR(tag, call, format, ...) \
    do                                              \
    {                                               \
      sentinel::detail::log_failed_fmt(             \
        SENTINEL_LOG_FUNCTION(                      \
          sentinel::platform::log_error_isr),       \
        tag,                                        \
        FUNCTION_NAME,                              \
        __LINE__,                                   \
        #call,                                      \
        (call),                                     \
        format __VA_OPT__(,) __VA_ARGS__);          \
    } while(0)

  #define LOG_ERROR_ON_ERR(tag, call)             \
    do                                            \
    {                                             \
      auto&& result_check = (call);               \
      if (sentinel::detail::failed(result_check)) \
        [[unlikely]]                              \
      {                                           \
        sentinel::detail::log_failed(             \
          SENTINEL_LOG_FUNCTION(                  \
            sentinel::platform::log_error),       \
          tag,                                    \
          FUNCTION_NAME,                          \
          __LINE__,                               \
          #call,                                  \
          result_check);                          \
      }                                           \
    } while(0)

  #define LOG_ERROR_ON_ERR_ISR(tag, call)         \
    do                                            \
    {                                             \
      auto&& result_check = (call);               \
      if (sentinel::detail::failed(result_check)) \
        [[unlikely]]                              \
      {                                           \
        sentinel::detail::log_failed(             \
          SENTINEL_LOG_FUNCTION(                  \
            sentinel::platform::log_error_isr),   \
          tag,                                    \
          FUNCTION_NAME,                          \
          __LINE__,                               \
          #call,                                  \
          result_check);                          \
      }                                           \
    } while(0)

  #define LOG_ERROR_ON_ERR_FMT(tag, call, format, ...) \
    do                                                 \
    {                                                  \
      auto&& result_check = (call);                    \
      if (sentinel::detail::failed(result_check))      \
        [[unlikely]]                                   \
      {                                                \
        sentinel::detail::log_failed_fmt(              \
          SENTINEL_LOG_FUNCTION(                       \
            sentinel::platform::log_error),            \
          tag,                                         \
          FUNCTION_NAME,                               \
          __LINE__,                                    \
          #call,                                       \
          result_check,                                \
          format __VA_OPT__(,) __VA_ARGS__);           \
      }                                                \
    } while(0)

  #define LOG_ERROR_ON_ERR_FMT_ISR(tag, call, format, ...) \
    do                                                     \
    {                                                      \
      auto&& result_check = (call);                        \
      if (sentinel::detail::failed(result_check))          \
        [[unlikely]]                                       \
      {                                                    \
        sentinel::detail::log_failed_fmt(                  \
          SENTINEL_LOG_FUNCTION(                           \
            sentinel::platform::log_error_isr),            \
          tag,                                             \
          FUNCTION_NAME,                                   \
          __LINE__,                                        \
          #call,                                           \
          result_check,                                    \
          format __VA_OPT__(,) __VA_ARGS__);               \
      }                                                    \
    } while(0)

#endif
