#pragma once

/**
 * @file
 * @ingroup sentinel_return
 *
 * @brief Return helpers that return a caller-provided fallback value on failure.
 */

#include "sentinel/return/detail.hpp"


#define RETURN_OTHER_WITH_INFO(tag, call, ret_err)                         SENTINEL_RETURN_IMPL_VALUE(tag, call, sentinel::platform::log_info, ret_err)
#define RETURN_OTHER_WITH_INFO_ISR(tag, call, ret_err)                     SENTINEL_RETURN_IMPL_VALUE(tag, call, sentinel::platform::log_info_isr, ret_err)
#define RETURN_OTHER_WITH_INFO_FMT(tag, call, ret_err, format, ...)        SENTINEL_RETURN_IMPL_VALUE_FMT(tag, call, sentinel::platform::log_info, ret_err, format __VA_OPT__(,) __VA_ARGS__)
#define RETURN_OTHER_WITH_INFO_FMT_ISR(tag, call, ret_err, format, ...)    SENTINEL_RETURN_IMPL_VALUE_FMT(tag, call, sentinel::platform::log_info_isr, ret_err, format __VA_OPT__(,) __VA_ARGS__)

#define RETURN_OTHER_WITH_WARNING(tag, call, ret_err)                      SENTINEL_RETURN_IMPL_VALUE(tag, call, sentinel::platform::log_warning, ret_err)
#define RETURN_OTHER_WITH_WARNING_ISR(tag, call, ret_err)                  SENTINEL_RETURN_IMPL_VALUE(tag, call, sentinel::platform::log_warning_isr, ret_err)
#define RETURN_OTHER_WITH_WARNING_FMT(tag, call, ret_err, format, ...)     SENTINEL_RETURN_IMPL_VALUE_FMT(tag, call, sentinel::platform::log_warning, ret_err, format __VA_OPT__(,) __VA_ARGS__)
#define RETURN_OTHER_WITH_WARNING_FMT_ISR(tag, call, ret_err, format, ...) SENTINEL_RETURN_IMPL_VALUE_FMT(tag, call, sentinel::platform::log_warning_isr, ret_err, format __VA_OPT__(,) __VA_ARGS__)

#define RETURN_OTHER_WITH_ERROR(tag, call, ret_err)                        SENTINEL_RETURN_IMPL_VALUE(tag, call, sentinel::platform::log_error, ret_err)
#define RETURN_OTHER_WITH_ERROR_ISR(tag, call, ret_err)                    SENTINEL_RETURN_IMPL_VALUE(tag, call, sentinel::platform::log_error_isr, ret_err)
#define RETURN_OTHER_WITH_ERROR_FMT(tag, call, ret_err, format, ...)       SENTINEL_RETURN_IMPL_VALUE_FMT(tag, call, sentinel::platform::log_error, ret_err, format __VA_OPT__(,) __VA_ARGS__)
#define RETURN_OTHER_WITH_ERROR_FMT_ISR(tag, call, ret_err, format, ...)   SENTINEL_RETURN_IMPL_VALUE_FMT(tag, call, sentinel::platform::log_error_isr, ret_err, format __VA_OPT__(,) __VA_ARGS__)
