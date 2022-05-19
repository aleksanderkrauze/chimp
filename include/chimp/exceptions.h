#ifndef CHIMP_EXCEPTIONS_H
#define CHIMP_EXCEPTIONS_H

#include <exception>
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
class Error : public std::exception {
public:
  /** Constructs Error */
  explicit Error(const std::string) noexcept;

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
class LogicError : public Error {
public:
  /** Constructs LogicError */
  explicit LogicError(const std::string) noexcept;

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
class ParsingError : public Error {
public:
  /** Constructs ParsingError */
  explicit ParsingError(const std::string) noexcept;

  ParsingError(const ParsingError&) = delete;
  explicit ParsingError(ParsingError&&) = default;
  ParsingError& operator=(const ParsingError&) = delete;
  ParsingError& operator=(ParsingError&&) = delete;
};

} // namespace chimp

#endif // CHIMP_EXCEPTIONS_H
