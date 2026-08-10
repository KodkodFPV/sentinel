#pragma once

/**
 * @file
 * @ingroup sentinel_config
 *
 * @brief Compile-time configuration entry point.
 *
 * Includes an optional user-provided `sentinel.tweaks.hpp` and defines default values for
 * configuration switches that were not provided by the user.
 */

#if __has_include("sentinel.tweaks.hpp")
  #include "sentinel.tweaks.hpp"
#endif

/**
 * @def CHECKS_SILENT
 * @ingroup sentinel_config
 *
 * @brief Suppresses platform logging while keeping checks and returns active.
 */
#if !defined(CHECKS_SILENT)
  #define CHECKS_SILENT 0
#endif
