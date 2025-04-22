#ifndef LOWESTCOSTSEARCHAS_H
#define LOWESTCOSTSEARCHAS_H

#include <vector>
#include <queue>
#include <climits>
#include "../../App/DistMatrix.h"

using namespace std;

class LowestCostSearchAS {
private:
    DistMatrix& distMatrix;
    int bestCost;
    vector<int> bestPath;

    struct Node {
        vector<int> path;
        int currentCost;
        int lowerBound;

        // Konstruktor węzła
        Node(vector<int> p, int cost, int bound)
                : path(move(p)), currentCost(cost), lowerBound(bound) {}

        // Porównywanie w kolejce priorytetowej
        bool operator>(const Node& other) const {
            return lowerBound > other.lowerBound;
        }
    };

    // Pomocnicza funkcja do obliczania dolnego ograniczenia
    int calculateLowerBound(int currentCost, const vector<int>& visited);

public:
    LowestCostSearchAS(DistMatrix& dm);
    void solve();
    void displayResult();
};

#endif // LOWESTCOSTSEARCHAS_H