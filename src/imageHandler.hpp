#ifndef IMAGE_HANDLER_HPP
#define IMAGE_HANDLER_HPP

#include "image.hpp"
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

class ImageHandler {
public:
  ImageHandler(const std::string &filename) { decodePng(filename); }

  void decodePng(const std::string &filename);

  void encodePng(const std::string &filename);

  void clear();

  void convertToMonochrome();

  void invertImage();

  void makeOpaque();

  void doMeanBlur();

private:
  Image image;
};

#endif // IMAGE_HANDLER_HPP
