#pragma once

#include "platform.hpp"

#include "sentinel/config.hpp"

#include "sentinel/detail/log_core.hpp"
#include "sentinel/detail/source_location.hpp"


#if CHECKS_SILENT

  #define LOG_WARNING(tag, call) \
    do                           \
    {                            \
      (void)(tag);               \
      (void)(call);              \
    } while(0)

  #define LOG_WARNING_ISR(tag, call) \
    do                               \
    {                                \
      (void)(tag);                   \
      (void)(call);                  \
    } while(0)

  #define LOG_WARNING_FMT(tag, call, format, ...) \
    do                                            \
    {                                             \
      (void)(tag);                                \
      (void)(call);                               \
      (void)(format);                             \
    } while(0)

  #define LOG_WARNING_FMT_ISR(tag, call, format, ...) \
    do                                                \
    {                                                 \
      (void)(tag);                                    \
      (void)(call);                                   \
      (void)(format);                                 \
    } while(0)

  #define LOG_WARNING_ON_ERR(tag, call) \
    do                                  \
    {                                   \
      (void)(tag);                      \
      (void)(call);                     \
    } while(0)

  #define LOG_WARNING_ON_ERR_ISR(tag, call) \
    do                                      \
    {                                       \
      (void)(tag);                          \
      (void)(call);                         \
    } while(0)

  #define LOG_WARNING_ON_ERR_FMT(tag, call, format, ...) \
    do                                                   \
    {                                                    \
      (void)(tag);                                       \
      (void)(call);                                      \
      (void)(format);                                    \
    } while(0)

  #define LOG_WARNING_ON_ERR_FMT_ISR(tag, call, format, ...) \
    do                                                       \
    {                                                        \
      (void)(tag);                                           \
      (void)(call);                                          \
      (void)(format);                                        \
    } while(0)

#else

  #define LOG_WARNING(tag, call)            \
    do                                      \
    {                                       \
      sentinel::detail::log_failed(         \
        SENTINEL_LOG_FUNCTION(              \
          sentinel::platform::log_warning), \
        tag,                                \
        FUNCTION_NAME,                      \
        __LINE__,                           \
        #call,                              \
        (call));                            \
    } while(0)

  #define LOG_WARNING_ISR(tag, call)            \
    do                                          \
    {                                           \
      sentinel::detail::log_failed(             \
        SENTINEL_LOG_FUNCTION(                  \
          sentinel::platform::log_warning_isr), \
        tag,                                    \
        FUNCTION_NAME,                          \
        __LINE__,                               \
        #call,                                  \
        (call));                                \
    } while(0)

  #define LOG_WARNING_FMT(tag, call, format, ...) \
    do                                            \
    {                                             \
      sentinel::detail::log_failed_fmt(           \
        SENTINEL_LOG_FUNCTION(                    \
          sentinel::platform::log_warning),       \
        tag,                                      \
        FUNCTION_NAME,                            \
        __LINE__,                                 \
        #call,                                    \
        (call),                                   \
        format __VA_OPT__(,) __VA_ARGS__);        \
    } while(0)

  #define LOG_WARNING_FMT_ISR(tag, call, format, ...) \
    do                                                \
    {                                                 \
      sentinel::detail::log_failed_fmt(               \
        SENTINEL_LOG_FUNCTION(                        \
          sentinel::platform::log_warning_isr),       \
        tag,                                          \
        FUNCTION_NAME,                                \
        __LINE__,                                     \
        #call,                                        \
        (call),                                       \
        format __VA_OPT__(,) __VA_ARGS__);            \
    } while(0)

  #define LOG_WARNING_ON_ERR(tag, call)           \
    do                                            \
    {                                             \
      auto&& result_check = (call);               \
      if (sentinel::detail::failed(result_check)) \
        [[unlikely]]                              \
      {                                           \
        sentinel::detail::log_failed(             \
          SENTINEL_LOG_FUNCTION(                  \
            sentinel::platform::log_warning),     \
          tag,                                    \
          FUNCTION_NAME,                          \
          __LINE__,                               \
          #call,                                  \
          result_check);                          \
      }                                           \
    } while(0)

  #define LOG_WARNING_ON_ERR_ISR(tag, call)       \
    do                                            \
    {                                             \
      auto&& result_check = (call);               \
      if (sentinel::detail::failed(result_check)) \
        [[unlikely]]                              \
      {                                           \
        sentinel::detail::log_failed(             \
          SENTINEL_LOG_FUNCTION(                  \
            sentinel::platform::log_warning_isr), \
          tag,                                    \
          FUNCTION_NAME,                          \
          __LINE__,                               \
          #call,                                  \
          result_check);                          \
      }                                           \
    } while(0)

  #define LOG_WARNING_ON_ERR_FMT(tag, call, format, ...) \
    do                                                   \
    {                                                    \
      auto&& result_check = (call);                      \
      if (sentinel::detail::failed(result_check))        \
        [[unlikely]]                                     \
      {                                                  \
        sentinel::detail::log_failed_fmt(                \
          SENTINEL_LOG_FUNCTION(                         \
            sentinel::platform::log_warning),            \
          tag,                                           \
          FUNCTION_NAME,                                 \
          __LINE__,                                      \
          #call,                                         \
          result_check,                                  \
          format __VA_OPT__(,) __VA_ARGS__);             \
      }                                                  \
    } while(0)

  #define LOG_WARNING_ON_ERR_FMT_ISR(tag, call, format, ...) \
    do                                                       \
    {                                                        \
      auto&& result_check = (call);                          \
      if (sentinel::detail::failed(result_check))            \
        [[unlikely]]                                         \
      {                                                      \
        sentinel::detail::log_failed_fmt(                    \
          SENTINEL_LOG_FUNCTION(                             \
            sentinel::platform::log_warning_isr),            \
          tag,                                               \
          FUNCTION_NAME,                                     \
          __LINE__,                                          \
          #call,                                             \
          result_check,                                      \
          format __VA_OPT__(,) __VA_ARGS__);                 \
      }                                                      \
    } while(0)

#endif
