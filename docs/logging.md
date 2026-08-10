# Logging API

@ingroup sentinel_log

The logging API is split by severity: error, warning, and info. Every severity has the same
shape and differs only by the backend function it calls.

## Common Parameters

| Parameter | Used by | Description |
| --------- | ------- | ----------- |
| `tag` | All logging macros | Platform log tag, usually a short static component name. |
| `message` | Plain log macros | Null-terminated text message. It is forwarded to the backend using `"%s"`. |
| `format` | `_FMT` macros | Backend-defined format string. Existing backends use printf-style formatting. |
| `...` | `_FMT` macros | Format arguments passed to the selected platform backend. |
| `value` | `*_FAILURE*` macros | Already available failure value to format. These macros do not check whether it failed. |
| `call` | `*_ON_FAILURE*` macros | Expression executed once, stored as `result_check`, checked with `sentinel::detail::failed`, and logged only on failure. |

## Return Value

Logging macros do not return a value. They either emit a platform log message or, when
`CHECKS_SILENT` is `1`, suppress the platform log call.

## Plain Log Macros

| Macro | Parameters | Return value | Behavior |
| ----- | ---------- | ------------ | -------- |
| `LOG_ERROR(tag, message)` | `tag`, `message` | none | Logs a plain error message using `"%s"`. |
| `LOG_WARNING(tag, message)` | `tag`, `message` | none | Logs a plain warning message using `"%s"`. |
| `LOG_INFO(tag, message)` | `tag`, `message` | none | Logs a plain info message using `"%s"`. |
| `LOG_ERROR_ISR(tag, message)` | `tag`, `message` | none | ISR-safe error variant. |
| `LOG_WARNING_ISR(tag, message)` | `tag`, `message` | none | ISR-safe warning variant. |
| `LOG_INFO_ISR(tag, message)` | `tag`, `message` | none | ISR-safe info variant. |

## Formatted Log Macros

| Macro | Parameters | Return value | Behavior |
| ----- | ---------- | ------------ | -------- |
| `LOG_ERROR_FMT(tag, format, ...)` | `tag`, `format`, `...` | none | Logs a formatted error message. |
| `LOG_WARNING_FMT(tag, format, ...)` | `tag`, `format`, `...` | none | Logs a formatted warning message. |
| `LOG_INFO_FMT(tag, format, ...)` | `tag`, `format`, `...` | none | Logs a formatted info message. |
| `LOG_ERROR_FMT_ISR(tag, format, ...)` | `tag`, `format`, `...` | none | ISR-safe formatted error variant. |
| `LOG_WARNING_FMT_ISR(tag, format, ...)` | `tag`, `format`, `...` | none | ISR-safe formatted warning variant. |
| `LOG_INFO_FMT_ISR(tag, format, ...)` | `tag`, `format`, `...` | none | ISR-safe formatted info variant. |

## Failure Value Macros

These macros receive an already available value and log it as a failure without deciding whether
the value failed.

| Macro | Parameters | Return value | Behavior |
| ----- | ---------- | ------------ | -------- |
| `LOG_ERROR_FAILURE(tag, value)` | `tag`, `value` | none | Logs `value` as an error failure. |
| `LOG_WARNING_FAILURE(tag, value)` | `tag`, `value` | none | Logs `value` as a warning failure. |
| `LOG_INFO_FAILURE(tag, value)` | `tag`, `value` | none | Logs `value` as an info failure. |
| `LOG_ERROR_FAILURE_ISR(tag, value)` | `tag`, `value` | none | ISR-safe error failure variant. |
| `LOG_WARNING_FAILURE_ISR(tag, value)` | `tag`, `value` | none | ISR-safe warning failure variant. |
| `LOG_INFO_FAILURE_ISR(tag, value)` | `tag`, `value` | none | ISR-safe info failure variant. |
| `LOG_ERROR_FAILURE_FMT(tag, value, format, ...)` | `tag`, `value`, `format`, `...` | none | Logs failure details and an additional formatted error message. |
| `LOG_WARNING_FAILURE_FMT(tag, value, format, ...)` | `tag`, `value`, `format`, `...` | none | Logs failure details and an additional formatted warning message. |
| `LOG_INFO_FAILURE_FMT(tag, value, format, ...)` | `tag`, `value`, `format`, `...` | none | Logs failure details and an additional formatted info message. |
| `LOG_ERROR_FAILURE_FMT_ISR(tag, value, format, ...)` | `tag`, `value`, `format`, `...` | none | ISR-safe formatted error failure variant. |
| `LOG_WARNING_FAILURE_FMT_ISR(tag, value, format, ...)` | `tag`, `value`, `format`, `...` | none | ISR-safe formatted warning failure variant. |
| `LOG_INFO_FAILURE_FMT_ISR(tag, value, format, ...)` | `tag`, `value`, `format`, `...` | none | ISR-safe formatted info failure variant. |

## Conditional Failure Macros

These macros execute `call`, check it with `sentinel::detail::failed`, and log only when the
result represents failure.

| Macro | Parameters | Return value | Behavior |
| ----- | ---------- | ------------ | -------- |
| `LOG_ERROR_ON_FAILURE(tag, call)` | `tag`, `call` | none | Executes `call`; logs error details if it failed. |
| `LOG_WARNING_ON_FAILURE(tag, call)` | `tag`, `call` | none | Executes `call`; logs warning details if it failed. |
| `LOG_INFO_ON_FAILURE(tag, call)` | `tag`, `call` | none | Executes `call`; logs info details if it failed. |
| `LOG_ERROR_ON_FAILURE_ISR(tag, call)` | `tag`, `call` | none | ISR-safe conditional error variant. |
| `LOG_WARNING_ON_FAILURE_ISR(tag, call)` | `tag`, `call` | none | ISR-safe conditional warning variant. |
| `LOG_INFO_ON_FAILURE_ISR(tag, call)` | `tag`, `call` | none | ISR-safe conditional info variant. |
| `LOG_ERROR_ON_FAILURE_FMT(tag, call, format, ...)` | `tag`, `call`, `format`, `...` | none | Logs failure details and an additional formatted error message. |
| `LOG_WARNING_ON_FAILURE_FMT(tag, call, format, ...)` | `tag`, `call`, `format`, `...` | none | Logs failure details and an additional formatted warning message. |
| `LOG_INFO_ON_FAILURE_FMT(tag, call, format, ...)` | `tag`, `call`, `format`, `...` | none | Logs failure details and an additional formatted info message. |
| `LOG_ERROR_ON_FAILURE_FMT_ISR(tag, call, format, ...)` | `tag`, `call`, `format`, `...` | none | ISR-safe formatted conditional error variant. |
| `LOG_WARNING_ON_FAILURE_FMT_ISR(tag, call, format, ...)` | `tag`, `call`, `format`, `...` | none | ISR-safe formatted conditional warning variant. |
| `LOG_INFO_ON_FAILURE_FMT_ISR(tag, call, format, ...)` | `tag`, `call`, `format`, `...` | none | ISR-safe formatted conditional info variant. |

## Silent Checks

When `CHECKS_SILENT` is `1`, logging macros do not call the platform backend.

Conditional failure macros still evaluate `call`; pure formatted log macros do not evaluate
variadic formatting arguments because no platform log call is made.
