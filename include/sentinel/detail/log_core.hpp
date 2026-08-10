#pragma once

#include <cstdint>
#include <memory>
#include <type_traits>
#include <utility>
#include <concepts>
#include <system_error>
#include <optional>
#include <expected>

#include "sentinel/detail/check_core.hpp"
#include "sentinel/error_traits.hpp"


#define SENTINEL_LOG_FUNCTION(log_function)                                        \
  [](auto&&... sentinel_log_args)                                                  \
  {                                                                                \
    log_function(std::forward<decltype(sentinel_log_args)>(sentinel_log_args)...); \
  }

namespace sentinel::detail
{
  template <class T>
    concept PlainError =
      !ErrorTraits<T> &&
      std::is_enum_v<T> &&
      requires(T err)
      {
        { strerr(err) } -> std::convertible_to<const char*>;
      };

  template <class LogF>
    inline void log_failed(LogF&&       log,
                           const char*  tag,
                           const char*  function,
                           std::int32_t line,
                           const char*  call,
                           bool)
    {
      std::forward<LogF>(log)(tag, "%s(%d): check %s", function, line, call);
    }

  template <class LogF, class T>
    inline void log_failed(LogF&&       log,
                           const char*  tag,
                           const char*  function,
                           std::int32_t line,
                           const char*  call,
                           T*)
    {
      std::forward<LogF>(log)(tag, "%s(%d): check %s", function, line, call);
    }

  template <class LogF>
    inline void log_failed(LogF&&       log,
                           const char*  tag,
                           const char*  function,
                           std::int32_t line,
                           const char*  call,
                           std::nullptr_t)
    {
      std::forward<LogF>(log)(tag, "%s(%d): check %s", function, line, call);
    }

  template <class LogF, class T, class D>
    inline void log_failed(LogF&&       log,
                           const char*  tag,
                           const char*  function,
                           std::int32_t line,
                           const char*  call,
                           const std::unique_ptr<T, D>&)
    {
      std::forward<LogF>(log)(tag, "%s(%d): check %s", function, line, call);
    }

  template <class LogF, class T>
    inline void log_failed(LogF&&                   log,
                           const char*              tag,
                           const char*              function,
                           std::int32_t             line,
                           const char*              call,
                           const std::shared_ptr<T>&)
    {
      std::forward<LogF>(log)(tag, "%s(%d): check %s", function, line, call);
    }

  template <class LogF, class T>
    inline void log_failed(LogF&&       log,
                           const char*  tag,
                           const char*  function,
                           std::int32_t line,
                           const char*  call,
                           const std::optional<T>&)
    {
      std::forward<LogF>(log)(tag, "%s(%d): check %s", function, line, call);
    }

  template <class LogF, PlainError T>
    inline void log_failed(LogF&&       log,
                           const char*  tag,
                           const char*  function,
                           std::int32_t line,
                           const char*  call,
                           T            err)
    {
      std::forward<LogF>(log)(tag,
                              "%s(%d): call %s error 0x%.4X [%s]",
                              function,
                              line,
                              call,
                              static_cast<std::int32_t>(err),
                              strerr(err));
    }

  template <class LogF, ErrorTraits T>
    inline void log_failed(LogF&&       log,
                           const char*  tag,
                           const char*  function,
                           std::int32_t line,
                           const char*  call,
                           T            err)
    {
      std::forward<LogF>(log)(tag,
                              "%s(%d): call %s error 0x%.4X [%s]",
                              function,
                              line,
                              call,
                              sentinel::error_traits<std::remove_cvref_t<T>>::value(err),
                              sentinel::error_traits<std::remove_cvref_t<T>>::message(err));
    }

  template <class LogF>
    inline void log_failed(LogF&&                 log,
                           const char*            tag,
                           const char*            function,
                           std::int32_t           line,
                           const char*            call,
                           const std::error_code& err)
    {
      std::forward<LogF>(log)(tag,
                              "%s(%d): call %s error %s:0x%.4X [%s]",
                              function,
                              line,
                              call,
                              err.category().name(),
                              static_cast<std::int32_t>(err.value()),
                              err.message().c_str());
    }

  template <class LogF, class T, class E>
    inline void log_failed(LogF&&                     log,
                           const char*                tag,
                           const char*                function,
                           std::int32_t               line,
                           const char*                call,
                           const std::expected<T, E>& value)
    {
      log_failed(std::forward<LogF>(log), tag, function, line, call, value.error());
    }

  template <class LogF, class E>
    inline void log_failed(LogF&&                    log,
                           const char*               tag,
                           const char*               function,
                           std::int32_t              line,
                           const char*               call,
                           const std::unexpected<E>& value)
    {
      log_failed(std::forward<LogF>(log), tag, function, line, call, value.error());
    }

  template <class LogF, class T, class... Args>
    inline void log_failed_fmt(LogF&&       log,
                               const char*  tag,
                               const char*  function,
                               std::int32_t line,
                               const char*  call,
                               const T&     value,
                               const char*  format,
                               Args&&...    args)
    {
      log_failed(log, tag, function, line, call, value);
      std::forward<LogF>(log)(tag, format, std::forward<Args>(args)...);
    }
}
