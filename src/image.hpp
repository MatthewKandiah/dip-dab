#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <cstdint>
#include <vector>
#include "pixel.hpp"

class Image {
public:
    Image() : width(), height() {};

    Image(std::vector<std::uint8_t> imageData, std::uint32_t width, std::uint32_t height) {
        this->width = width;
        this->height = height;
        std::vector<Pixel> row;
        for (auto i = 0; i < height; i++) {
            for (auto j = 0; j < width; j++) {
                auto currentPosition = 4 * (width * i + j);
                const std::uint8_t r = imageData[currentPosition];
                const std::uint8_t g = imageData[currentPosition + 1];
                const std::uint8_t b = imageData[currentPosition + 2];
                const std::uint8_t a = imageData[currentPosition + 3];
                row.push_back(Pixel(r, g, b, a));
            }
            data.push_back(row);
            row.clear();
        }
    }

    std::vector<std::vector<Pixel> > data;

    std::uint32_t width, height;

    std::vector<std::uint8_t> toFlatVector() {
        std::vector<std::uint8_t> result;
        for (auto row : data) {
            for (auto pixel : row) {
                result.push_back(pixel.r);
                result.push_back(pixel.g);
                result.push_back(pixel.b);
                result.push_back(pixel.a);
            }
        }
        return result;
    }
};

#endif