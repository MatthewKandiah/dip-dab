#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include "lodepng.h"
#include "decoder.h"
#include "encoder.h"
#include "greyscale_processor.h"

int main(int argc, char** argv) {
  const std::string filename {argv[1]};

  Decoder decoder = Decoder(filename);
  std::cout << "image read successfully: width = " << decoder.width << ", height = " << decoder.height << '\n';

  GreyscaleProcessor greyscaleProcessor = GreyscaleProcessor(decoder.image);
  const std::vector<unsigned char> greyscaleImage = greyscaleProcessor.process();
  std::cout << "greyscale image produced in memory" << '\n';
  
  const std::string outputFilename {filename + ".grey.png"};
  std::cout << "expected outputFilename " << outputFilename << '\n'; 
  Encoder encoder = Encoder(outputFilename, greyscaleImage, decoder.width, decoder.height);
  encoder.encode();
  return 0;
}

