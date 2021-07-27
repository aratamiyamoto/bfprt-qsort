#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <string>
#include "bfprt_qsort.hpp"

using ::testing::ElementsAre;

class BfprtQsortTest : public ::testing::Test {
};

TEST_F(BfprtQsortTest, SortEmptyVector_DoNothing) {
    std::vector<int> vec{};

    sorting::bfprtQsort(vec.begin(), vec.end(), std::less<int>());
    // At least, it should not throw or not fail with a segmentation fault.
}

TEST_F(BfprtQsortTest, SortSingleElementVector_DoNothing) {
    std::vector<int> vec{1234};

    sorting::bfprtQsort(vec.begin(), vec.end(), std::less<int>());
    ASSERT_THAT(vec, ElementsAre(1234));
}

TEST_F(BfprtQsortTest, SortTwoElementVector_Sorted) {
    std::vector<int> vec{34, 12};

    sorting::bfprtQsort(vec.begin(), vec.end(), std::less<int>());
    ASSERT_THAT(vec, ElementsAre(12, 34));
}

TEST_F(BfprtQsortTest, SortTwoElementSortedVector_Sorted) {
    std::vector<int> vec{12, 34};

    sorting::bfprtQsort(vec.begin(), vec.end(), std::less<int>());
    ASSERT_THAT(vec, ElementsAre(12, 34));
}

TEST_F(BfprtQsortTest, SortVector_Sorted) {
    std::vector<int> vec{15, 13, 16, 10, 11, 17, 14, 12};

    sorting::bfprtQsort(vec.begin(), vec.end(), std::less<int>());
    ASSERT_THAT(vec, ElementsAre(10, 11, 12, 13, 14, 15, 16, 17));
}

TEST_F(BfprtQsortTest, SortReverselySortedVector_Sorted) {
    std::vector<int> vec{17, 16, 15, 14, 13, 12, 11, 10};

    sorting::bfprtQsort(vec.begin(), vec.end(), std::less<int>());
    ASSERT_THAT(vec, ElementsAre(10, 11, 12, 13, 14, 15, 16, 17));
}

TEST_F(BfprtQsortTest, SortSortedVectors_Sorted) {
    std::vector<int> vec{10, 11, 12, 13, 14, 15, 16, 17};

    sorting::bfprtQsort(vec.begin(), vec.end(), std::less<int>());
    ASSERT_THAT(vec, ElementsAre(10, 11, 12, 13, 14, 15, 16, 17));
}

TEST_F(BfprtQsortTest, SortVectorWithNonUniqueValues_Sorted) {
    std::vector<int> vec{12, 11, 13, 10, 10, 13, 12, 11};

    sorting::bfprtQsort(vec.begin(), vec.end(), std::less<int>());
    ASSERT_THAT(vec, ElementsAre(10, 10, 11, 11, 12, 12, 13, 13));
}

TEST_F(BfprtQsortTest, SortUniformVectorExceptForOneElement_Sorted) {
    std::vector<int> vec{11, 10, 10, 10, 10, 10, 10, 10};

    sorting::bfprtQsort(vec.begin(), vec.end(), std::less<int>());
    ASSERT_THAT(vec, ElementsAre(10, 10, 10, 10, 10, 10, 10, 11));
}

TEST_F(BfprtQsortTest, SortUniformVector_Sorted) {
    std::vector<int> vec{10, 10, 10, 10, 10, 10, 10, 10};

    sorting::bfprtQsort(vec.begin(), vec.end(), std::less<int>());
    ASSERT_THAT(vec, ElementsAre(10, 10, 10, 10, 10, 10, 10, 10));
}

TEST_F(BfprtQsortTest, SortStringVector_Sorted) {
    std::vector<std::string> vec{"fff", "ddd", "ggg", "aaa", "bbb", "hhh", "eee", "ccc"};

    sorting::bfprtQsort(vec.begin(), vec.end(), std::less<std::string>());
    ASSERT_THAT(vec, ElementsAre("aaa", "bbb", "ccc", "ddd", "eee", "fff", "ggg", "hhh"));
}

TEST_F(BfprtQsortTest, SortArray_Sorted) {
    int vec[]{15, 13, 16, 10, 11, 17, 14, 12};

    sorting::bfprtQsort(vec, vec + sizeof(vec) / sizeof(vec[0]), std::less<int>());
    ASSERT_THAT(vec, ElementsAre(10, 11, 12, 13, 14, 15, 16, 17));
}

TEST_F(BfprtQsortTest, SortVectorInDescendingOrder_Sorted) {
    std::vector<int> vec{15, 13, 16, 10, 11, 17, 14, 12};

    sorting::bfprtQsort(vec.begin(), vec.end(), std::greater<int>());
    ASSERT_THAT(vec, ElementsAre(17, 16, 15, 14, 13, 12, 11, 10));
}

TEST_F(BfprtQsortTest, SwapFirstAndLast_NoSideEffect) {
    std::vector<int> vec{15, 13, 16, 10, 11, 17, 14, 12};

    sorting::bfprtQsort(vec.end(), vec.begin(), std::less<int>());
    ASSERT_THAT(vec, ElementsAre(15, 13, 16, 10, 11, 17, 14, 12));
}