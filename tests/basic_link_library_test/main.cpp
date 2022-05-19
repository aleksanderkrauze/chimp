#include <cassert>

#include "chimp/chimp.h"

int main(int argc, char* argv[]) {
  std::shared_ptr<chimp::Arg> all_arg, num_arg;

  // clang-format off
  auto app = chimp::App::builder("test")
               .author("Aleksander Krauze")
               .version("1.0.0")
               .about("Simple app that doesn't do anything")
               .arg(
                  chimp::Arg::builder()
                    .short_arg('a')
                    .long_arg("all")
                    .build(all_arg)
                )
               .arg(
                  chimp::Arg::builder()
                    .short_arg('n')
                    .long_arg("number")
                    .build(num_arg)
               )
               .build();
  // clang-format on

  app.parse(argc, argv);

  // Use all_arg & num_arg
  assert(!all_arg->is_positional());
  assert(!num_arg->is_positional());

  return 0;
}
