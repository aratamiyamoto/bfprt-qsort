#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <algorithm>
#include <limits>
#include <numeric>

#include "bfprt_qsort.hpp"

class RandomInitializer {
 public:
  template<typename ArraySorter, typename RandomAccessIterator>
  void operator()(RandomAccessIterator first, RandomAccessIterator last, ArraySorter sorter) {
    std::mt19937 mt(1234);  // Use a fixed seed for reproducibility.
    std::uniform_int_distribution<> rand_int(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

    std::generate(first, last, [&mt, &rand_int]{ return rand_int(mt); });
  }

  std::string getName() const {
    return "random";
  }
};

class QuicksortKillerInitializer {
  template<typename T>
  class QuicksortKillerCompare {
    std::map<int, int> keys;
    int candidate = 0;

   public:
    bool operator()(const T &x, const T &y) {
      if (!keys.count(x) && !keys.count(y)) {
        if (x == candidate) {
          keys[x] = keys.size();
        } else {
          keys[y] = keys.size();
        }
      }

      bool ret;
      if (!keys.count(x)) {
        candidate = x;
        ret = true;
      } else if (!keys.count(y)) {
        candidate = y;
        ret = false;
      } else {
        ret = (keys[x] >= keys[y]);
      }

      return ret;
    }
  };

 public:
  template<typename ArraySorter, typename RandomAccessIterator>
  void operator()(RandomAccessIterator first, RandomAccessIterator last, ArraySorter sorter) {
    std::iota(first, last, 0);
    using ElemType = typename std::iterator_traits<RandomAccessIterator>::value_type;
    sorter(first, last, QuicksortKillerCompare<ElemType>());
  }

  std::string getName() const {
    return "random";
  }
};

class StdSort {
 public:
  template<typename RandomAccessIterator, typename Compare = std::less<typename std::iterator_traits<RandomAccessIterator>::value_type> >
  void operator()(RandomAccessIterator first, RandomAccessIterator last, Compare comp = Compare()) {
    std::sort(first, last, comp);
  }

  std::string getName() const {
    return "std::sort";
  }
};

class BfprtQsort {
 public:
  template<typename RandomAccessIterator, typename Compare = std::less<typename std::iterator_traits<RandomAccessIterator>::value_type> >
  void operator()(RandomAccessIterator first, RandomAccessIterator last, Compare comp = Compare()) {
    sorting::bfprtQsort(first, last, comp);
  }

  std::string getName() const {
    return "bfprtQsort";
  }
};

template<typename ArraySorter, typename ArrayInitializer>
void profile(ArrayInitializer initializer, ArraySorter sorter, const int array_size, const int iterations=100) {
  std::vector<double> elapsed_times;
  std::vector<int> array(array_size);

  for (int i = 0; i < iterations; ++i) {
    // Initialize the array before starting the timer not to include the initialization time to the profiling results.
    initializer(array.begin(), array.end(), sorter);

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
  profile(RandomInitializer(), StdSort(), 100);
  profile(RandomInitializer(), StdSort(), 1000);
  profile(RandomInitializer(), StdSort(), 10000);
  profile(RandomInitializer(), StdSort(), 100000);
  profile(QuicksortKillerInitializer(), StdSort(), 100);
  profile(QuicksortKillerInitializer(), StdSort(), 1000);
  profile(QuicksortKillerInitializer(), StdSort(), 10000);
  profile(QuicksortKillerInitializer(), StdSort(), 100000);
  profile(RandomInitializer(), BfprtQsort(), 100);
  profile(RandomInitializer(), BfprtQsort(), 1000);
  profile(RandomInitializer(), BfprtQsort(), 10000);
  profile(RandomInitializer(), BfprtQsort(), 100000);

  return 0;
}