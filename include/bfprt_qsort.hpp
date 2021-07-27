#ifndef __BFPRT_QSORT_HPP__
#define __BFPRT_QSORT_HPP__

#include <stack>

namespace sort {
    template <class RandomAccessIterator, class Compare>
    bfprtQsort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
       std::stack low_stack, high_stack;

       low_stack.push(first);
       high_stack.push(last - 1);

       while (!low_stack.is_empty() && !high_stack.is_empty()) {
           break;
       }
    }
}

#endif  // __BFPRT_QSORT_HPP__