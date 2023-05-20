#ifndef IMAGE_HANDLER_HPP
#define IMAGE_HANDLER_HPP

#include <cstdint>
#include <string>
#include <utility>
#include <vector>
#include "image.hpp"

class ImageHandler {
public:
    ImageHandler(const std::string &filename) { decodePng(filename); }

    void decodePng(const std::string &filename);

    void encodePng(const std::string &filename);

    void convertToMonochrome();

    void invertImage();

    void makeOpaque();

private:
    Image image;
};

#endif // IMAGE_HANDLER_HPP
