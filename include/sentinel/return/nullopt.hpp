#pragma once

/**
 * @file
 * @ingroup sentinel_return
 *
 * @brief Return helpers that return `std::nullopt` on failure.
 */

#include <optional>

#include "sentinel/return/detail.hpp"


#define RETURN_NULLOPT_WITH_INFO(tag, call)                         SENTINEL_RETURN_IMPL_VALUE(tag, call, sentinel::platform::log_info, std::nullopt)
#define RETURN_NULLOPT_WITH_INFO_ISR(tag, call)                     SENTINEL_RETURN_IMPL_VALUE(tag, call, sentinel::platform::log_info_isr, std::nullopt)
#define RETURN_NULLOPT_WITH_INFO_FMT(tag, call, format, ...)        SENTINEL_RETURN_IMPL_VALUE_FMT(tag, call, sentinel::platform::log_info, std::nullopt, format __VA_OPT__(,) __VA_ARGS__)
#define RETURN_NULLOPT_WITH_INFO_FMT_ISR(tag, call, format, ...)    SENTINEL_RETURN_IMPL_VALUE_FMT(tag, call, sentinel::platform::log_info_isr, std::nullopt, format __VA_OPT__(,) __VA_ARGS__)

#define RETURN_NULLOPT_WITH_WARNING(tag, call)                      SENTINEL_RETURN_IMPL_VALUE(tag, call, sentinel::platform::log_warning, std::nullopt)
#define RETURN_NULLOPT_WITH_WARNING_ISR(tag, call)                  SENTINEL_RETURN_IMPL_VALUE(tag, call, sentinel::platform::log_warning_isr, std::nullopt)
#define RETURN_NULLOPT_WITH_WARNING_FMT(tag, call, format, ...)     SENTINEL_RETURN_IMPL_VALUE_FMT(tag, call, sentinel::platform::log_warning, std::nullopt, format __VA_OPT__(,) __VA_ARGS__)
#define RETURN_NULLOPT_WITH_WARNING_FMT_ISR(tag, call, format, ...) SENTINEL_RETURN_IMPL_VALUE_FMT(tag, call, sentinel::platform::log_warning_isr, std::nullopt, format __VA_OPT__(,) __VA_ARGS__)

#define RETURN_NULLOPT_WITH_ERROR(tag, call)                        SENTINEL_RETURN_IMPL_VALUE(tag, call, sentinel::platform::log_error, std::nullopt)
#define RETURN_NULLOPT_WITH_ERROR_ISR(tag, call)                    SENTINEL_RETURN_IMPL_VALUE(tag, call, sentinel::platform::log_error_isr, std::nullopt)
#define RETURN_NULLOPT_WITH_ERROR_FMT(tag, call, format, ...)       SENTINEL_RETURN_IMPL_VALUE_FMT(tag, call, sentinel::platform::log_error, std::nullopt, format __VA_OPT__(,) __VA_ARGS__)
#define RETURN_NULLOPT_WITH_ERROR_FMT_ISR(tag, call, format, ...)   SENTINEL_RETURN_IMPL_VALUE_FMT(tag, call, sentinel::platform::log_error_isr, std::nullopt, format __VA_OPT__(,) __VA_ARGS__)
