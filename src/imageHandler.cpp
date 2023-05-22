#include "imageHandler.hpp"
#include "lodepng/lodepng.h"
#include "kernel.hpp"
#include <iostream>

void ImageHandler::decodePng(const std::string &filename) {
    std::vector<std::uint8_t> imageData;
    std::uint32_t width, height;
    std::uint32_t error = lodepng::decode(imageData, width, height, filename);

    if (error) {
        std::cout << "decoder error " << error << ": " << lodepng_error_text(error)
                  << '\n';
    } else {
        image = Image(imageData, width, height);
    }
}

void ImageHandler::encodePng(const std::string &filename) {
    std::uint32_t error = lodepng::encode(filename, image.toFlatVector(), image.width, image.height);

    if (error) {
        std::cout << "encoder error " << error << ": " << lodepng_error_text(error)
                  << '\n';
    }
}

void ImageHandler::convertToMonochrome() {
    std::vector<std::uint8_t> resultImageData;
    for (const auto &row: image.data) {
        for (const auto &pixel: row) {
            const auto grey = static_cast<std::uint8_t>(0.299 * pixel.r + 0.587 * pixel.g + 0.114 * pixel.b);
            resultImageData.push_back(grey);
            resultImageData.push_back(grey);
            resultImageData.push_back(grey);
            resultImageData.push_back(pixel.a);
        }
    }
    image = Image(resultImageData, image.width, image.height);
}

void ImageHandler::invertImage() {
    std::vector<std::uint8_t> resultImageData;
    for (const auto &row: image.data) {
        for (const auto &pixel: row) {
            resultImageData.push_back(255 - pixel.r);
            resultImageData.push_back(255 - pixel.g);
            resultImageData.push_back(255 - pixel.b);
            resultImageData.push_back(pixel.a);
        }
    }
    image = Image(resultImageData, image.width, image.height);
}

void ImageHandler::makeOpaque() {
    std::vector<std::uint8_t> resultImageData;
    for (const auto &row: image.data) {
        for (const auto &pixel: row) {
            resultImageData.push_back(pixel.r);
            resultImageData.push_back(pixel.g);
            resultImageData.push_back(pixel.b);
            resultImageData.push_back(255);
        }
    }
    image = Image(resultImageData, image.width, image.height);
}

void ImageHandler::doMeanBlur() {
    std::vector<int32_t> row = {1, 1, 1, 1, 1};
    std::vector<std::vector<int32_t> > kernelData = {row, row, row, row, row};

    auto kernel = Kernel(kernelData);
    image = kernel.apply(image);
}

// gaussian blur

// edge detection
