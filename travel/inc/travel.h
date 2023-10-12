#pragma once

#include <vector>

// This algorithm is aimed at finding the shortest way comprising all cities on a travel salesman way.
// The input is 2D array containing distances between any two cities (the value -1 means there is no way between such cities, whereas 0 denotes distance from a city to itself).

namespace travel {
int minLength(const std::vector<std::vector<int>>& W);
}