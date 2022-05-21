#include "chimp/common.h"

#include "chimp/exceptions.h"

namespace chimp {

/** @param msg error message */
Error::Error(const std::string msg) noexcept
    : m_msg{msg} {}

const char* Error::what() const noexcept {
  return this->m_msg.c_str();
}

/** @param msg error message */
LogicError::LogicError(const std::string msg) noexcept
    : Error{msg} {}

/** @param msg error message */
ParsingError::ParsingError(const std::string msg) noexcept
    : Error{msg} {}

} // namespace chimp
