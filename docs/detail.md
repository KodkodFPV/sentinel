# Internal Details

@ingroup sentinel_detail

The `sentinel::detail` namespace and `SENTINEL_*` implementation macros are internal. They are
documented for maintainers, tests, and backend authors, but they are not a stable user-facing API.

## Failure Detection

`sentinel::detail::failed` maps supported result values to a boolean failure state. Public logging
and return macros use it to keep failure semantics consistent.

### Parameters

| Overload family | Template parameters | Parameters | Return value |
| --------------- | ------------------- | ---------- | ------------ |
| `failed(bool value)` | none | `value`: boolean check result | `true` when `value` is `false`. |
| `failed(T* ptr)` | `T`: pointee type | `ptr`: raw pointer to check | `true` when `ptr` is null. |
| `failed(const std::unique_ptr<T, D>& ptr)` | `T`: pointee type, `D`: deleter type | `ptr`: unique pointer to check | `true` when `ptr` is empty. |
| `failed(const std::shared_ptr<T>& ptr)` | `T`: pointee type | `ptr`: shared pointer to check | `true` when `ptr` is empty. |
| `failed(T value)` for plain enums | `T`: enum type | `value`: enum value to check | `true` when the underlying value is non-zero. |
| `failed(T value)` for trait-backed types | `T`: trait-backed type | `value`: status value to check | Result of `sentinel::error_traits<T>::failed(value)`. |
| `failed(const std::optional<T>& value)` | `T`: stored value type | `value`: optional value to check | `true` when empty. |
| `failed(const std::error_code& err)` | none | `err`: error code to check | `true` when `err` contains an error. |
| `failed(const std::expected<T, E>& value)` | `T`: value type, `E`: error type | `value`: expected value to check | `true` when it contains an error. |
| `failed(const std::unexpected<E>& value)` | `E`: error type | `value`: unexpected wrapper | Always `true`. |

## Failure Logging

`sentinel::detail::log_failed` formats failure details for known value categories:

- boolean and pointer-like values log the failed expression.
- plain enum errors log numeric value and `strerr(value)`.
- trait-backed errors log `error_traits<T>::value(value)` and `error_traits<T>::message(value)`.
- `std::error_code` logs category, numeric value, and message.
- `std::expected` and `std::unexpected` delegate to their error values.

### Parameters

Common parameters for `log_failed` and `log_failed_fmt`:

| Parameter | Description |
| --------- | ----------- |
| `log` | Platform log callable used to emit the message. |
| `tag` | Platform log tag. |
| `function` | Function name where the failure was detected. |
| `line` | Source line where the failure was detected. |
| `call` | Stringified expression that produced the failure. |
| `err`, `value`, or unnamed checked value | Failure value being formatted. |
| `format` | Additional backend-defined format string used only by `log_failed_fmt`. |
| `args` | Additional format arguments used only by `log_failed_fmt`. |

### Template Parameters

| Template parameter | Description |
| ------------------ | ----------- |
| `LogF` | Platform log callable type. |
| `T` | Checked value, pointee, expected value, optional value, or error type depending on overload. |
| `D` | Deleter type for `std::unique_ptr`. |
| `E` | Error type for `std::expected` or `std::unexpected`. |
| `Args` | Additional format argument types for `log_failed_fmt`. |

### Return Value

`log_failed` and `log_failed_fmt` return no value.

## Return Macro Backend

The public `RETURN_*` macros are thin aliases over `SENTINEL_RETURN_IMPL_*` macros. Those internal
macros own the common pattern:

- evaluate `call`;
- check `sentinel::detail::failed(result_check)`;
- log through the selected severity backend unless `CHECKS_SILENT` is enabled;
- return the correct value for the public return-family macro.

Do not call `SENTINEL_RETURN_IMPL_*` directly from application code.

### Parameters

| Parameter | Description |
| --------- | ----------- |
| `tag` | Platform log tag. |
| `call` | Expression executed once and checked with `sentinel::detail::failed`. |
| `log_function` | Platform log function selected by public severity macro. |
| `ret_value` | Return value used by value-returning implementation helpers. |
| `format` | Additional backend-defined format string used by formatted helpers. |
| `...` | Additional format arguments passed to the selected platform backend. |

### Return Value

Implementation macros return from the current function only when `call` fails. The exact returned
value depends on the implementation macro:

| Macro family | Return value on failure |
| ------------ | ----------------------- |
| `SENTINEL_RETURN_IMPL_VOID*` | `return;` |
| `SENTINEL_RETURN_IMPL_VALUE*` | `return (ret_value);` |
| `SENTINEL_RETURN_IMPL_SAME*` | `return (result_check);` |
| `SENTINEL_RETURN_IMPL_SAME_UNEXPECTED*` | `return std::unexpected(result_check);` |
| `SENTINEL_RETURN_IMPL_ERROR_FROM_UNEXPECTED*` | `return result_check.error();` |
| `SENTINEL_RETURN_IMPL_UNEXPECTED_FROM_UNEXPECTED*` | `return std::unexpected(result_check.error());` |
