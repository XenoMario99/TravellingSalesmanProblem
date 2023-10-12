#include "travel.h"

#include <algorithm>
#include <iostream>
#include <limits>

namespace {

struct Path {
    int distance;
    std::vector<int> subset;

    Path() : distance(0), subset{} {}
    Path(int val, const std::vector<int>& s) : distance(val), subset(s) {}
    ~Path() {}
};

void prepare(int n, int pathLength, std::vector<Path>& vec) {
    if (pathLength == n - 1) {
        std::vector<int> temp;
        temp.reserve(n);

        for (int i = 0; i < n; i++) {
            temp.push_back(i + 1);
        }

        vec.push_back(Path(0, temp));
        return;
    }

    int sizeMinusFirstElem = n - 1;
    int left = sizeMinusFirstElem - pathLength;

    for (int i = 1; i < n; i++) {
        int bitmask{0};
        bitmask |= (1 << i);

        for (int j = 1; j <= left; j++) {
            std::vector<int> temp;
            temp.reserve(left);
            temp.push_back(i + 1);

            for (int k = 0; k < pathLength; k++) {
                for (int m = 1; m < n; m++) {
                    if (!(bitmask & (1 << m))) {
                        temp.push_back(m + 1);
                        bitmask |= (1 << m);
                        break;
                    }
                }
            }
            vec.push_back(Path(0, temp));
        }
    }
}

bool compareVec(const std::vector<int>& vec1, const std::vector<int>& vec2) {
    const unsigned long size{vec1.size()};
    if (size != vec2.size() || vec1[0] != vec2[0]) {  // First element of both vectors must be the same. The order of the rest elements of both vectors has no meaning due to principle of optimality
        return false;
    }

    int bitmask1{0}, bitmask2{0};

    for (int i = 1; i < size; i++) {
        bitmask1 |= (1 << vec1[i]);
        bitmask2 |= (1 << vec2[i]);
    }

    return bitmask1 == bitmask2;
}

}  // namespace

int travel::minLength(const std::vector<std::vector<int>>& W) {
    if (W.size() != W[0].size()) {
        std::cerr << "Wrong argument" << std::endl;
        return -1;
    }

    const int vertices = W.size();
    std::vector<std::vector<Path>> D{std::vector<std::vector<Path>>(vertices, std::vector<Path>{})};

    for (int i = 1; i < vertices; i++) {
        D[0].push_back(Path(W[i][0], {i + 1}));
    }

    int i{1}, j{0};
    for (i; i < vertices; i++) {  // starts from 1 since first iteration is done separately
        int subsetAmount{1};

        for (int m = vertices - 1; m >= i + 1; m--) {
            subsetAmount *= m;
        }

        D[i].reserve(subsetAmount);

        prepare(vertices, i, D[i]);  // Prepare all possible sets on which we operate later

        for (j; j < subsetAmount; j++) {
            int min{std::numeric_limits<int>::max()};
            const auto subsetLength{D[i][j].subset.size() - 1};

            int startVertex{D[i][j].subset[0]};

            std::vector<int> subgroup{D[i][j].subset.begin() + 1, D[i][j].subset.end()};

            int n{0};
            auto rotate = [n, &subgroup, &subsetLength]() mutable {  // Rotate function to use all possible combination during process of finding the shortest way
                auto beg = subgroup.begin();
                int ref{*beg};
                auto end = --subgroup.end();

                auto aux = subgroup.begin();

                while (beg != end) {
                    *beg = *(beg + 1);
                    beg++;
                }

                *(subgroup.end() - 1) = ref;
                n++;

                return n >= subsetLength ? false : true;
            };

            do {
                int firstElem{subgroup[0]};
                int distanceA{W[startVertex - 1][firstElem - 1]};  // indexing starts at 0

                int setNum{0};
                while (!compareVec(D[i - 1][setNum].subset, subgroup)) {  // Need own compare function because vectors order doest not matter
                    setNum++;
                }

                int distanceB{D[i - 1][setNum].distance};

                if ((distanceA == -1 || distanceB == -1)) {
                    continue;
                } else if (min > distanceA + distanceB) {
                    min = distanceA + distanceB;
                }
            } while (rotate());

            if (min == std::numeric_limits<int>::max()) {
                min = -1;
            }
            D[i][j].distance = min;
        }
        j = 0;
    }

    return D.at(i - 1).at(j).distance;
}