//
// Created by Miłosz on 22.11.2024.
//

#ifndef PEA2_LCSEARCHS_H
#define PEA2_LCSEARCHS_H
#include <vector>
#include <queue>
#include <climits>
#include "../../App/DistMatrix.h"
using namespace std;

class LCSearchS {
private:
    DistMatrix& distMatrix;
    int bestCost;
    vector<int> bestPath;

    struct Node {
        vector<int> path;
        int currentCost;
        int lowerBound;

        Node(vector<int> p, int cost, int bound)
                : path(std::move(p)), currentCost(cost), lowerBound(bound) {}

        bool operator>(const Node& other) const {
            return lowerBound > other.lowerBound;
        }
    };


    // Pomocnicza funkcja do obliczania dolnego ograniczenia
    int calculateLowerBound(int currentCost, const vector<int>& visited);

public:
    LCSearchS(DistMatrix& dm);
    void solve();
    void displayResult();
};


#endif //PEA2_LCSEARCHS_H
