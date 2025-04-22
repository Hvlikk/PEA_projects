//
// Created by Miłosz on 22.11.2024.
//

#include "DFSSearchS.h"
#include "DFSSearchS.h"
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>

using namespace std;

DFSSearchS::DFSSearchS(const DistMatrix& dm)
        : distanceMatrix(dm),
          bestCost(numeric_limits<int>::max()),
          visited(dm.getSize(), false) {}

void DFSSearchS::branchAndBound(int currentCity, int depth, int currentCost, vector<int>& currentPath) {
    int n = distanceMatrix.getSize();

    // Jeśli odwiedzono wszystkie miasta, wracamy do miasta początkowego
    if (depth == n && distanceMatrix.get(currentCity, currentPath[0]) != -1) {
        currentCost += distanceMatrix.get(currentCity, currentPath[0]);
        if (currentCost < bestCost) {
            bestCost = currentCost;
            bestPath = currentPath;
            bestPath.push_back(currentPath[0]); // Dodaj miasto startowe na koniec
        }
        return;
    }

    // Oblicz dolne ograniczenie dla bieżącego stanu
    int lowerBound = currentCost;
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            int minCost = numeric_limits<int>::max();
            for (int j = 0; j < n; ++j) {
                if (i != j && distanceMatrix.get(i, j) != -1) {
                    minCost = min(minCost, distanceMatrix.get(i, j));
                }
            }
            lowerBound += minCost;
        }
    }

    // Przycinamy, jeśli dolne ograniczenie jest większe od najlepszego znalezionego kosztu
    if (lowerBound >= bestCost) {
        return;
    }

    // Generujemy listę miast do odwiedzenia, sortując je według kosztów
    vector<pair<int, int>> candidates; // <koszt, miasto>
    for (int nextCity = 0; nextCity < n; ++nextCity) {
        if (!visited[nextCity] && distanceMatrix.get(currentCity, nextCity) != -1) {
            candidates.emplace_back(distanceMatrix.get(currentCity, nextCity), nextCity);
        }
    }
    sort(candidates.begin(), candidates.end());

    // Przechodzimy do każdego nieodwiedzonego miasta w kolejności rosnących kosztów
    for (const auto& [cost, nextCity] : candidates) {
        visited[nextCity] = true;
        currentPath.push_back(nextCity);

        branchAndBound(nextCity, depth + 1, currentCost + cost, currentPath);

        // Cofamy się (Backtracking)
        visited[nextCity] = false;
        currentPath.pop_back();
    }
}

void DFSSearchS::solve() {
    int n = distanceMatrix.getSize();
    vector<int> currentPath;
    currentPath.reserve(n);

    currentPath.push_back(0); // Startujemy z miasta 0
    visited[0] = true;

    branchAndBound(0, 1, 0, currentPath);
}

void DFSSearchS::displayResult() const {
    if (bestPath.empty()) {
        cout << "Nie znaleziono rozwiązania." << endl;
    } else {
        cout << "Najlepsza trasa (DFS - SYM): ";
        for (int city : bestPath) {
            cout << city << " ";
        }
        cout << endl;
        cout << "Koszt trasy: " << bestCost << endl;
    }
}