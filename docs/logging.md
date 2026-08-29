# Logging API

@ingroup sentinel_log

The logging API is split by severity: info, warning, error, debug, and verbose. Every severity
has the same shape and differs only by the backend function it calls.

## Common Parameters

| Parameter | Used by | Description |
| --------- | ------- | ----------- |
| `tag` | All logging macros | Platform log tag, usually a short static component name. |
| `format` | Direct log macros | Backend-defined format string. Existing backends use printf-style formatting. A plain message is just a format without extra arguments. |
| `...` | Direct log and failure macros | Optional format arguments passed to the selected platform backend. |
| `value` | `*_FAILURE*` macros | Already available failure value to format. These macros do not check whether it failed. |
| `call` | `*_ON_FAILURE*` macros | Expression executed once, stored as `result_check`, checked with `sentinel::detail::failed`, and logged only on failure. |

## Return Value

Logging macros do not return a value. They either emit a platform log message or, when
`CHECKS_SILENT` is `1`, suppress the platform log call.

## Log Macros

| Macro | Parameters | Return value | Behavior |
| ----- | ---------- | ------------ | -------- |
| `LOG_INFO(tag, format, ...)` | `tag`, `format`, `...` | none | Logs an info message. |
| `LOG_INFO_ISR(tag, format, ...)` | `tag`, `format`, `...` | none | ISR-safe info variant. |
| `LOG_WARNING(tag, format, ...)` | `tag`, `format`, `...` | none | Logs a warning message. |
| `LOG_WARNING_ISR(tag, format, ...)` | `tag`, `format`, `...` | none | ISR-safe warning variant. |
| `LOG_ERROR(tag, format, ...)` | `tag`, `format`, `...` | none | Logs an error message. |
| `LOG_ERROR_ISR(tag, format, ...)` | `tag`, `format`, `...` | none | ISR-safe error variant. |
| `LOG_DEBUG(tag, format, ...)` | `tag`, `format`, `...` | none | Logs a debug message. |
| `LOG_DEBUG_ISR(tag, format, ...)` | `tag`, `format`, `...` | none | ISR-safe debug variant. |
| `LOG_VERBOSE(tag, format, ...)` | `tag`, `format`, `...` | none | Logs a verbose message. |
| `LOG_VERBOSE_ISR(tag, format, ...)` | `tag`, `format`, `...` | none | ISR-safe verbose variant. |

## Failure Value Macros

These macros receive an already available value and log it as a failure without deciding whether
the value failed.

| Macro | Parameters | Return value | Behavior |
| ----- | ---------- | ------------ | -------- |
| `LOG_INFO_FAILURE(tag, value, ...)` | `tag`, `value`, `...` | none | Logs `value` as an info failure and optionally logs an additional info message. |
| `LOG_INFO_FAILURE_ISR(tag, value, ...)` | `tag`, `value`, `...` | none | ISR-safe info failure variant. |
| `LOG_WARNING_FAILURE(tag, value, ...)` | `tag`, `value`, `...` | none | Logs `value` as a warning failure and optionally logs an additional warning message. |
| `LOG_WARNING_FAILURE_ISR(tag, value, ...)` | `tag`, `value`, `...` | none | ISR-safe warning failure variant. |
| `LOG_ERROR_FAILURE(tag, value, ...)` | `tag`, `value`, `...` | none | Logs `value` as an error failure and optionally logs an additional error message. |
| `LOG_ERROR_FAILURE_ISR(tag, value, ...)` | `tag`, `value`, `...` | none | ISR-safe error failure variant. |
| `LOG_DEBUG_FAILURE(tag, value, ...)` | `tag`, `value`, `...` | none | Logs `value` as a debug failure and optionally logs an additional debug message. |
| `LOG_DEBUG_FAILURE_ISR(tag, value, ...)` | `tag`, `value`, `...` | none | ISR-safe debug failure variant. |
| `LOG_VERBOSE_FAILURE(tag, value, ...)` | `tag`, `value`, `...` | none | Logs `value` as a verbose failure and optionally logs an additional verbose message. |
| `LOG_VERBOSE_FAILURE_ISR(tag, value, ...)` | `tag`, `value`, `...` | none | ISR-safe verbose failure variant. |

## Conditional Failure Macros

These macros execute `call`, check it with `sentinel::detail::failed`, and log only when the
result represents failure.

