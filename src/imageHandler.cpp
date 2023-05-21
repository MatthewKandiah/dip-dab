#include "imageHandler.hpp"
#include "lodepng/lodepng.h"
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
    for (auto row: image.data) {
        for (auto pixel: row) {
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
    for (auto row: image.data) {
        for (auto pixel: row) {
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
    for (auto row: image.data) {
        for (auto pixel: row) {
            resultImageData.push_back(pixel.r);
            resultImageData.push_back(pixel.g);
            resultImageData.push_back(pixel.b);
            resultImageData.push_back(255);
        }
    }
    image = Image(resultImageData, image.width, image.height);
}

void ImageHandler::doMeanBlur() {
    std::vector<std::uint8_t> resultImageData;
    const std::int32_t kernelLeftBoundIndex = -2;
    const std::int32_t kernelRightBoundIndex = 2;
    const std::int32_t kernelUpperBoundIndex = 2;
    const std::int32_t kernelBottomBoundIndex = -2;
    for (auto rowIndex = 0; rowIndex < image.height; rowIndex++) {
        for (auto columnIndex = 0; columnIndex < image.width; columnIndex++) {
            std::vector<Pixel> kernelData;
            for (auto rowIndexDisplacement = kernelLeftBoundIndex;
                 rowIndexDisplacement <= kernelRightBoundIndex; rowIndexDisplacement++) {
                for (auto columnIndexDisplacement = kernelBottomBoundIndex;
                     columnIndexDisplacement <= kernelUpperBoundIndex; columnIndexDisplacement++) {
                    auto currentRowIndex = rowIndex + rowIndexDisplacement;
                    auto currentColumnIndex = columnIndex + columnIndexDisplacement;
                    if (currentRowIndex < 0 || currentRowIndex >= image.height || currentColumnIndex < 0 ||
                        currentColumnIndex >= image.width) {
                        // this is like adding an infinite transparent black border around the image
                        // there are probably smarter ways to handle kernels overflowing the edge of the image!
                        kernelData.push_back(Pixel(0, 0, 0, 0));
                    } else {
                        kernelData.push_back(image.data[currentRowIndex][currentColumnIndex]);
                    }
                }
            }
            auto kernel = Image(kernelData, kernelRightBoundIndex - kernelLeftBoundIndex + 1);
            auto resultR = 0;
            auto resultG = 0;
            auto resultB = 0;
            auto resultA = 0;
            auto kernelPixelCount = 0;
            for (auto kernelRow: kernel.data) {
                for (auto kernelPixel: kernelRow) {
                    resultR += kernelPixel.r;
                    resultG += kernelPixel.g;
                    resultB += kernelPixel.b;
                    resultA += kernelPixel.a;
                    kernelPixelCount++;
                }
            }
            resultR /= kernelPixelCount;
            resultG /= kernelPixelCount;
            resultB /= kernelPixelCount;
            resultA /= kernelPixelCount;
            resultImageData.push_back(resultR);
            resultImageData.push_back(resultG);
            resultImageData.push_back(resultB);
            resultImageData.push_back(resultA);
        }
    }
    image = Image(resultImageData, image.width, image.height);
}

// gaussian blur

// edge detection
