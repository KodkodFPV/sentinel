@mainpage sentinel

@tableofcontents

`sentinel` is a small C++ diagnostics layer for embedded and native targets. It provides
logging macros, failure-aware early-return helpers, explicit status-type adaptation through
`sentinel::error_traits`, and a pluggable platform logging backend.

The library is header-only. The selected platform backend supplies `platform.hpp` and the actual
logging sink.

@section sentinel_main_modules Modules

- @ref sentinel_log "Logging": direct logging and failure logging.
- @ref sentinel_return "Return Helpers": guard-style return helpers for common function return types.
- @ref sentinel_traits "Error Traits": opt-in support for platform-specific status types.
- @ref sentinel_config "Configuration": compile-time configuration through tweaks.
- @ref sentinel_platform "Platform Contract": required backend API.
- @ref sentinel_detail "Internal Details": internal implementation notes for maintainers.

@section sentinel_main_install CMake Integration

@code{.cmake}
add_subdirectory(sentinel)
target_link_libraries(my_target PRIVATE sentinel::sentinel)

set(SENTINEL_PLATFORM stderr CACHE STRING "" FORCE)
@endcode

Documentation generation is optional:

@code{.cmake}
set(SENTINEL_BUILD_DOCS ON CACHE BOOL "" FORCE)
@endcode

The `sentinel.docs` target runs Doxygen and writes HTML documentation into the CMake build tree.

@defgroup sentinel_public Public API

@brief Stable API intended for application and library users.

@defgroup sentinel_config Configuration
@ingroup sentinel_public

@brief Compile-time configuration switches.

@defgroup sentinel_log Logging
@ingroup sentinel_public

@brief Direct log macros and failure log macros.

@defgroup sentinel_return Return Helpers
@ingroup sentinel_public

@brief Guard-style macros that return from the current function when a value represents failure.

@defgroup sentinel_traits Error Traits
@ingroup sentinel_public

@brief Extension point for platform-specific status types.

@defgroup sentinel_platform Platform Contract
@ingroup sentinel_public

@brief Logging backend functions required by the selected platform.

@defgroup sentinel_detail Internal Details

@brief Internal implementation helpers. These names are not a stable public contract.
