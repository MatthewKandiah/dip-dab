#include "imageHandler.hpp"
#include "lodepng/lodepng.h"
#include "kernel.hpp"
#include <iostream>
#include <math.h>

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
    std::vector<double> row = {1, 1, 1, 1, 1};
    std::vector<std::vector<double> > kernelData = {row, row, row, row, row};

    auto kernel = Kernel(kernelData);
    image = kernel.apply(image);
}

double gaussian(double x, double sigma) {
    return std::exp(-(x * x) / (sigma * sigma));
}

void ImageHandler::doGaussianBlur(double sigma) {
// reasonable upper bound on the dimensions of the N x N kernel is N <= 3sigma
//    auto gaussian = [sigma](double x) { return std::exp(-(x * x) / (sigma * sigma)); };
    std::int32_t kernelDimension = 0;
    auto result = gaussian(kernelDimension, sigma);
    while (result >= 0.01) {
        kernelDimension++;
        result = gaussian(kernelDimension, sigma);
//        std::cout << result << ' ' << kernelDimension << '\n';
    }

    std::vector<std::vector<double>> kernelData;
    for (auto rowIndex = 0; rowIndex < kernelDimension; rowIndex++) {
        std::vector<double> row{};
        for (auto columnIndex = 0; columnIndex < kernelDimension; columnIndex++) {
            double distance = std::sqrt(rowIndex * rowIndex + columnIndex * columnIndex);
//            std::cout << "rowIndex " << rowIndex << " columnIndex " << columnIndex << " distance " << distance << '\n';
            row.push_back(gaussian(distance, sigma));
        }
        kernelData.push_back(row);
        row.clear();
    }
    auto kernel = Kernel(kernelData);
//    std::cout << "kernel built\n";
    image = kernel.apply(image);
    std::cout << "image updated\n";
}

// edge detection
// need to do the left-right edge detection, then the up-down edge detection, then add them in quadrature
// NOTE - new complexity here, this transformation requires calculating multiple kernels for each pixel, can either generate 2 images then combine
//        but probably better to calculate both values in the loop over pixels, and generate a single image
