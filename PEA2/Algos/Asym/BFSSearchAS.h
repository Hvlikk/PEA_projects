//
// Created by Miłosz on 03.11.2024.
//

#ifndef PEA2_BFSSEARCH_H
#define PEA2_BFSSEARCH_H
#include "../../App/DistMatrix.h"
#include "vector"

class BFSSearchAS {
private:
    const DistMatrix& distanceMatrix; // Odwołanie do macierzy odległości
    int bestCost;                     // Najlepszy koszt trasy
    std::vector<int> bestPath;        // Najlepsza trasa

    int calculateLowerBound(int currentCost, const std::vector<bool>& visited) const; // Obliczanie dolnego ograniczenia
    int reduceMatrix(int** matrix, int size) const;
public:
    explicit BFSSearchAS(const DistMatrix& dm);
    void solve();        // Rozwiązanie problemu
    void displayResult() const; // Wyświetlenie wyników
};

#endif // BRANCH_AND_BOUND_TSP_H

