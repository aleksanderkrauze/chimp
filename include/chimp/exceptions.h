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
class CHIMP_EXPORT Error : public std::exception {
public:
  /** Constructs Error */
  CHIMP_EXPORT explicit Error(const std::string) noexcept;

  CHIMP_EXPORT Error(const Error&) = delete;
  CHIMP_EXPORT explicit Error(Error&&) = default;
  CHIMP_EXPORT Error& operator=(const Error&) = delete;
  CHIMP_EXPORT Error& operator=(Error&&) = delete;

  CHIMP_EXPORT virtual ~Error() = default;

  CHIMP_EXPORT virtual const char* what() const noexcept final;

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
  CHIMP_EXPORT explicit LogicError(const std::string) noexcept;

  CHIMP_EXPORT LogicError(const LogicError&) = delete;
  CHIMP_EXPORT explicit LogicError(LogicError&&) = default;
  CHIMP_EXPORT LogicError& operator=(const LogicError&) = delete;
  CHIMP_EXPORT LogicError& operator=(LogicError&&) = delete;
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
  CHIMP_EXPORT explicit ParsingError(const std::string) noexcept;

  CHIMP_EXPORT ParsingError(const ParsingError&) = delete;
  CHIMP_EXPORT explicit ParsingError(ParsingError&&) = default;
  CHIMP_EXPORT ParsingError& operator=(const ParsingError&) = delete;
  CHIMP_EXPORT ParsingError& operator=(ParsingError&&) = delete;
};

} // namespace chimp

#endif // CHIMP_EXCEPTIONS_H
