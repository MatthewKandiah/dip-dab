#ifndef PIXEL_H
#define PIXEL_H

#include <array>
#include <cstdint>
#include <stdint.h>

class Pixel {
  public:
    uint8_t r, g, b, a;
    
    Pixel(std::array<uint8_t, 4> x): 
      r(x[0]),
      g(x[1]),
      b(x[2]),
      a(x[3]) {};

    Pixel(uint8_t ri, uint8_t gi, uint8_t bi, uint8_t ai):
      r(ri),
      g(gi),
      b(bi),
      a(ai) {};

    std::array<uint8_t, 4> getRGBA() {
      return {r, g, b, a};
    }
};

#endif
