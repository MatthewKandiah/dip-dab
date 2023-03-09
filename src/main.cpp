#include "decoder.h"
#include "encoder.h"
#include "greyscale_processor.h"
#include "lodepng/lodepng.h"
#include <bitset>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char **argv) {
  const std::string filename{argv[1]};

  Decoder decoder = Decoder(filename);
  std::cout << "image read successfully: width = " << decoder.width
            << ", height = " << decoder.height << '\n';

  GreyscaleProcessor greyscaleProcessor =
      GreyscaleProcessor(decoder.getImage());
  Image greyscaleImage = greyscaleProcessor.process();
  std::cout << "greyscale image produced in memory" << '\n';

  const std::string outputFilename{filename + ".grey.png"};
  Encoder encoder = Encoder(outputFilename, &greyscaleImage);
  encoder.encode();
  return 0;
}
