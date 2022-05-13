#include "chimp/chimp.h"

int main(int argc, char* argv[]) {
  auto app = chimp::App::builder("test")
               .author("Aleksander Krauze")
               .version("1.0.0")
               .about("Simple app that doesn't do anything")
               .build();

  app.parse(argc, argv);

  return 0;
}
