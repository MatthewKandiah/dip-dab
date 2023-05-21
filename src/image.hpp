#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <cstdint>
#include <utility>
#include <vector>
#include <exception>
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
        if (data.empty()) {
            throw std::invalid_argument("Image data empty");
        }
        if (data.size() != height) {
            throw std::invalid_argument("Image height does not match image data");
        }
        if (data[0].size() != width) {
            throw std::invalid_argument("Image width does not match image data");
        }
    }

    Image(const std::vector<Pixel>& newData, std::uint32_t newWidth) {
        if (newData.empty()) {
            throw std::invalid_argument("Image data cannot be empty");
        }
        std::vector<std::vector<Pixel> > result;
        std::vector<Pixel> row;
        for (auto pixel : newData) {
            row.push_back(pixel);
            if (row.size() >= newWidth) {
                result.push_back(row);
                row.clear();
            }
        }
        data = result;
        height = data.size();
        width = data[0].size();
        if (width != newWidth) {
            throw std::invalid_argument("Something went wrong, argument width does not match output width");
        }
    }

    std::vector<std::vector<Pixel> > data;

    std::uint32_t width, height;

    std::vector<std::uint8_t> toFlatVector() {
        std::vector<std::uint8_t> result;
        for (auto row: data) {
            for (auto pixel: row) {
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