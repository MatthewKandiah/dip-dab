#include "lodepng/lodepng.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>


void decodeOneStep(const char *filename, std::vector<unsigned char> &image, unsigned &width, unsigned &height) {
  unsigned error = lodepng::decode(image, width, height, filename);

  if (error)
    std::cout << "decoder error " << error << ": " << lodepng_error_text(error)
              << '\n';
}

void encodeOneStep(const char *filename, std::vector<unsigned char> &image,
                   unsigned &width, unsigned &height) {
  unsigned error = lodepng::encode(filename, image, width, height);

  if (error)
    std::cout << "encoder error" << error << ": " << lodepng_error_text(error)
              << '\n';
}

int main() {
  const std::string filename = "examples/sunset.png";
  const std::string outputFilename = "examples/sunset.example.png";

  std::vector<unsigned char> image;
  unsigned width, height;

  decodeOneStep(filename.c_str(), image, width, height);
  encodeOneStep(outputFilename.c_str(), image, width, height);

  return 0;
}
