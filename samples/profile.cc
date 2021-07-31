#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include <limits>
#include <numeric>

#include "bfprt_qsort.hpp"

class RandomInitializer {
 public:
  template<typename RandomAccessIterator>
  void operator()(RandomAccessIterator first, RandomAccessIterator last) {
    std::mt19937 mt(1234);  // Use a fixed seed for reproducibility.
    std::uniform_int_distribution<> rand_int(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

    std::generate(first, last, [&mt, &rand_int]{ return rand_int(mt); });
  }

  std::string getName() const {
    return "random";
  }
};

class LibcQsort {
 public:
  template<typename RandomAccessIterator>
  void operator()(RandomAccessIterator first, RandomAccessIterator last) {
    int num = std::distance(first, last);
    qsort(&(*first), num, sizeof(int), [](const void *a, const void *b){ return *reinterpret_cast<const int*>(a) - *reinterpret_cast<const int*>(b); });
  }

  std::string getName() const {
    return "libc_qsort";
  }
};

class BfprtQsort {
 public:
  template<typename RandomAccessIterator>
  void operator()(RandomAccessIterator first, RandomAccessIterator last) {
    int num = std::distance(first, last);
    using ElemType = typename std::iterator_traits<RandomAccessIterator>::value_type;
    sorting::bfprtQsort(first, last, std::less<ElemType>());
  }

  std::string getName() const {
    return "bfprt_qsort";
  }
};

template<typename ArraySorter, typename ArrayInitializer>
void profile(ArrayInitializer initializer, ArraySorter sorter, const int array_size, const int iterations=100) {
  std::vector<double> elapsed_times;
  std::vector<int> array(array_size);

  for (int i = 0; i < iterations; ++i) {
    // Initialize the array before starting the timer not to include the initialization time to the profiling results.
    initializer(array.begin(), array.end());

    const auto start_time = std::chrono::steady_clock::now();
    sorter(array.begin(), array.end());
    const auto end_time = std::chrono::steady_clock::now();

    std::chrono::duration<decltype(elapsed_times)::value_type, std::milli> elapsed = end_time - start_time;
    elapsed_times.push_back(elapsed.count());
  }

  decltype(elapsed_times)::value_type average_elapsed = std::accumulate(elapsed_times.begin(), elapsed_times.end(), 0.0) / elapsed_times.size();
  std::cout << "[" << initializer.getName() << ", " << sorter.getName() << ", " << iterations << " iterations, " << array_size << " elements]: average=" << average_elapsed << "[ms]" << std::endl;
}

int main(int argc, char *argv[]) {
  profile(RandomInitializer(), LibcQsort(), 100);
  profile(RandomInitializer(), LibcQsort(), 1000);
  profile(RandomInitializer(), LibcQsort(), 10000);
  profile(RandomInitializer(), LibcQsort(), 100000);
  profile(RandomInitializer(), BfprtQsort(), 100);
  profile(RandomInitializer(), BfprtQsort(), 1000);
  profile(RandomInitializer(), BfprtQsort(), 10000);
  profile(RandomInitializer(), BfprtQsort(), 100000);

  return 0;
}