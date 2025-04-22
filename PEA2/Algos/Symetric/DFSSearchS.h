//
// Created by Miłosz on 22.11.2024.
//

#ifndef PEA2_DFSSEARCHS_H
#define PEA2_DFSSEARCHS_H
#include "../../App/DistMatrix.h"
#include "stack"
#include "iostream"
#include "climits"
#include <vector>
#include <climits>
#include <iostream>


class DFSSearchS {
private:
    const DistMatrix& distanceMatrix; // Odwołanie do macierzy odległości
    int bestCost; // Najlepszy koszt (długość trasy)
    std::vector<int> bestPath; // Najlepsza trasa
    std::vector<bool> visited; // Tablica odwiedzonych miast
    void branchAndBound(int currentCity, int depth, int currentCost, std::vector<int>& currentPath);

public:
    explicit DFSSearchS(const DistMatrix& dm);
    void solve();
    void displayResult() const;
};


#endif //PEA2_DFSSEARCHS_H
