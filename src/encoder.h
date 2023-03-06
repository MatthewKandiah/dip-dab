#include "lodepng/lodepng.h"
#include <vector>
#include <string>
#include <iostream>

class Encoder{
  public:
    std::string filename;
    unsigned width, height;
    std::vector<uint8_t> imageData;
    Encoder(std::string w, std::vector<uint8_t> x, unsigned y, unsigned z):
      filename(w),
      imageData(x),
      width(y),
      height(z) {}

    void encode(){
      unsigned error = lodepng::encode(filename, imageData, width, height);
      if (error) {
        std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << '\n';
      } else {
        std::cout << "png image successfully written to " <<  filename << '\n';
      }
    }
};
