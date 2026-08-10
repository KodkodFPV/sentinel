# sentinel

`sentinel` is a lightweight cross-platform C++ diagnostics layer for embedded and native targets.
It provides guard-style checks, error/warning/info logging, and early-return helpers for
`std::error_code`, `std::expected`, booleans, enums, pointers, and platform-specific status types
through explicit error traits and pluggable backends.

Platform backends live in the `platform` submodule:

```bash
git submodule update --init --recursive
```

## CMake

```cmake
add_subdirectory(sentinel)
target_link_libraries(my_target PRIVATE sentinel::sentinel)
```

Select a backend with:

```cmake
set(SENTINEL_PLATFORM stderr CACHE STRING "" FORCE)
```

Supported backends are provided by `sentinel-platform`.

## Error Traits

Platform-specific status types can opt in by specializing `sentinel::error_traits<T>`:

```cpp
namespace sentinel
{
  template <>
    struct error_traits<MyStatus>
    {
      static bool failed(MyStatus value);
      static const char* message(MyStatus value);
      static std::int32_t value(MyStatus value);
    };
}
```
