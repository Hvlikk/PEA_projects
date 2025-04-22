#include "DFSSearchAS.h"
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <cstring> // For memcpy

using namespace std;

DFSSearchAS::DFSSearchAS(const DistMatrix& dm)
        : distanceMatrix(dm),
          bestCost(numeric_limits<int>::max()),
          visited(dm.getSize(), false) {}

// Funkcja redukcji macierzy (zwraca koszt redukcji)
int DFSSearchAS::reduceMatrix(int** matrix, int size) {
    int reductionCost = 0;

    // Redukcja wierszy
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

    // Redukcja kolumn
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

void DFSSearchAS::branchAndBound(int** matrix, int currentCity, int depth, int currentCost, vector<int>& currentPath) {
    int n = distanceMatrix.getSize();

    // Jeśli odwiedzono wszystkie miasta, wracamy do miasta początkowego
    if (depth == n && distanceMatrix.get(currentCity, currentPath[0]) != -1) {
        //currentCost += distanceMatrix.get(currentCity, currentPath[0]);
        if (currentCost < bestCost) {
            bestCost = currentCost;
            bestPath = currentPath;
            bestPath.push_back(currentPath[0]); // Dodaj miasto startowe na koniec
        }
        return;
    }


    // Przechodzimy do każdego nieodwiedzonego miasta
    for (int nextCity = 0; nextCity < n; ++nextCity) {
        if (!visited[nextCity] && matrix[currentCity][nextCity] != -1) {
            // Stwórz kopię macierzy dla nowej gałęzi
            int** newMatrix = new int*[n];
            for (int i = 0; i < n; i++) {
                newMatrix[i] = new int[n];
                memcpy(newMatrix[i], matrix[i], n * sizeof(int));
            }

            // Zablokuj powrót do poprzednich miast w nowej macierzy
            for (int i = 0; i < n; i++) {
                newMatrix[currentCity][i] = -1; // Zerowanie wiersza
                newMatrix[i][nextCity] = -1; // Zerowanie kolumny
            }
            newMatrix[nextCity][currentPath[0]] = -1; // Zerowanie powrotu do startu

            // Zredukuj nową macierz
            int reductionCost = reduceMatrix(newMatrix, n);

            // Oblicz nowy koszt
            int newCost = currentCost + matrix[currentCity][nextCity] + reductionCost;


            if (newCost < bestCost) {
                // Zapisz wizytę
                visited[nextCity] = true;
                currentPath.push_back(nextCity);

                // Wywołaj rekurencyjnie
                branchAndBound(newMatrix, nextCity, depth + 1, newCost, currentPath);

                // Cofnij wizytę
                visited[nextCity] = false;
                currentPath.pop_back();
            }

            // Zwolnij pamięć macierzy
            for (int i = 0; i < n; i++) {
                delete[] newMatrix[i];
            }
            delete[] newMatrix;
        }
    }
}

void DFSSearchAS::solve() {
    int n = distanceMatrix.getSize();

    // Inicjalizuj macierz i wykonaj początkową redukcję
    int** matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
        for (int j = 0; j < n; j++) {
            matrix[i][j] = distanceMatrix.get(i, j);
        }
    }
    int initialReductionCost = reduceMatrix(matrix, n);

    vector<int> currentPath;
    currentPath.push_back(0); // Startujemy z miasta     0
    visited[0] = true;

    branchAndBound(matrix, 0, 1, initialReductionCost, currentPath);

    // Zwolnij pamięć macierzy
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void DFSSearchAS::displayResult() const {
    if (bestPath.empty()) {
        cout << "Nie znaleziono rozwiązania." << endl;
    } else {
        cout     << "Najlepsza trasa (DFS): ";
        for (int city : bestPath) {
            cout << city << " ";
        }
        cout << endl;
        cout << "Koszt trasy: " << bestCost << endl;
    }
}
