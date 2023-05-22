#ifndef KERNEL_HPP
#define KERNEL_HPP

#include "image.hpp"
#include <vector>

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
        for (const auto &row: data) {
            for (const auto &value: row) {
                result += abs(value);
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

#endif