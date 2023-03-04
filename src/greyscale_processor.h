#include <vector>
#include <array>

class GreyscaleProcessor {
  public: 
    std::vector<unsigned char> image;
    GreyscaleProcessor(std::vector<unsigned char> x):
      image(x) {} 

    std::vector<unsigned char> process() {
      std::vector<unsigned char> result {};
      std::array<unsigned long, 4> buffer;
      int bufferCount = 0;
      for (unsigned long number : image) {
        buffer[bufferCount] = number;
        flushBuffertoResultIfNecessary(bufferCount, buffer, result);
        bufferCount++;
        bufferCount %= 4;
      }
      return result;
    }

  private:
    unsigned char greyscaleWeightedAverage(const std::array<unsigned long, 4> &buffer) {
      // greyscale weighted average formula taken from https://goodcalculators.com/rgb-to-grayscale-conversion-calculator/
      return static_cast<char>(0.299*buffer[0] + 0.587*buffer[1] + 0.114*buffer[2]);
    }

    void flushBuffertoResultIfNecessary(
        int &bufferCount,
        std::array<unsigned long, 4> &buffer,
        std::vector<unsigned char> &result
        ) {
      if (bufferCount == 3) {
        unsigned char grey = greyscaleWeightedAverage(buffer);
        unsigned char alpha = buffer[3];
        for (int i = 0; i < 3; i++){
          result.push_back(grey);
        }
        result.push_back(alpha);
      } 
    }
 };
