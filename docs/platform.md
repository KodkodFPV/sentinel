# Platform Contract

@ingroup sentinel_platform

The selected platform backend provides a `platform.hpp` header on the include path. The core
library includes it as:

@code{.cpp}
#include "platform.hpp"
@endcode

The backend must define logging functions in `sentinel::platform`.

@code{.cpp}
namespace sentinel::platform
{
  /**
   *
   * @brief Emits an error-level log message.
   * @tparam Args Format argument types.
   *
   * @param tag Platform log tag.
   * @param format Backend-defined format string.
   * @param args Format arguments.
   *
   * @return No value.
   */
  template <class... Args>
    void log_error(const char* tag, const char* format, Args&&... args);

  /**
   *
   * @brief Emits an ISR-safe error-level log message.
   * @tparam Args Format argument types.
   *
   * @param tag Platform log tag.
   * @param format Backend-defined format string.
   * @param args Format arguments.
   *
   * @return No value.
   */
  template <class... Args>
    void log_error_isr(const char* tag, const char* format, Args&&... args);

  /**
   *
   * @brief Emits a warning-level log message.
   * @tparam Args Format argument types.
   *
   * @param tag Platform log tag.
   * @param format Backend-defined format string.
   * @param args Format arguments.
   *
   * @return No value.
   */
  template <class... Args>
    void log_warning(const char* tag, const char* format, Args&&... args);

  /**
   *
   * @brief Emits an ISR-safe warning-level log message.
   * @tparam Args Format argument types.
   *
   * @param tag Platform log tag.
   * @param format Backend-defined format string.
   * @param args Format arguments.
   *
   * @return No value.
   */
  template <class... Args>
    void log_warning_isr(const char* tag, const char* format, Args&&... args);

  /**
   *
   * @brief Emits an info-level log message.
   * @tparam Args Format argument types.
   *
   * @param tag Platform log tag.
   * @param format Backend-defined format string.
   * @param args Format arguments.
   *
   * @return No value.
   */
  template <class... Args>
    void log_info(const char* tag, const char* format, Args&&... args);

  /**
   *
   * @brief Emits an ISR-safe info-level log message.
   * @tparam Args Format argument types.
   *
   * @param tag Platform log tag.
   * @param format Backend-defined format string.
   * @param args Format arguments.
   *
   * @return No value.
   */
  template <class... Args>
    void log_info_isr(const char* tag, const char* format, Args&&... args);
}
@endcode

The format string contract is backend-defined. Existing backends use printf-style formatting.

## CMake Selection

`SENTINEL_PLATFORM` selects a backend target from `sentinel-platform`:

@code{.cmake}
set(SENTINEL_PLATFORM stderr CACHE STRING "" FORCE)
@endcode

The selected backend target is linked into `sentinel::sentinel`.

## Backend Policy

The core library does not depend directly on ESP-IDF, POSIX, an RTOS, or a vendor SDK. Platform
dependencies belong in the selected backend.
