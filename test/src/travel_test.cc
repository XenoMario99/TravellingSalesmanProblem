#include "travel.h"

#include <gtest/gtest.h>

TEST(TravelSalesmanProblemTest, AlgorithmResultWithGiven2DArr_ok) {
    std::vector<std::vector<int>> tab{std::vector<std::vector<int>>(4, std::vector<int>(4, 0))};

    tab[0][0] = 0;
    tab[0][1] = 2;
    tab[0][2] = 9;
    tab[0][3] = -1;
    tab[1][0] = 1;
    tab[1][1] = 0;
    tab[1][2] = 6;
    tab[1][3] = 4;
    tab[2][0] = -1;
    tab[2][1] = 7;
    tab[2][2] = 0;
    tab[2][3] = 8;
    tab[3][0] = 6;
    tab[3][1] = 3;
    tab[3][2] = -1;
    tab[3][3] = 0;

    int result = travel::minLength(tab);

    ASSERT_EQ(result, 21);
}