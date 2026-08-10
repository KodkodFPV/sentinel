#pragma once

/**
 * @file
 * @ingroup sentinel_return
 *
 * @brief Return helpers that rewrap `.error()` into `std::unexpected`.
 */

#include <expected>

#include "sentinel/return/detail.hpp"


#define RETURN_UNEXPECTED_FROM_UNEXPECTED_WITH_ERROR(tag, call)                        SENTINEL_RETURN_IMPL_UNEXPECTED_FROM_UNEXPECTED(tag, call, sentinel::platform::log_error)
#define RETURN_UNEXPECTED_FROM_UNEXPECTED_WITH_ERROR_ISR(tag, call)                    SENTINEL_RETURN_IMPL_UNEXPECTED_FROM_UNEXPECTED(tag, call, sentinel::platform::log_error_isr)
#define RETURN_UNEXPECTED_FROM_UNEXPECTED_WITH_ERROR_FMT(tag, call, format, ...)       SENTINEL_RETURN_IMPL_UNEXPECTED_FROM_UNEXPECTED_FMT(tag, call, sentinel::platform::log_error, format __VA_OPT__(,) __VA_ARGS__)
#define RETURN_UNEXPECTED_FROM_UNEXPECTED_WITH_ERROR_FMT_ISR(tag, call, format, ...)   SENTINEL_RETURN_IMPL_UNEXPECTED_FROM_UNEXPECTED_FMT(tag, call, sentinel::platform::log_error_isr, format __VA_OPT__(,) __VA_ARGS__)

#define RETURN_UNEXPECTED_FROM_UNEXPECTED_WITH_WARNING(tag, call)                      SENTINEL_RETURN_IMPL_UNEXPECTED_FROM_UNEXPECTED(tag, call, sentinel::platform::log_warning)
#define RETURN_UNEXPECTED_FROM_UNEXPECTED_WITH_WARNING_ISR(tag, call)                  SENTINEL_RETURN_IMPL_UNEXPECTED_FROM_UNEXPECTED(tag, call, sentinel::platform::log_warning_isr)
#define RETURN_UNEXPECTED_FROM_UNEXPECTED_WITH_WARNING_FMT(tag, call, format, ...)     SENTINEL_RETURN_IMPL_UNEXPECTED_FROM_UNEXPECTED_FMT(tag, call, sentinel::platform::log_warning, format __VA_OPT__(,) __VA_ARGS__)
#define RETURN_UNEXPECTED_FROM_UNEXPECTED_WITH_WARNING_FMT_ISR(tag, call, format, ...) SENTINEL_RETURN_IMPL_UNEXPECTED_FROM_UNEXPECTED_FMT(tag, call, sentinel::platform::log_warning_isr, format __VA_OPT__(,) __VA_ARGS__)

#define RETURN_UNEXPECTED_FROM_UNEXPECTED_WITH_INFO(tag, call)                         SENTINEL_RETURN_IMPL_UNEXPECTED_FROM_UNEXPECTED(tag, call, sentinel::platform::log_info)
#define RETURN_UNEXPECTED_FROM_UNEXPECTED_WITH_INFO_ISR(tag, call)                     SENTINEL_RETURN_IMPL_UNEXPECTED_FROM_UNEXPECTED(tag, call, sentinel::platform::log_info_isr)
#define RETURN_UNEXPECTED_FROM_UNEXPECTED_WITH_INFO_FMT(tag, call, format, ...)        SENTINEL_RETURN_IMPL_UNEXPECTED_FROM_UNEXPECTED_FMT(tag, call, sentinel::platform::log_info, format __VA_OPT__(,) __VA_ARGS__)
#define RETURN_UNEXPECTED_FROM_UNEXPECTED_WITH_INFO_FMT_ISR(tag, call, format, ...)    SENTINEL_RETURN_IMPL_UNEXPECTED_FROM_UNEXPECTED_FMT(tag, call, sentinel::platform::log_info_isr, format __VA_OPT__(,) __VA_ARGS__)
