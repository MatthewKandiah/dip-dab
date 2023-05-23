#include "imageHandler.hpp"
#include <string>

int main() {
  const std::string filename = "examples/sunset.png";
  const std::string outputFilename = "examples/sunset.example.png";
  const std::string opaqueOutputFilename = "examples/sunset.opaque.png";
  const std::string monochromeOutputFilename = "examples/sunset.monochrome.png";
  const std::string invertedOutputFilename = "examples/sunset.inverted.png";
  const std::string invertedMonochromeOutputFilename = "examples/sunset.monochrome.inverted.png";
  const std::string meanBlurredOutputFilename = "examples/sunset.mean_blurred.png";
  const std::string gaussianBlurred2OutputFilename = "examples/sunset.gaussian_blurred2.png";

  ImageHandler imageHandler = ImageHandler(filename);
  imageHandler.encodePng(outputFilename);

  ImageHandler opaqueImageHandler = imageHandler;
  opaqueImageHandler.makeOpaque();
  opaqueImageHandler.encodePng(opaqueOutputFilename);
  opaqueImageHandler.clear();
  
  ImageHandler monochromeOpaqueImageHandler = imageHandler;
  monochromeOpaqueImageHandler.convertToMonochrome();
  monochromeOpaqueImageHandler.encodePng(monochromeOutputFilename);
  monochromeOpaqueImageHandler.clear();

  ImageHandler invertedImageHandler = imageHandler;
  invertedImageHandler.invertImage();
  invertedImageHandler.encodePng(invertedOutputFilename);
  invertedImageHandler.clear();

  ImageHandler monochromeInvertedImageHandler = imageHandler;
  monochromeInvertedImageHandler.convertToMonochrome();
  monochromeInvertedImageHandler.invertImage();
  monochromeInvertedImageHandler.encodePng(invertedMonochromeOutputFilename);
  monochromeInvertedImageHandler.clear();

  ImageHandler meanBlurredImageHandler = imageHandler;
  meanBlurredImageHandler.convertToMonochrome();
  meanBlurredImageHandler.doMeanBlur();
  meanBlurredImageHandler.encodePng(meanBlurredOutputFilename);
  meanBlurredImageHandler.clear();

  ImageHandler gaussianBlurredImageHandler2 = imageHandler;
//  gaussianBlurredImageHandler2.convertToMonochrome();
  gaussianBlurredImageHandler2.doGaussianBlur(2);
  gaussianBlurredImageHandler2.encodePng(gaussianBlurred2OutputFilename);
  gaussianBlurredImageHandler2.clear();

  return 0;
}
