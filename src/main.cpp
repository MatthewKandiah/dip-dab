//#include "imageDecoder.hpp"
//#include "imageEncoder.hpp"
#include "lodepng/lodepng.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

class ImageEncoder {
public:
  void encodePng(const std::string &filename, std::vector<std::uint8_t> &image,
                 std::uint32_t &width, std::uint32_t &height){
   std::uint32_t error = lodepng::encode(filename.c_str(), image, width, height);

  if (error) {
    std::cout << "encoder error " << error << ": " << lodepng_error_text(error)
              << '\n';
  }
 };
};

class ImageDecoder {
public:
  void decodePng(const std::string &filename, std::vector<std::uint8_t> &image,
                 std::uint32_t &width, std::uint32_t &height){
   std::uint32_t error = lodepng::decode(image, width, height, filename.c_str());

  if (error) {
    std::cout << "decoder error " << error << ": " << lodepng_error_text(error)
              << '\n';
  }
 };
};

int main() {
  const std::string filename = "examples/sunset.png";
  const std::string outputFilename = "examples/sunset.example.png";

  std::vector<std::uint8_t> image;
  std::uint32_t width, height;

  ImageDecoder().decodePng(filename, image, width, height);
  ImageEncoder().encodePng(outputFilename, image, width, height);

  return 0;
}
