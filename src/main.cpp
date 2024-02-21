#include "GMApp.hpp"
#include <iostream>

int main() {
  GMApp app;

  if(app.initialize(1280, 720, "Geimmeiker")) {
    app.run();
  } else {
    std::cerr << "Something went horribly wrong! L + ratio + skill issue.\n";
    return -1;
  }
  return 0;
}
