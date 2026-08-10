#pragma once

#include <memory>
#include <concepts>
#include <type_traits>
#include <system_error>
#include <optional>
#include <expected>

#include "sentinel/error_traits.hpp"


namespace sentinel::detail
{
  inline bool failed(bool value)
  {
    return !value;
  }

  inline bool failed(std::nullptr_t)
  {
    return true;
  }

  template <class T>
    inline bool failed(T* ptr)
    {
      return ptr == nullptr;
    }

  template <class T, class D>
    inline bool failed(const std::unique_ptr<T, D>& ptr)
    {
      return ptr == nullptr;
    }

  template <class T>
    inline bool failed(const std::shared_ptr<T>& ptr)
    {
      return ptr == nullptr;
    }

  template <class T> requires std::is_enum_v<T> && !ErrorTraits<T>
    inline bool failed(T value)
    {
      return static_cast<std::underlying_type_t<T>>(value) != 0;
    }

  template <class T> requires ErrorTraits<T>
    inline bool failed(T value)
    {
      return sentinel::error_traits<std::remove_cvref_t<T>>::failed(value);
    }

  template <class T> requires std::is_integral_v<T> && !std::same_as<std::remove_cvref_t<T>, bool> && !ErrorTraits<T>
    inline bool failed(T) = delete;

  template <class T>
    inline bool failed(const std::optional<T>& value)
    {
      return !value.has_value();
    }

  inline bool failed(const std::error_code& err)
  {
    return static_cast<bool>(err);
  }

  template <class T, class E>
    inline bool failed(const std::expected<T, E>& value)
    {
      return !value.has_value();
    }

  template <class E>
    inline bool failed(const std::unexpected<E>&)
    {
      return true;
    }
}
