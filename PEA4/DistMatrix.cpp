//
// Created by Miłosz on 16.01.2025.
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
            size_t pos = line.find(":");                            // Wczytanie liczby miast
            cityCount = stoi(line.substr(pos + 1));
        } else if (line.find("EDGE_WEIGHT_SECTION") != string::npos) {
            readingMatrix = true;
            break;
        }
    }

    if (!readingMatrix) {                                       // Nie znaleziono sekcji z wagami
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

// Zwraca wskaźnik do macierzy odległości
int** DistMatrix::getDistanceMatrix() const {
    return distanceMatrix;
}

// Zwraca liczbę miast
int DistMatrix::getCityCount() const {
    return cityCount;
}
