#include "chimp/chimp.h"

int main(int argc, char* argv[]) {
  auto app = chimp::App::builder().build();
  app.parse(argc, argv);

  return 0;
}
