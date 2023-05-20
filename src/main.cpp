#include "imageHandler.hpp"
#include <string>

int main() {
    const std::string filename = "examples/sunset.png";
    const std::string outputFilename = "examples/sunset.example.png";
    const std::string monochromeOutputFilename = "examples/sunset.monochrome.png";
    const std::string invertedOutputFilename = "examples/sunset.inverted.png";

    ImageHandler imageHandler = ImageHandler(filename);
    imageHandler.encodePng(outputFilename);
    imageHandler.convertToMonochrome();
    imageHandler.encodePng(monochromeOutputFilename);
    imageHandler.invertImage();
    imageHandler.encodePng(invertedOutputFilename);

    return 0;
}
