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

void ImageHandler::clear() {
    image = Image();
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
// given a standard deviation, and a set peak of 1, calculate the kernel size to get edge value < 0.01, then generate kernel, then apply

// edge detection
// need to do the left-right edge detection, then the up-down edge detection, then add them in quadrature
// NOTE - new complexity here, this transformation requires calculating multiple kernels for each pixel, can either generate 2 images then combine
//        but probably better to calculate both values in the loop over pixels, and generate a single image
