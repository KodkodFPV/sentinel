#pragma once

/**
 * @file
 * @ingroup sentinel_return
 *
 * @brief Return helpers that return `false` on failure.
 */

#include <sentinel/return/detail.hpp>


#define RETURN_FALSE_WITH_INFO(tag, call)                         SENTINEL_RETURN_IMPL_VALUE(tag, call, sentinel::platform::log_info, false)
#define RETURN_FALSE_WITH_INFO_ISR(tag, call)                     SENTINEL_RETURN_IMPL_VALUE(tag, call, sentinel::platform::log_info_isr, false)
#define RETURN_FALSE_WITH_INFO_FMT(tag, call, format, ...)        SENTINEL_RETURN_IMPL_VALUE_FMT(tag, call, sentinel::platform::log_info, false, format __VA_OPT__(,) __VA_ARGS__)
#define RETURN_FALSE_WITH_INFO_FMT_ISR(tag, call, format, ...)    SENTINEL_RETURN_IMPL_VALUE_FMT(tag, call, sentinel::platform::log_info_isr, false, format __VA_OPT__(,) __VA_ARGS__)

#define RETURN_FALSE_WITH_WARNING(tag, call)                      SENTINEL_RETURN_IMPL_VALUE(tag, call, sentinel::platform::log_warning, false)
#define RETURN_FALSE_WITH_WARNING_ISR(tag, call)                  SENTINEL_RETURN_IMPL_VALUE(tag, call, sentinel::platform::log_warning_isr, false)
#define RETURN_FALSE_WITH_WARNING_FMT(tag, call, format, ...)     SENTINEL_RETURN_IMPL_VALUE_FMT(tag, call, sentinel::platform::log_warning, false, format __VA_OPT__(,) __VA_ARGS__)
#define RETURN_FALSE_WITH_WARNING_FMT_ISR(tag, call, format, ...) SENTINEL_RETURN_IMPL_VALUE_FMT(tag, call, sentinel::platform::log_warning_isr, false, format __VA_OPT__(,) __VA_ARGS__)

#define RETURN_FALSE_WITH_ERROR(tag, call)                        SENTINEL_RETURN_IMPL_VALUE(tag, call, sentinel::platform::log_error, false)
#define RETURN_FALSE_WITH_ERROR_ISR(tag, call)                    SENTINEL_RETURN_IMPL_VALUE(tag, call, sentinel::platform::log_error_isr, false)
#define RETURN_FALSE_WITH_ERROR_FMT(tag, call, format, ...)       SENTINEL_RETURN_IMPL_VALUE_FMT(tag, call, sentinel::platform::log_error, false, format __VA_OPT__(,) __VA_ARGS__)
#define RETURN_FALSE_WITH_ERROR_FMT_ISR(tag, call, format, ...)   SENTINEL_RETURN_IMPL_VALUE_FMT(tag, call, sentinel::platform::log_error_isr, false, format __VA_OPT__(,) __VA_ARGS__)
