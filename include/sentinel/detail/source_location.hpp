#pragma once

/**
 * @file
 * @ingroup sentinel_detail
 * @internal
 *
 * @brief Compiler-specific function-name macro selection.
 */

/**
 * @def FUNCTION_NAME
 * @ingroup sentinel_detail
 * @internal
 *
 * @brief Expands to the best available compiler-specific current function name string.
 *
 * @return String expression naming the current function.
 */
#if defined(__GNUC__) || defined(__clang__)
  #define FUNCTION_NAME __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
  #define FUNCTION_NAME __FUNCSIG__
#else
  #define FUNCTION_NAME __func__
#endif
