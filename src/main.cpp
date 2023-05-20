#include "imageHandler.hpp"
#include "lodepng/lodepng.h"
#include <cstdint>
#include <string>
#include <vector>

int main() {
  const std::string filename = "examples/sunset.png";
  const std::string outputFilename = "examples/sunset.example.png";

  ImageHandler imageHandler = ImageHandler(filename);
  imageHandler.encodePng(outputFilename);

  return 0;
}
