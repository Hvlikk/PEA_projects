#ifndef PEA2_DFSSEARCHAS_H
#define PEA2_DFSSEARCHAS_H
#include "../../App/DistMatrix.h"
#include <vector>
#include <climits>
#include <iostream>
#include <utility> // for std::pair

class DFSSearchAS {
private:
    const DistMatrix& distanceMatrix; // Odwołanie do macierzy odległości
    int bestCost; // Najlepszy koszt (długość trasy)
    std::vector<int> bestPath; // Najlepsza trasa
    std::vector<bool> visited; // Tablica odwiedzonych miast

    int reduceMatrix(int** matrix, int size); // Redukcja macie    int n = distanceMatrix.getSize();
    void branchAndBound(int** matrix, int currentCity, int depth, int currentCost, std::vector<int>& currentPath);

public:
    explicit DFSSearchAS(const DistMatrix& dm);
    void solve();
    void displayResult() const;
};
#endif //PEA2_DFSSEARCHAS_H