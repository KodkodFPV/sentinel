#pragma once

/**
 * @file
 * @ingroup sentinel_log
 *
 * @brief Info-level logging macros.
 *
 * Provides info logs, explicit failure logging, and conditional failure logging.
 */

#include "platform.hpp"

#include "sentinel/config.hpp"

#include "sentinel/detail/log_core.hpp"
#include "sentinel/detail/source_location.hpp"


#if CHECKS_SILENT

  #define LOG_INFO(tag, format, ...) \
    do                               \
    {                                \
      (void)(tag);                   \
      (void)(format);                \
    } while(0)

  #define LOG_INFO_ISR(tag, format, ...) \
    do                                   \
    {                                    \
      (void)(tag);                       \
      (void)(format);                    \
    } while(0)

  #define LOG_INFO_FAILURE(tag, value, ...) \
    do                                      \
    {                                       \
      (void)(tag);                          \
      (void)(value);                        \
    } while(0)

  #define LOG_INFO_FAILURE_ISR(tag, value, ...) \
    do                                          \
    {                                           \
      (void)(tag);                              \
      (void)(value);                            \
    } while(0)

  #define LOG_INFO_ON_FAILURE(tag, call, ...) \
    do                                        \
    {                                         \
      (void)(tag);                            \
      (void)(call);                           \
    } while(0)

  #define LOG_INFO_ON_FAILURE_ISR(tag, call, ...) \
    do                                            \
    {                                             \
      (void)(tag);                                \
      (void)(call);                               \
    } while(0)

#else

  #define LOG_INFO(tag, format, ...)       \
    do                                     \
    {                                      \
      sentinel::platform::log_info(        \
        tag,                               \
        format __VA_OPT__(,) __VA_ARGS__); \
    } while(0)

  #define LOG_INFO_ISR(tag, format, ...)   \
    do                                     \
    {                                      \
      sentinel::platform::log_info_isr(    \
        tag,                               \
        format __VA_OPT__(,) __VA_ARGS__); \
    } while(0)

  #define LOG_INFO_FAILURE(tag, value, ...) \
    do                                      \
    {                                       \
      sentinel::detail::log_failed(         \
        SENTINEL_LOG_FUNCTION(              \
          sentinel::platform::log_info),    \
        tag,                                \
        FUNCTION_NAME,                      \
        __LINE__,                           \
        #value,                             \
        (value));                           \
      __VA_OPT__(                           \
        sentinel::platform::log_info(       \
          tag,                              \
          __VA_ARGS__);)                    \
    } while(0)

  #define LOG_INFO_FAILURE_ISR(tag, value, ...) \
    do                                          \
    {                                           \
      sentinel::detail::log_failed(             \
        SENTINEL_LOG_FUNCTION(                  \
          sentinel::platform::log_info_isr),    \
        tag,                                    \
        FUNCTION_NAME,                          \
        __LINE__,                               \
        #value,                                 \
        (value));                               \
      __VA_OPT__(                               \
        sentinel::platform::log_info_isr(       \
          tag,                                  \
          __VA_ARGS__);)                        \
    } while(0)

  #define LOG_INFO_ON_FAILURE(tag, call, ...)     \
    do                                            \
    {                                             \
      auto&& result_check = (call);               \
      if (sentinel::detail::failed(result_check)) \
        [[unlikely]]                              \
      {                                           \
        sentinel::detail::log_failed(             \
          SENTINEL_LOG_FUNCTION(                  \
            sentinel::platform::log_info),        \
          tag,                                    \
          FUNCTION_NAME,                          \
          __LINE__,                               \
          #call,                                  \
          result_check);                          \
        __VA_OPT__(                               \
          sentinel::platform::log_info(           \
            tag,                                  \
            __VA_ARGS__);)                        \
      }                                           \
    } while(0)

  #define LOG_INFO_ON_FAILURE_ISR(tag, call, ...) \
    do                                            \
    {                                             \
      auto&& result_check = (call);               \
      if (sentinel::detail::failed(result_check)) \
        [[unlikely]]                              \
      {                                           \
        sentinel::detail::log_failed(             \
          SENTINEL_LOG_FUNCTION(                  \
            sentinel::platform::log_info_isr),    \
          tag,                                    \
          FUNCTION_NAME,                          \
          __LINE__,                               \
          #call,                                  \
          result_check);                          \
        __VA_OPT__(                               \
          sentinel::platform::log_info_isr(       \
            tag,                                  \
            __VA_ARGS__);)                        \
      }                                           \
    } while(0)

#endif
