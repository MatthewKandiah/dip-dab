#include "imageHandler.hpp"
#include "lodepng/lodepng.h"
#include <iostream>
#include <utility>

// TODO - move to its own sensible file
class Kernel {
public:
    Kernel(std::vector<std::vector<std::int32_t> > newData) {
        data = std::move(newData);
    }

    std::vector<std::vector<std::int32_t> > data;

    std::size_t width() { return data[0].size(); } // must be odd to be sensibly centred on pixel

    std::size_t height() { return data.size(); } // must be odd to be sensibly centred on pixel

    std::int32_t rightBoundary() {
        return static_cast<std::int32_t>(0.5 * static_cast<double>(width() - 1));
    }

    std::int32_t upperBoundary() {
        return static_cast<std::int32_t>(0.5 * static_cast<double>(height() - 1));
    }

    std::int32_t leftBoundary() {
        return -rightBoundary();
    }

    std::int32_t lowBoundary() {
        return -upperBoundary();
    }

    std::int32_t getNormalisationFactor() {
        auto result = 0;
        for (auto row: data) {
            for (auto value: row) {
                result += value;
            }
        }
        return result;
    }

    Image apply(const Image &image) {
        std::vector<Pixel> resultPixelData;
        for (auto rowIndex = 0; rowIndex < image.data.size(); rowIndex++) {
            for (auto columnIndex = 0; columnIndex < image.data[0].size(); columnIndex++) {
                resultPixelData.push_back(applyToPixel(image, columnIndex, rowIndex));
            }
        }
        return Image(resultPixelData, image.width);
    }

private:
    Pixel applyToPixel(const Image &image, std::size_t columnIndex, std::size_t rowIndex) {
        std::int32_t resultR = 0, resultG = 0, resultB = 0, resultA = 0;

        for (auto kernelColumnPosition = leftBoundary();
             kernelColumnPosition <= rightBoundary(); kernelColumnPosition++) {
            for (auto kernelRowPosition = lowBoundary(); kernelRowPosition <= upperBoundary(); kernelRowPosition++) {
                const auto kernelValue = data[kernelRowPosition][kernelColumnPosition];
                auto imageColumnPosition = static_cast<std::int32_t>(columnIndex + kernelColumnPosition);
                auto imageRowPosition = static_cast<std::int32_t>(rowIndex + kernelRowPosition);
                Pixel currentPixel;
                if (imageColumnPosition < 0 || imageColumnPosition >= image.width || imageRowPosition < 0 ||
                    imageRowPosition >= image.height) {
                    // effectively adds an infinite, transparent, black border around the image to handle the edges
                    currentPixel = Pixel(0, 0, 0, 0);
                } else {
                    currentPixel = image.data[imageRowPosition][imageColumnPosition];
                }
                resultR += kernelValue * currentPixel.r;
                resultG += kernelValue * currentPixel.g;
                resultB += kernelValue * currentPixel.b;
                resultA += kernelValue * currentPixel.a;
            }
        }
        const auto normalisationFactor = getNormalisationFactor();
        resultR /= normalisationFactor;
        resultG /= normalisationFactor;
        resultB /= normalisationFactor;
        resultA /= normalisationFactor;
        return Pixel(resultR, resultG, resultB, resultA);
    }
};

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
    std::vector<int32_t> row = {1,1,1,1,1};
    std::vector<std::vector<int32_t> > kernelData = {row, row, row, row, row};

    auto kernel = Kernel(kernelData);
    image = kernel.apply(image);
}

// gaussian blur

// edge detection
