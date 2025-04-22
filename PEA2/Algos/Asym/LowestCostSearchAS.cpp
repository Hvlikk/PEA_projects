#include "LowestCostSearchAS.h"
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

LowestCostSearchAS::LowestCostSearchAS(DistMatrix& dm)
        : distMatrix(dm), bestCost(INT_MAX) {}

int LowestCostSearchAS::calculateLowerBound(int currentCost, const vector<int>& visited) {
    int bound = currentCost;

    // Suma minimalnych kosztów wychodzących dla nieodwiedzonych węzłów
    for (int i = 0; i < distMatrix.getSize(); i++) {
        if (find(visited.begin(), visited.end(), i) == visited.end()) {
            int minCost = INT_MAX;
            for (int j = 0; j < distMatrix.getSize(); j++) {
                if (i != j && distMatrix.get(i, j) != -1) {
                    minCost = min(minCost, distMatrix.get(i, j));
                }
            }
            bound += minCost;
        }
    }

    return bound;
}

void LowestCostSearchAS::solve() {
    // Kolejka priorytetowa węzłów
    priority_queue<Node, vector<Node>, greater<>> pq;

    // Inicjalizacja węzła startowego
    vector<int> startPath = {0};
    int startLowerBound = calculateLowerBound(0, startPath);
    pq.emplace(startPath, 0, startLowerBound);

    // Przeglądanie węzłów
    while (!pq.empty()) {
        Node currentNode = pq.top();
        pq.pop();

        // Jeśli ścieżka jest kompletna (wszystkie miasta odwiedzone)
        if (currentNode.path.size() == distMatrix.getSize()) {
            int finalCost = currentNode.currentCost + distMatrix.get(currentNode.path.back(), 0); // Koszt powrotu
            if (finalCost < bestCost) {
                bestCost = finalCost;
                bestPath = currentNode.path;
                bestPath.push_back(0); // Powrót do miasta startowego
            }
            continue;
        }

        // Rozwój węzłów potomnych
        for (int i = 0; i < distMatrix.getSize(); i++) {
            // Jeśli miasto nie zostało odwiedzone
            if (find(currentNode.path.begin(), currentNode.path.end(), i) == currentNode.path.end()) {
                vector<int> newPath = currentNode.path;
                newPath.push_back(i);
                int newCost = currentNode.currentCost + distMatrix.get(currentNode.path.back(), i);
                int newLowerBound = calculateLowerBound(newCost, newPath);

                // Jeśli dolne ograniczenie jest mniejsze niż najlepszy koszt, dodajemy do kolejki
                if (newLowerBound < bestCost) {
                    pq.emplace(newPath, newCost, newLowerBound);
                }
            }
        }
    }
}

void LowestCostSearchAS::displayResult() {
    cout << "Najlepsza trasa (LCFS): ";
    for (int city : bestPath) {
        cout << city << " ";
    }
    cout << endl;
    cout << "Koszt: " << bestCost << endl;
}
