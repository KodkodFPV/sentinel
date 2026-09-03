#pragma once

/**
 * @file
 * @ingroup sentinel_return
 *
 * @brief Return helpers that wrap a caller-provided error into `std::unexpected`.
 */

#include <expected>

#include <sentinel/return/detail.hpp>


#define RETURN_OTHER_UNEXPECTED_WITH_INFO(tag, call, ret_err)                         SENTINEL_RETURN_IMPL_VALUE(tag, call, sentinel::platform::log_info, std::unexpected((ret_err)))
#define RETURN_OTHER_UNEXPECTED_WITH_INFO_ISR(tag, call, ret_err)                     SENTINEL_RETURN_IMPL_VALUE(tag, call, sentinel::platform::log_info_isr, std::unexpected((ret_err)))
#define RETURN_OTHER_UNEXPECTED_WITH_INFO_FMT(tag, call, ret_err, format, ...)        SENTINEL_RETURN_IMPL_VALUE_FMT(tag, call, sentinel::platform::log_info, std::unexpected((ret_err)), format __VA_OPT__(,) __VA_ARGS__)
#define RETURN_OTHER_UNEXPECTED_WITH_INFO_FMT_ISR(tag, call, ret_err, format, ...)    SENTINEL_RETURN_IMPL_VALUE_FMT(tag, call, sentinel::platform::log_info_isr, std::unexpected((ret_err)), format __VA_OPT__(,) __VA_ARGS__)

#define RETURN_OTHER_UNEXPECTED_WITH_WARNING(tag, call, ret_err)                      SENTINEL_RETURN_IMPL_VALUE(tag, call, sentinel::platform::log_warning, std::unexpected((ret_err)))
#define RETURN_OTHER_UNEXPECTED_WITH_WARNING_ISR(tag, call, ret_err)                  SENTINEL_RETURN_IMPL_VALUE(tag, call, sentinel::platform::log_warning_isr, std::unexpected((ret_err)))
#define RETURN_OTHER_UNEXPECTED_WITH_WARNING_FMT(tag, call, ret_err, format, ...)     SENTINEL_RETURN_IMPL_VALUE_FMT(tag, call, sentinel::platform::log_warning, std::unexpected((ret_err)), format __VA_OPT__(,) __VA_ARGS__)
#define RETURN_OTHER_UNEXPECTED_WITH_WARNING_FMT_ISR(tag, call, ret_err, format, ...) SENTINEL_RETURN_IMPL_VALUE_FMT(tag, call, sentinel::platform::log_warning_isr, std::unexpected((ret_err)), format __VA_OPT__(,) __VA_ARGS__)

#define RETURN_OTHER_UNEXPECTED_WITH_ERROR(tag, call, ret_err)                        SENTINEL_RETURN_IMPL_VALUE(tag, call, sentinel::platform::log_error, std::unexpected((ret_err)))
#define RETURN_OTHER_UNEXPECTED_WITH_ERROR_ISR(tag, call, ret_err)                    SENTINEL_RETURN_IMPL_VALUE(tag, call, sentinel::platform::log_error_isr, std::unexpected((ret_err)))
#define RETURN_OTHER_UNEXPECTED_WITH_ERROR_FMT(tag, call, ret_err, format, ...)       SENTINEL_RETURN_IMPL_VALUE_FMT(tag, call, sentinel::platform::log_error, std::unexpected((ret_err)), format __VA_OPT__(,) __VA_ARGS__)
#define RETURN_OTHER_UNEXPECTED_WITH_ERROR_FMT_ISR(tag, call, ret_err, format, ...)   SENTINEL_RETURN_IMPL_VALUE_FMT(tag, call, sentinel::platform::log_error_isr, std::unexpected((ret_err)), format __VA_OPT__(,) __VA_ARGS__)