| Macro | Parameters | Return value | Behavior |
| ----- | ---------- | ------------ | -------- |
| `LOG_INFO_ON_FAILURE(tag, call, ...)` | `tag`, `call`, `...` | none | Executes `call`; logs info details and optionally logs an additional info message if it failed. |
| `LOG_INFO_ON_FAILURE_ISR(tag, call, ...)` | `tag`, `call`, `...` | none | ISR-safe conditional info variant. |
| `LOG_WARNING_ON_FAILURE(tag, call, ...)` | `tag`, `call`, `...` | none | Executes `call`; logs warning details and optionally logs an additional warning message if it failed. |
| `LOG_WARNING_ON_FAILURE_ISR(tag, call, ...)` | `tag`, `call`, `...` | none | ISR-safe conditional warning variant. |
| `LOG_ERROR_ON_FAILURE(tag, call, ...)` | `tag`, `call`, `...` | none | Executes `call`; logs error details and optionally logs an additional error message if it failed. |
| `LOG_ERROR_ON_FAILURE_ISR(tag, call, ...)` | `tag`, `call`, `...` | none | ISR-safe conditional error variant. |
| `LOG_DEBUG_ON_FAILURE(tag, call, ...)` | `tag`, `call`, `...` | none | Executes `call`; logs debug details and optionally logs an additional debug message if it failed. |
| `LOG_DEBUG_ON_FAILURE_ISR(tag, call, ...)` | `tag`, `call`, `...` | none | ISR-safe conditional debug variant. |
| `LOG_VERBOSE_ON_FAILURE(tag, call, ...)` | `tag`, `call`, `...` | none | Executes `call`; logs verbose details and optionally logs an additional verbose message if it failed. |
| `LOG_VERBOSE_ON_FAILURE_ISR(tag, call, ...)` | `tag`, `call`, `...` | none | ISR-safe conditional verbose variant. |

## Hexdump Macros

Hexdump macros log a label line, a hexadecimal column header, and one line per 32 data bytes.
Hex bytes are grouped by 8 bytes with two spaces between groups. ASCII bytes are grouped by
8 bytes with one space between groups. Printable ASCII bytes `0x20..0x7E` are logged as
characters; all other bytes, including zeroes, are logged as `.`. Missing bytes in the final
incomplete row are padded with spaces.

| Macro | Parameters | Return value | Behavior |
| ----- | ---------- | ------------ | -------- |
| `LOG_HEXDUMP_INFO(tag, label, data, size)` | `tag`, `label`, `data`, `size` | none | Logs a hexdump through the info backend. |
| `LOG_HEXDUMP_INFO_ISR(tag, label, data, size)` | `tag`, `label`, `data`, `size` | none | ISR-safe info hexdump variant. |
| `LOG_HEXDUMP_WARNING(tag, label, data, size)` | `tag`, `label`, `data`, `size` | none | Logs a hexdump through the warning backend. |
| `LOG_HEXDUMP_WARNING_ISR(tag, label, data, size)` | `tag`, `label`, `data`, `size` | none | ISR-safe warning hexdump variant. |
| `LOG_HEXDUMP_ERROR(tag, label, data, size)` | `tag`, `label`, `data`, `size` | none | Logs a hexdump through the error backend. |
| `LOG_HEXDUMP_ERROR_ISR(tag, label, data, size)` | `tag`, `label`, `data`, `size` | none | ISR-safe error hexdump variant. |
| `LOG_HEXDUMP_DEBUG(tag, label, data, size)` | `tag`, `label`, `data`, `size` | none | Logs a hexdump through the debug backend. |
| `LOG_HEXDUMP_DEBUG_ISR(tag, label, data, size)` | `tag`, `label`, `data`, `size` | none | ISR-safe debug hexdump variant. |
| `LOG_HEXDUMP_VERBOSE(tag, label, data, size)` | `tag`, `label`, `data`, `size` | none | Logs a hexdump through the verbose backend. |
| `LOG_HEXDUMP_VERBOSE_ISR(tag, label, data, size)` | `tag`, `label`, `data`, `size` | none | ISR-safe verbose hexdump variant. |

Example output:

```text
Firmware header, size 32
          00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F  10 11 12 13 14 15 16 17  18 19 1A 1B 1C 1D 1E 1F
00000000: 48 47 49 43 00 01 20 7E  7F 80 FF 41 42 43 44 45  30 31 32 33 34 35 36 37  38 39 3A 3B 3C 3D 3E 3F  |HGIC.. ~ ...ABCDE 01234567 89:;<=>?|
```

## Silent Checks

When `CHECKS_SILENT` is `1`, logging macros do not call the platform backend.

Conditional failure macros still evaluate `call`; direct log and optional additional-message
arguments are not evaluated because no platform log call is made. Hexdump macros do not read
`data` or build dump lines.
