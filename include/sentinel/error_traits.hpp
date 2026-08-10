#pragma once

#include <cstdint>
#include <concepts>
#include <type_traits>


namespace sentinel
{
  template <class T>
    struct error_traits;
}

namespace sentinel::detail
{
  template <class T>
    concept ErrorTraits =
      requires(std::remove_cvref_t<T> value)
      {
        { sentinel::error_traits<std::remove_cvref_t<T>>::failed(value) } -> std::convertible_to<bool>;
        { sentinel::error_traits<std::remove_cvref_t<T>>::message(value) } -> std::convertible_to<const char*>;
        { sentinel::error_traits<std::remove_cvref_t<T>>::value(value) } -> std::convertible_to<std::int32_t>;
      };
}
