# Error Traits

@ingroup sentinel_traits

`sentinel::error_traits<T>` is the extension point for status types whose failure convention and
message conversion are not known to the core library.

Specialize the template for a concrete type:

@code{.cpp}
namespace sentinel
{
  /**
   *
   * @brief Adapts `MyStatus` to sentinel checks and logs.
   */
  template <>
    struct error_traits<MyStatus>
    {
      /**
       * @param value Status value to check.
       *
       * @return `true` when `value` represents failure; otherwise `false`.
       */
      static bool failed(MyStatus value);

      /**
       * @param value Status value to describe.
       *
       * @return Stable null-terminated string describing `value`.
       */
      static const char* message(MyStatus value);

      /**
       * @param value Status value to convert.
       *
       * @return Signed numeric representation used in failure logs.
       */
      static std::int32_t value(MyStatus value);
    };
}
@endcode

The specialization must provide:

- `failed(value)`: returns `true` when `value` represents failure.
- `message(value)`: returns a stable C string describing the value.
- `value(value)`: returns a signed numeric representation used in logs.

## Template Parameters

`sentinel::error_traits<T>` has one template parameter:

| Template parameter | Description |
| ------------------ | ----------- |
| `T` | Concrete status type adapted to sentinel. |

Use traits for platform SDK status types, vendor enums, and integer-like handles whose zero/nonzero
failure convention is not safe to infer globally.

## Typedef Note

Traits are matched by the C++ type system. If a platform status type is only a typedef of a plain
integer, specializing `error_traits` for it also specializes that integer type. Prefer a small
wrapper type when the platform does not provide a distinct type.
