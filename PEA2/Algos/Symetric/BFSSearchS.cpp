//
// Created by Miłosz on 03.11.2024.
//
#include <limits>
#include "climits"
#include "BFSSearchS.h"
#include "cstdlib"
#include "queue"
#include "climits"
#include "algorithm"
#include "iostream"
using namespace std;


// Konstruktor
BFSSearchS::BFSSearchS(const DistMatrix& dm)
        : distanceMatrix(dm), bestCost(numeric_limits<int>::max()) {}

// Funkcja obliczająca dolne ograniczenie dla aktualnej trasy
int BFSSearchS::calculateLowerBound(int currentCost, const vector<bool>& visited) const {
    int n = distanceMatrix.getSize();
    int lowerBound = currentCost;

    // Dodaj minimalne koszty wyjścia dla każdego nieodwiedzonego miasta
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            int minCost = numeric_limits<int>::max();
            for (int j = 0; j <= i; ++j) { // Sprawdzamy tylko połowę macierzy
                if (!visited[j] && distanceMatrix.get(i, j) != -1) {
                    minCost = min(minCost, distanceMatrix.get(i, j));
                }
            }
            if (minCost < numeric_limits<int>::max()) {
                lowerBound += minCost;
            }
        }
    }

    return lowerBound;
}

// Funkcja rozwiązująca BFS
void BFSSearchS::solve() {
    int n = distanceMatrix.getSize();
    queue<pair<int, vector<int>>> bfsQueue; // Kolejka: <koszt, ścieżka>
    queue<vector<bool>> visitedQueue;      // Kolejka odwiedzonych miast

    // Inicjalizacja algorytmu od miasta startowego (miasto 0)
    bfsQueue.push({0, {0}});
    visitedQueue.push(vector<bool>(n, false));
    visitedQueue.front()[0] = true;

    while (!bfsQueue.empty()) {
        // Pobranie aktualnej trasy z kolejki BFS
        auto [currentCost, currentPath] = bfsQueue.front();
        vector<bool> currentVisited = visitedQueue.front();
        bfsQueue.pop();
        visitedQueue.pop();

        int currentCity = currentPath.back(); // Ostatnie miasto w trasie

        // Jeśli odwiedziliśmy wszystkie miasta, dodajemy koszt powrotu do startu
        if (currentPath.size() == n) {
            int finalCost = currentCost + distanceMatrix.get(currentCity, 0);
            if (finalCost < bestCost) {
                bestCost = finalCost;
                bestPath = currentPath;
                bestPath.push_back(0); // Powrót do miasta startowego
            }
            continue;
        }

        // Rozwijamy tylko unikalne kombinacje w symetrycznej macierzy
        for (int nextCity = 0; nextCity < n; ++nextCity) {
            if (!currentVisited[nextCity] && distanceMatrix.get(currentCity, nextCity) != -1) {
                int newCost = currentCost + distanceMatrix.get(currentCity, nextCity);

                // Oblicz dolne ograniczenie
                vector<bool> newVisited = currentVisited;
                newVisited[nextCity] = true;

                int lowerBound = calculateLowerBound(newCost, newVisited);

                // Rozwijamy węzeł tylko jeśli dolne ograniczenie jest lepsze
                if (lowerBound < bestCost) {
                    vector<int> newPath = currentPath;
                    newPath.push_back(nextCity);
                    bfsQueue.push({newCost, newPath});
                    visitedQueue.push(newVisited);
                }
            }
        }
    }
}

// Wyświetlenie wyników
void BFSSearchS::displayResult() const {
    if (bestPath.empty()) {
        cout << "Nie znaleziono rozwiązania." << endl;
    } else {
        cout << "Najlepsza trasa (BFS - SYM): ";
        for (int city : bestPath) {
            cout << city << " ";
        }
        cout << endl;
        cout << "Koszt trasy: " << bestCost << endl;
    }
}