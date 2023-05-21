#include "imageHandler.hpp"
#include <string>

int main() {
    const std::string filename = "examples/sunset.png";
    const std::string outputFilename = "examples/sunset.example.png";
    const std::string opaqueOutputFilename = "examples/sunset.opaque.png";
    const std::string monochromeOutputFilename = "examples/sunset.monochrome.png";
    const std::string invertedOutputFilename = "examples/sunset.inverted.png";
    const std::string meanBlurredOutputFilename = "examples/sunset.mean_blurred.png";

    ImageHandler imageHandler = ImageHandler(filename);
    imageHandler.encodePng(outputFilename);
    imageHandler.makeOpaque();
    imageHandler.encodePng(opaqueOutputFilename);
    imageHandler.convertToMonochrome();
    imageHandler.encodePng(monochromeOutputFilename);
    imageHandler.invertImage();
    imageHandler.encodePng(invertedOutputFilename);
    imageHandler.invertImage();
    imageHandler.doMeanBlur();
    imageHandler.encodePng(meanBlurredOutputFilename);

    return 0;
}
