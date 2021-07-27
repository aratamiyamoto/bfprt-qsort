#ifndef __BFPRT_QSORT_HPP__
#define __BFPRT_QSORT_HPP__

#include <stack>

namespace sorting {
    template <class RandomAccessIterator, class Compare>
    void bfprtQsort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
        std::stack<RandomAccessIterator> low_stack, high_stack;

        low_stack.push(first);
        high_stack.push(last - 1);

        while (!low_stack.empty() && !high_stack.empty()) {
            break;
        }
    }
}

#endif  // __BFPRT_QSORT_HPP__