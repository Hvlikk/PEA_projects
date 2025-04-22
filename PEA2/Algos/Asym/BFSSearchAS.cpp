#include <limits>
#include "climits"
#include "BFSSearchAS.h"
#include "cstdlib"
#include "queue"
#include "climits"
#include "algorithm"
#include "iostream"
using namespace std;

// Konstruktor
BFSSearchAS::BFSSearchAS(const DistMatrix& dm)
        : distanceMatrix(dm), bestCost(numeric_limits<int>::max()) {}

//Funkcja redukująca macierz - optymalizacja
int BFSSearchAS::reduceMatrix(int** matrix, int size) const {
    int reductionCost = 0;

    // Redukcja po wierszach
    for (int i = 0; i < size; i++) {
        int rowMin = INT_MAX;
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] >= 0) {
                rowMin = min(rowMin, matrix[i][j]);
            }
        }
        if (rowMin != INT_MAX && rowMin > 0) {
            reductionCost += rowMin;
            for (int j = 0; j < size; j++) {
                if (matrix[i][j] >= 0) {
                    matrix[i][j] -= rowMin;
                }
            }
        }
    }

    // Redukcja po kolumnach
    for (int j = 0; j < size; j++) {
        int colMin = INT_MAX;
        for (int i = 0; i < size; i++) {
            if (matrix[i][j] >= 0) {
                colMin = min(colMin, matrix[i][j]);
            }
        }
        if (colMin != INT_MAX && colMin > 0) {
            reductionCost += colMin;
            for (int i = 0; i < size; i++) {
                if (matrix[i][j] >= 0) {
                    matrix[i][j] -= colMin;
                }
            }
        }
    }

    return reductionCost;
}


// Funkcja obliczająca dolne ograniczenie dla aktualnej trasy
int BFSSearchAS::calculateLowerBound(int currentCost, const vector<bool>& visited) const {
    int n = distanceMatrix.getSize();

    // Tworzymy dynamiczną kopię macierzy kosztów
    int** reducedMatrix = new int*[n];
    for (int i = 0; i < n; ++i) {
        reducedMatrix[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            if (!visited[i] && !visited[j]) {
                reducedMatrix[i][j] = distanceMatrix.get(i, j);
            } else {
                reducedMatrix[i][j] = -1; // Oznaczamy niedostępne krawędzie
            }
        }
    }

    // Redukcja macierzy i obliczenie dolnego ograniczenia
    int reductionCost = reduceMatrix(reducedMatrix, n);

    // Usuwanie dynamicznej macierzy
    for (int i = 0; i < n; ++i) {
        delete[] reducedMatrix[i];
    }
    delete[] reducedMatrix;

    return currentCost + reductionCost;
}

// Funkcja rozwiązująca problem przy użyciu BFS + Branch and Bound
void BFSSearchAS::solve() {
    int n = distanceMatrix.getSize();
    queue<pair<int, vector<int>>> bfsQueue; // Kolejka BFS: <koszt, ścieżka>
    queue<vector<bool>> visitedQueue;       // Kolejka odwiedzonych miast

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

        int currentCity = currentPath.back(); // Ostatnie miasto w bieżącej trasie

        // Jeśli odwiedziliśmy wszystkie miasta, dodajemy koszt powrotu do miasta startowego
        if (currentPath.size() == n) {
            int finalCost = currentCost + distanceMatrix.get(currentCity, 0);
            if (finalCost < bestCost) {
                bestCost = finalCost;
                bestPath = currentPath;
                bestPath.push_back(0); // Dodajemy powrót do startu
            }
            continue;
        }

        // Przechodzimy do nieodwiedzonych miast
        for (int nextCity = 0; nextCity < n; ++nextCity) {
            if (!currentVisited[nextCity] && distanceMatrix.get(currentCity, nextCity) != -1) {
                int newCost = currentCost + distanceMatrix.get(currentCity, nextCity);

                // Oblicz dolne ograniczenie
                vector<bool> newVisited = currentVisited;
                newVisited[nextCity] = true;

                int lowerBound = calculateLowerBound(newCost, newVisited);

                // Dodajemy do kolejki tylko węzły spełniające ograniczenie
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
void BFSSearchAS::displayResult() const {
    if (bestPath.empty()) {
        cout << "Nie znaleziono rozwiązania." << endl;
    } else {
        cout << "Najlepsza trasa (BFS): ";
        for (int city : bestPath) {
            cout << city << " ";
        }
        cout << endl;
        cout << "Koszt trasy: " << bestCost << endl;
    }
}
