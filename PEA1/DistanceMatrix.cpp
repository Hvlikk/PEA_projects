//
// Created by Miłosz on 13.10.2024.
//
#include "DistanceMatrix.h"
#include <iostream>
#include <fstream>
using namespace std;

// Konstruktor
DistanceMatrix::DistanceMatrix(const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Nie można otworzyć pliku!" << endl;
        exit(1);
    }

    // Wczytujemy liczbę miast
    file >> cityCount;

    // Dynamiczna alokacja macierzy
    distanceMatrix = new int*[cityCount];
    for (int i = 0; i < cityCount; i++) {
        distanceMatrix[i] = new int[cityCount];
    }

    // Wczytujemy macierz z pliku
    for (int i = 0; i < cityCount; i++) {
        for (int j = 0; j < cityCount; j++) {
            file >> distanceMatrix[i][j];
        }
    }

    // Zamykamy plik
    file.close();
}

DistanceMatrix::DistanceMatrix(int cities) : cityCount(cities) {
    // Inicjalizacja generatora liczb losowych
    srand(static_cast<unsigned int>(time(0)));

    // Dynamiczna alokacja macierzy
    distanceMatrix = new int*[cityCount];
    for (int i = 0; i < cityCount; i++) {
        distanceMatrix[i] = new int[cityCount];
    }

    // Wypełniamy macierz losowymi wartościami (z wyjątkiem przekątnej)
    for (int i = 0; i < cityCount; i++) {
        for (int j = 0; j < cityCount; j++) {
            if (i == j) {
                distanceMatrix[i][j] = -1;  // Brak drogi do tego samego miasta
            } else {
                distanceMatrix[i][j] = rand() % 100 + 1;  // Losowa odległość od 1 do 100
            }
        }
    }
}

DistanceMatrix::DistanceMatrix(int** matrix, int size) : cityCount(size) {
    // Dynamic allocation of matrix
    distanceMatrix = new int*[cityCount];
    for (int i = 0; i < cityCount; i++) {
        distanceMatrix[i] = new int[cityCount];
        for (int j = 0; j < cityCount; j++) {
            distanceMatrix[i][j] = matrix[i][j];
        }
    }
}

// Destruktor
DistanceMatrix::~DistanceMatrix() {
    for (int i = 0; i < cityCount; i++) {
        delete[] distanceMatrix[i];
    }
    delete[] distanceMatrix;
}

// Metoda wyświetlająca macierz
void DistanceMatrix::displayMatrix()  {
    cout << "Wczytana macierz odleglosci: " << endl;
    for (int i = 0; i < cityCount; i++) {
        for (int j = 0; j < cityCount; j++) {
            cout << distanceMatrix[i][j] << " ";
        }
        cout << endl;
    }
}
