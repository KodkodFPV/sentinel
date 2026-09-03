#pragma once

/**
 * @file
 * @ingroup sentinel_log
 *
 * @brief Hexdump logging macros.
 *
 * Provides normal and ISR hexdump logs for all logging severities.
 */

#include "platform.hpp"

#include <sentinel/config.hpp>
#include <sentinel/detail/log_core.hpp>
#include <sentinel/detail/hexdump.hpp>


#if CHECKS_SILENT

  #define SENTINEL_LOG_HEXDUMP_SILENT(tag, label, data, size) \
    do                                                        \
    {                                                         \
      (void)(tag);                                            \
      (void)(label);                                          \
      (void)(data);                                           \
      (void)(size);                                           \
    } while(0)

  #define LOG_HEXDUMP_INFO(tag, label, data, size)        SENTINEL_LOG_HEXDUMP_SILENT(tag, label, data, size)
  #define LOG_HEXDUMP_INFO_ISR(tag, label, data, size)    SENTINEL_LOG_HEXDUMP_SILENT(tag, label, data, size)
  #define LOG_HEXDUMP_WARNING(tag, label, data, size)     SENTINEL_LOG_HEXDUMP_SILENT(tag, label, data, size)
  #define LOG_HEXDUMP_WARNING_ISR(tag, label, data, size) SENTINEL_LOG_HEXDUMP_SILENT(tag, label, data, size)
  #define LOG_HEXDUMP_ERROR(tag, label, data, size)       SENTINEL_LOG_HEXDUMP_SILENT(tag, label, data, size)
  #define LOG_HEXDUMP_ERROR_ISR(tag, label, data, size)   SENTINEL_LOG_HEXDUMP_SILENT(tag, label, data, size)
  #define LOG_HEXDUMP_DEBUG(tag, label, data, size)       SENTINEL_LOG_HEXDUMP_SILENT(tag, label, data, size)
  #define LOG_HEXDUMP_DEBUG_ISR(tag, label, data, size)   SENTINEL_LOG_HEXDUMP_SILENT(tag, label, data, size)
  #define LOG_HEXDUMP_VERBOSE(tag, label, data, size)     SENTINEL_LOG_HEXDUMP_SILENT(tag, label, data, size)
  #define LOG_HEXDUMP_VERBOSE_ISR(tag, label, data, size) SENTINEL_LOG_HEXDUMP_SILENT(tag, label, data, size)

#else

  #define SENTINEL_LOG_HEXDUMP_IMPL(log_function, tag, label, data, size) \
    do                                                                    \
    {                                                                     \
      sentinel::detail::log_hexdump(                                      \
        SENTINEL_LOG_FUNCTION(log_function),                              \
        tag,                                                              \
        label,                                                            \
        data,                                                             \
        size);                                                            \
    } while(0)

  #define LOG_HEXDUMP_INFO(tag, label, data, size)        SENTINEL_LOG_HEXDUMP_IMPL(sentinel::platform::log_info, tag, label, data, size)
  #define LOG_HEXDUMP_INFO_ISR(tag, label, data, size)    SENTINEL_LOG_HEXDUMP_IMPL(sentinel::platform::log_info_isr, tag, label, data, size)
  #define LOG_HEXDUMP_WARNING(tag, label, data, size)     SENTINEL_LOG_HEXDUMP_IMPL(sentinel::platform::log_warning, tag, label, data, size)
  #define LOG_HEXDUMP_WARNING_ISR(tag, label, data, size) SENTINEL_LOG_HEXDUMP_IMPL(sentinel::platform::log_warning_isr, tag, label, data, size)
  #define LOG_HEXDUMP_ERROR(tag, label, data, size)       SENTINEL_LOG_HEXDUMP_IMPL(sentinel::platform::log_error, tag, label, data, size)
  #define LOG_HEXDUMP_ERROR_ISR(tag, label, data, size)   SENTINEL_LOG_HEXDUMP_IMPL(sentinel::platform::log_error_isr, tag, label, data, size)
  #define LOG_HEXDUMP_DEBUG(tag, label, data, size)       SENTINEL_LOG_HEXDUMP_IMPL(sentinel::platform::log_debug, tag, label, data, size)
  #define LOG_HEXDUMP_DEBUG_ISR(tag, label, data, size)   SENTINEL_LOG_HEXDUMP_IMPL(sentinel::platform::log_debug_isr, tag, label, data, size)
  #define LOG_HEXDUMP_VERBOSE(tag, label, data, size)     SENTINEL_LOG_HEXDUMP_IMPL(sentinel::platform::log_verbose, tag, label, data, size)
  #define LOG_HEXDUMP_VERBOSE_ISR(tag, label, data, size) SENTINEL_LOG_HEXDUMP_IMPL(sentinel::platform::log_verbose_isr, tag, label, data, size)

#endif
