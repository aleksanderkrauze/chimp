#include <algorithm>
#include <sstream>
#include <string_view>
#include <utility>

#include "chimp/common.h"

#include "chimp/app.h"
#include "chimp/app_builder.h"
#include "chimp/exceptions.h"

namespace chimp {

/** @param builder AppBuilder that is used to create App */
App::App(AppBuilder&& builder)
    : m_name{std::move(builder.m_name)}
    , m_author{std::move(builder.m_author)}
    , m_version{std::move(builder.m_version)}
    , m_about{std::move(builder.m_about)}
    , m_args{std::move(builder.m_args)} {}

/** @param name Application's name */
AppBuilder App::builder(const std::string name) noexcept {
  return AppBuilder{name};
}

void App::parse(int argc, char const* const* argv) {
  for (auto i = 1; i < argc; ++i) {
    auto arg = std::string_view(argv[i]);

    if (arg.empty()) {
      std::ostringstream ss;
      ss << "argv[" << i << "] is empty";

      throw ParsingError{ss.str()};
    }

    if (arg[0] == '-') {
      if (arg.size() > 1) {
        if (arg[1] == '-') {
          // long argument
          arg.remove_prefix(2);

          if (arg.empty()) {
            std::ostringstream ss;
            ss << "argv[" << i << "] has empty long format";

            throw ParsingError{ss.str()};
          }

          const auto long_arg_matching = [arg](const auto argument) -> bool {
            const auto long_arg = argument->long_arg();
            if (long_arg) {
              return long_arg.value().compare(arg) == 0;
            }

            return false;
          };

          const auto arguments = this->m_args;
          const auto match = std::find_if(
            std::begin(arguments), std::end(arguments), long_arg_matching);

          if (match != std::end(arguments)) {
            match->get()->was_present(true);
          } else {
            std::ostringstream ss;
            ss << "Unknown argument --" << arg;

            throw ParsingError{ss.str()};
          }
        } else {
          // short argument(s)
          arg.remove_prefix(1);

          for (const char c : arg) {
            const auto short_arg_matching = [c](const auto argument) -> bool {
              const auto long_arg = argument->short_arg();
              if (long_arg) {
                return long_arg.value() == c;
              }

              return false;
            };

            const auto arguments = this->m_args;
            const auto match = std::find_if(
              std::begin(arguments), std::end(arguments), short_arg_matching);

            if (match != std::end(arguments)) {
              match->get()->was_present(true);
            } else {
              std::ostringstream ss;
              ss << "Unknown argument -" << c;

              throw ParsingError{ss.str()};
            }
          }
        }
      } else {
        std::ostringstream ss;
        ss << "argv[" << i << "] is empty";

        throw ParsingError{ss.str()};
      }
    } else {
      // ignore for now
    }
  }
}

} // namespace chimp
