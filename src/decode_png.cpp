#include <iostream>
#include <string>
#include <vector>
#include "lodepng.h"

int main(int argc, char** argv) {
  const std::string filename {argv[1]};
  std::vector<unsigned char> image; // the raw pixels
  unsigned width, height;

  // decode
  unsigned error = lodepng::decode(image, width, height, filename);
  if (error) {
    std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    return 1;
  } 
  std::cout << "image read successfully: width = " << width << ", height = " << height << std::endl;
  return 0;
}

