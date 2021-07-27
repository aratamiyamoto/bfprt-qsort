#ifndef __BFPRT_QSORT_HPP__
#define __BFPRT_QSORT_HPP__

#include <stack>

namespace sorting {
    template <class RandomAccessIterator, class Compare>
    RandomAccessIterator kth_smallest(RandomAccessIterator low, RandomAccessIterator high, typename std::iterator_traits<RandomAccessIterator>::difference_type k, Compare comp) {
        return high;
    }

    template <class RandomAccessIterator, class Compare>
    RandomAccessIterator partition(RandomAccessIterator low, RandomAccessIterator high, RandomAccessIterator pivot, Compare comp) {
        // Swap the pivot value to the highest index.
        swap(*pivot, *high);

        auto left = low;
        for (auto right = low; right < high; ++right) {
            // Move values smaller than pivot to left, lerger to right.
            if (comp(*right, *high)) {
                swap(*left, *right);
                ++left;
            }
        }

        // Swap back the pivot into the boundary between small values and large values.
        swap(*left, *high);

        // Return the position of the new pivot.
        return left;
    }

    template <class RandomAccessIterator, class Compare>
    void bfprtQsort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
        std::stack<RandomAccessIterator> low_stack, high_stack;

        low_stack.push(first);
        high_stack.push(last - 1);

        while (!low_stack.empty() && !high_stack.empty()) {
            auto low = low_stack.top();
            auto high = high_stack.top();
            low_stack.pop();
            high_stack.pop();

            if (low < high) {
                const auto n = std::distance(low, high) + 1;
                const auto med = kth_smallest(low, high, n / 2, comp);
                const auto pivot = partition(low, high, med, comp);

                const auto low_len = std::distance(low, pivot);
                const auto high_len = std::distance(pivot, high);

                decltype(low) next_low1, next_low2;
                decltype(high) next_high1, next_high2;
                if (low_len < high_len) {
                    next_low1 = pivot + 1;
                    next_low2 = low;
                    next_high1 = high;
                    next_high2 = pivot - 1;
                } else {
                    next_low1 = low;
                    next_low2 = pivot + 1;
                    next_high1 = pivot - 1;
                    next_high2 = high;
                }

                // Sort the shorter sub-array first.
                low_stack.push(next_low1);
                low_stack.push(next_low2);
                high_stack.push(next_high1);
                high_stack.push(next_high2);
            }
        }
    }
}

#endif  // __BFPRT_QSORT_HPP__