#include <iostream>
#include <string>
#include <vector>
#include "lodepng.h"
#include "decoder.h"

int main(int argc, char** argv) {
  const std::string filename {argv[1]};
  Decoder decoder = Decoder(filename);

  std::cout << "image read successfully: width = " << decoder.width << ", height = " << decoder.height << '\n';
  return 0;
}

