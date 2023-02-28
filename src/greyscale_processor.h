#include <vector>
#include <array>

class GreyscaleProcessor {
  public: 
    std::vector<unsigned char> image;
    GreyscaleProcessor(std::vector<unsigned char> x) {
      image = x;
    };

    std::vector<unsigned char> process() {
      std::vector<unsigned char> result {};
      std::array<unsigned long, 4> buffer;
      int bufferCount = 0;
      for (unsigned long number : image) {
        buffer[bufferCount] = number;

        if (bufferCount == 3) {
          unsigned char mean = static_cast<char>(buffer[0] + buffer[1] + buffer[2]) / 3;
          unsigned char alpha = static_cast<char>(buffer[3]);
          result.push_back(mean);
          result.push_back(mean);
          result.push_back(mean);
          result.push_back(alpha);
        }

        bufferCount++;
        bufferCount %= 4;
      }

      return result;
    }
 };
