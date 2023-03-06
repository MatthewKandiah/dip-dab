#include <array>
#include <stdint.h>

class Pixel {
  public:
    int8_t r, g, b, a;
    
    Pixel(std::array<int8_t, 4> x): 
      r(x[0]),
      g(x[1]),
      b(x[2]),
      a(x[3]) {};

    Pixel(int8_t ri, int8_t gi, int8_t bi, int8_t ai):
      r(ri),
      g(gi),
      b(bi),
      a(ai) {};
};
