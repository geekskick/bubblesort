#include "gtest/gtest.h"
#include "fmt/format.h"
#include "fmt/ranges.h"
#include "bubblesort.hpp"
#include "makearray.hpp"

TEST(sorts, sortsArray){
    constexpr auto unsorted = make_array<int>(8,7,6,5,4,3,2,1);
    const auto sorted = bubblesort(unsorted);

    ASSERT_TRUE(std::is_sorted(sorted.cbegin(), sorted.cend()));
}

TEST(sorts, sortsVector){
    const auto unsorted = std::vector<int>{8,7,6,5,4,3,2,1};
    const auto sorted = bubblesort(unsorted);
    ASSERT_TRUE(std::is_sorted(sorted.cbegin(), sorted.cend()));
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
