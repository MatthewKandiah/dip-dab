#include "imageHandler.hpp"
#include "lodepng/lodepng.h"
#include <cstdint>
#include <string>
#include <vector>

int main() {
  const std::string filename = "examples/sunset.png";
  const std::string outputFilename = "examples/sunset.example.png";

  std::vector<std::uint8_t> image;
  std::uint32_t width, height;

  ImageHandler().decodePng(filename, image, width, height);
  ImageHandler().encodePng(outputFilename, image, width, height);

  return 0;
}
