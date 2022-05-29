#include <iostream>

#include <chimp/chimp.h>

int main(int argc, char* argv[]) {
  try {
    std::shared_ptr<chimp::Arg> all_arg, num_arg;

    // clang-format off
    auto app = chimp::App::builder("test")
                 .author("Aleksander Krauze")
                 .version("1.0.0")
                 .about("Simple app that doesn't do anything")
                 .arg(
                    chimp::Arg::builder("all")
                      .short_arg('a')
                      .long_arg("all")
                      .build(all_arg)
                  )
                 .arg(
                    chimp::Arg::builder("number")
                      .short_arg('n')
                      .long_arg("number")
                      .takes_value(true)
                      .build(num_arg)
                 )
                 .build();
    // clang-format on

    app.parse(argc, argv);
  } catch (const chimp::Error& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }

  // Use parsed arguments

  return 0;
}
