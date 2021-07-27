#include <iostream>
#include <string>
#include <vector>

#include "bfprt_qsort.hpp"

int main(int argc, char *argv[]) {
  std::vector<std::string> lines;
  for (std::string line; std::getline(std::cin, line);) {
    lines.push_back(line);
  }

  sorting::bfprtQsort(lines.begin(), lines.end(), std::greater<std::string>());

  for (auto &line : lines) {
    std::cout << line << std::endl;
  }

  return 0;
}
