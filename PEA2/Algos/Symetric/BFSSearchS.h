//
// Created by Miłosz on 22.11.2024.
//

#ifndef PEA2_BFSSEARCHS_H
#define PEA2_BFSSEARCHS_H
#include "../../App/DistMatrix.h"
#include "vector"

class BFSSearchS {
private:
    const DistMatrix& distanceMatrix; // Odwołanie do macierzy odległości
    int bestCost;                     // Najlepszy koszt trasy
    std::vector<int> bestPath;        // Najlepsza trasa

    int calculateLowerBound(int currentCost, const std::vector<bool>& visited) const; // Obliczanie dolnego ograniczenia

public:
    explicit BFSSearchS(const DistMatrix& dm);
    void solve();        // Rozwiązanie problemu
    void displayResult() const; // Wyświetlenie wyników
};


#endif //PEA2_BFSSEARCHS_H
