#include <vector>
#include <array>

class Filter {
  const int width, height;
  std::vector<std::vector<int>> data;
  Filter(std::vector<std::vector<int>> x):
    data(x),
    width(x.size()),
    height(x[0].size()) {}

  // TODO public function to apply filter to a passed in pixel neighborhood, returning new pixel value
};
