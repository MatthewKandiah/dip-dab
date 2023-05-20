#ifndef IMAGE_HANDLER_HPP
#define IMAGE_HANDLER_HPP

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

class ImageHandler {
public:
    ImageHandler(const std::string &filename) { decodePng(filename); }

    ImageHandler(std::vector<std::uint8_t> imageData, std::uint32_t w,
                 std::uint32_t h) {
        image = std::move(imageData);
        width = w;
        height = h;
    }

    void decodePng(const std::string &filename);

    void encodePng(const std::string &filename);

    void convertToMonochrome();

    void invertImage();

private:
    std::vector<std::uint8_t> image;
    std::uint32_t width = 0;
    std::uint32_t height = 0;
};

#endif // IMAGE_HANDLER_HPP
