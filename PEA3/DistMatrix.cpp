//
// Created by Miłosz on 16.12.2024.
//

#include "DistMatrix.h"
#include "DistMatrix.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// Konstruktor
DistMatrix::DistMatrix(const char* filename) {
    // Otwarcie pliku
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Nie można otworzyć pliku!" << endl;
        exit(1);
    }

    string line;
    bool readingMatrix = false;

    // Przechodzenie przez nagłówki pliku ATSP
    while (getline(file, line)) {
        if (line.find("DIMENSION") != string::npos) {
            // Wczytanie liczby miast
            size_t pos = line.find(":");
            cityCount = stoi(line.substr(pos + 1));
        } else if (line.find("EDGE_WEIGHT_SECTION") != string::npos) {
            readingMatrix = true;
            break;
        }
    }

    if (!readingMatrix) {
        cerr << "Nie znaleziono sekcji EDGE_WEIGHT_SECTION!" << endl;
        exit(1);
    }

    // Dynamiczna alokacja macierzy
    distanceMatrix = new int*[cityCount];
    for (int i = 0; i < cityCount; i++) {
        distanceMatrix[i] = new int[cityCount];
    }

    // Wczytywanie macierzy odległości
    for (int i = 0; i < cityCount; i++) {
        for (int j = 0; j < cityCount; j++) {
            file >> distanceMatrix[i][j];
        }
    }

    // Zamknięcie pliku
    file.close();
}

// Konstruktor stworzony dla przeprowadzania testów - generowanie macierzy
DistMatrix::DistMatrix(int cities, int symetric) : cityCount(cities) {
    srand(static_cast<unsigned int>(time(0)));

    distanceMatrix = new int*[cityCount];
    for (int i = 0; i < cityCount; i++) {
        distanceMatrix[i] = new int[cityCount];
    }

    if (symetric == 1) {
        for (int i = 0; i < cityCount; i++) {
            for (int j = 0; j < cityCount; j++) {
                if (i == j) {
                    distanceMatrix[i][j] = -1;
                } else if (i < j) {
                    distanceMatrix[i][j] = rand() % 100 + 1;
                    distanceMatrix[j][i] = distanceMatrix[i][j];
                }
            }
        }
    } else {
        for (int i = 0; i < cityCount; i++) {
            for (int j = 0; j < cityCount; j++) {
                if (i == j) {
                    distanceMatrix[i][j] = -1;
                } else {
                    distanceMatrix[i][j] = rand() % 100 + 1;
                }
            }
        }
    }
}

DistMatrix::DistMatrix(int** matrix, int size) : cityCount(size) {
    distanceMatrix = new int*[cityCount];
    for (int i = 0; i < cityCount; i++) {
        distanceMatrix[i] = new int[cityCount];
        for (int j = 0; j < cityCount; j++) {
            distanceMatrix[i][j] = matrix[i][j];
        }
    }
}

// Destruktor
DistMatrix::~DistMatrix() {
    for (int i = 0; i < cityCount; i++) {
        delete[] distanceMatrix[i];
    }
    delete[] distanceMatrix;
}

// Metoda wyświetlająca macierz
void DistMatrix::displayMatrix() {
    cout << "Wczytana macierz odleglosci: " << endl;
    for (int i = 0; i < cityCount; i++) {
        for (int j = 0; j < cityCount; j++) {
            cout << distanceMatrix[i][j] << " ";
        }
        cout << endl;
    }
}
