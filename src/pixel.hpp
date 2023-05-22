#ifndef PIXEL_HPP
#define PIXEL_HPP

#include <cstdint>

class Pixel {
public:
    Pixel() {}

    Pixel(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha) {
        r = red;
        g = green;
        b = blue;
        a = alpha;
    }

    std::uint8_t r, g, b, a;
};

#endif