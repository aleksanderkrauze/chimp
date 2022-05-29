#ifndef CHIMP_EXCEPTIONS_H
#define CHIMP_EXCEPTIONS_H

#include <exception>
#include <ostream>
#include <sstream>
#include <string>

#include "chimp/common.h"

namespace chimp {

/**
 * Basic exception class that is inherited by all exception classes used in this
 * library.
 *
 * It inherits from `std::exception`. You should always expect some exceptions
 * will be thrown from this library and at least catch this base class.
 */
class CHIMP_EXPORT Error : public std::exception {
public:
  /** Constructs Error */
  explicit Error(const std::string) noexcept;
  template <typename... Ts> Error(Ts...) noexcept;

  Error(const Error&) = delete;
  explicit Error(Error&&) = default;
  Error& operator=(const Error&) = delete;
  Error& operator=(Error&&) = delete;

  virtual ~Error() = default;

  virtual const char* what() const noexcept final;

private:
  /** Stored exception message */
  const std::string m_msg;
};

// TODO: Add examples to the doc

/**
 * Exception class that is associated with logical errors (asking for doing
 * something impossible).
 *
 * This exception is thrown usually when some invariant is violated.
 * It should always be treated as a programmers fault.
 */
class CHIMP_EXPORT LogicError : public Error {
public:
  /** Constructs LogicError */
  explicit LogicError(const std::string) noexcept;
  template <typename... Ts> LogicError(Ts...) noexcept;

  LogicError(const LogicError&) = delete;
  explicit LogicError(LogicError&&) = default;
  LogicError& operator=(const LogicError&) = delete;
  LogicError& operator=(LogicError&&) = delete;
};

/**
 * Exception class that is associated with errors that occur during parsing.
 *
 * This exception is thrown during parsing phase. It should be treated as
 * end-user error.
 *
 * @see @ref App::parse
 */
class CHIMP_EXPORT ParsingError : public Error {
public:
  /** Constructs ParsingError */
  explicit ParsingError(const std::string) noexcept;
  template <typename... Ts> ParsingError(Ts...) noexcept;

  ParsingError(const ParsingError&) = delete;
  explicit ParsingError(ParsingError&&) = default;
  ParsingError& operator=(const ParsingError&) = delete;
  ParsingError& operator=(ParsingError&&) = delete;
};

template <typename T>
std::ostream& variadic_string_ostream(std::ostream& os, T val) {
  return os << val;
}

template <typename T, typename... Ts>
std::ostream& variadic_string_ostream(std::ostream& os, T head, Ts... tail) {
  os << head;
  return variadic_string_ostream(os, tail...);
}

template <typename... Ts> std::string variadic_string(Ts... vals) {
  std::ostringstream ss;
  variadic_string_ostream(ss, vals...);
  return ss.str();
}

template <typename... Ts>
Error::Error(Ts... vals) noexcept
    : Error{variadic_string(vals...)} {}

template <typename... Ts>
LogicError::LogicError(Ts... vals) noexcept
    : LogicError{variadic_string(vals...)} {}

template <typename... Ts>
ParsingError::ParsingError(Ts... vals) noexcept
    : ParsingError{variadic_string(vals...)} {}

} // namespace chimp

#endif // CHIMP_EXCEPTIONS_H
