#include "imageHandler.hpp"
#include <string>

int main() {
  const std::string filename = "examples/sunset.png";
  const std::string outputFilename = "examples/sunset.example.png";
  const std::string opaqueOutputFilename = "examples/sunset.opaque.png";
  const std::string monochromeOutputFilename = "examples/sunset.monochrome.png";
  const std::string invertedOutputFilename = "examples/sunset.inverted.png";
  const std::string meanBlurredOutputFilename =
      "examples/sunset.mean_blurred.png";

  ImageHandler imageHandler = ImageHandler(filename);
  imageHandler.encodePng(outputFilename);
  imageHandler.makeOpaque();
  imageHandler.encodePng(opaqueOutputFilename);
  
  ImageHandler monochromeOpaqueImageHandler = imageHandler;
  monochromeOpaqueImageHandler.convertToMonochrome();
  monochromeOpaqueImageHandler.encodePng(monochromeOutputFilename);

  ImageHandler invertedImageHandler = imageHandler;
  invertedImageHandler.invertImage();
  invertedImageHandler.encodePng(invertedOutputFilename);

  ImageHandler meanBlurredImageHandler = imageHandler;
  meanBlurredImageHandler.doMeanBlur();
  meanBlurredImageHandler.encodePng(meanBlurredOutputFilename);

  return 0;
}
