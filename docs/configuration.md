# Configuration

@ingroup sentinel_config

`sentinel` reads optional compile-time tweaks from `sentinel.tweaks.hpp`:

@code{.cpp}
#if __has_include("sentinel.tweaks.hpp")
  #include "sentinel.tweaks.hpp"
#endif
@endcode

Supported switches:

| Macro | Default | Meaning |
| ----- | ------- | ------- |
| `CHECKS_SILENT` | `0` | Suppresses platform logging when set to `1`. Failure checks and return behavior remain active. |

The tweaks header is intentionally user-provided. The library does not ship a generated tweaks
file and does not require one.
