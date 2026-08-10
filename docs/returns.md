# Return Helpers

@ingroup sentinel_return

Return helpers execute `call`, evaluate the result with `sentinel::detail::failed`, log the
failure, and return from the current function. They are intended for guard-style error handling.

Each return family is available for error, warning, and info severities. Each severity also has
plain, ISR, formatted, and formatted ISR variants.

## Common Parameters

| Parameter | Used by | Description |
| --------- | ------- | ----------- |
| `tag` | All return helpers | Platform log tag used when a failure is logged. |
| `call` | All return helpers | Expression executed once, stored as `result_check`, and checked with `sentinel::detail::failed`. |
| `ret_err` | `RETURN_OTHER*` helpers | Caller-provided fallback value or error value returned on failure. |
| `format` | `_FMT` variants | Backend-defined format string for an additional log message. |
| `...` | `_FMT` variants | Format arguments passed to the selected platform backend. |

## Template Parameters

Return helper macros do not have template parameters. Template parameter constraints are owned by
the internal `sentinel::detail::failed` and `sentinel::detail::log_failed` overload sets.

## Return Families

| Family | Parameters | Return value on failure |
| ------ | ---------- | ----------------------- |
| `RETURN_VOID_WITH_*` | `tag`, `call` | `return;` |
| `RETURN_FALSE_WITH_*` | `tag`, `call` | `return false;` |
| `RETURN_NULLOPT_WITH_*` | `tag`, `call` | `return std::nullopt;` |
| `RETURN_SAME_WITH_*` | `tag`, `call` | `return result_check;` |
| `RETURN_OTHER_WITH_*` | `tag`, `call`, `ret_err` | `return ret_err;` |
| `RETURN_SAME_UNEXPECTED_WITH_*` | `tag`, `call` | `return std::unexpected(result_check);` |
| `RETURN_OTHER_UNEXPECTED_WITH_*` | `tag`, `call`, `ret_err` | `return std::unexpected(ret_err);` |
| `RETURN_ERR_FROM_UNEXPECTED_WITH_*` | `tag`, `call` | `return result_check.error();` |
| `RETURN_UNEXPECTED_FROM_UNEXPECTED_WITH_*` | `tag`, `call` | `return std::unexpected(result_check.error());` |

`*` is one of `ERROR`, `WARNING`, or `INFO`.

## Variants

| Suffix | Behavior |
| ------ | -------- |
| no extra suffix | Uses the normal platform log function. |
| `_ISR` | Uses the ISR platform log function. |
| `_FMT` | Adds a user formatted message after the failure message. |
| `_FMT_ISR` | Combines formatted logging with the ISR platform log function. |

Formatted variants add `format` and `...` after the base family parameters. For example,
`RETURN_OTHER_WITH_ERROR_FMT(tag, call, ret_err, format, ...)` adds the formatted message
parameters after `ret_err`.

## Failure Detection

The result of `call` is checked by `sentinel::detail::failed`.

Supported failure values:

- `bool`: failure when `false`.
- `nullptr_t`, raw pointer, `std::unique_ptr`, `std::shared_ptr`: failure when null.
- enum without `error_traits`: failure when underlying value is non-zero.
- type with `sentinel::error_traits<T>`: failure according to the trait.
- `std::optional<T>`: failure when empty.
- `std::error_code`: failure when it contains an error.
- `std::expected<T, E>`: failure when it has no value.
- `std::unexpected<E>`: always failure.

Plain integral values are deliberately not accepted unless they provide `sentinel::error_traits`.
This prevents accidental use of status values whose failure convention is unknown.

## Silent Checks

When `CHECKS_SILENT` is `1`, return helpers still evaluate `call`, still perform the failure
check, and still return on failure. Only platform logging is suppressed.
