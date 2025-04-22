//
// Created by Miłosz on 13.10.2024.
//
#include "DistMatrix.h"
#include <iostream>
#include <fstream>
using namespace std;

// Konstruktor
DistMatrix::DistMatrix(const char* filename) {
    //Otwarcie strumienia wczytywania danych
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Nie można otworzyć pliku!" << endl;
        exit(1);
    }

    // Wczytujemy liczbę miast
    file >> cityCount;
    //Inicjalizacja zmiennych
    int symetric = 0, generator = 0;
    //Wczytanie czy macierz ma byc symetryczna
    file >> symetric;
    //Wczytanie czy ma byc wygenerowana
    file >> generator;



    // Dynamiczna alokacja macierzy
    distanceMatrix = new int*[cityCount];
    for (int i = 0; i < cityCount; i++) {
        distanceMatrix[i] = new int[cityCount];
    }

    if (generator == 0) {
        // Wczytujemy macierz z pliku
        for (int i = 0; i < cityCount; i++) {
            for (int j = 0; j < cityCount; j++) {
                file >> distanceMatrix[i][j];
            }
        }
    } else {
        srand(static_cast<unsigned int>(time(0)));
        if (symetric == 1) {
            // Wypełnianie macierzy
            for (int i = 0; i < cityCount; i++) {
                for (int j = 0; j < cityCount; j++) {
                    if (i == j) {
                        distanceMatrix[i][j] = -1;  // Brak drogi do samego siebie
                    } else if (i < j) {
                        // Wartości są generowane tylko dla górnej części macierzy
                        distanceMatrix[i][j] = rand() % 100 + 1;  // Losowa odległość od 1 do 100
                        distanceMatrix[j][i] = distanceMatrix[i][j];  // Odbicie wartości dla symetrii
                    }
                }
            }

        }
        else {
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
    }
    // Zamykamy plik
    file.close();
}

//Konstruktor stworzony dla przeprowadzania testów - generowanie macierzy
DistMatrix::DistMatrix(int cities, int symetric) : cityCount(cities) {
    // Inicjalizacja generatora liczb losowych
    srand(static_cast<unsigned int>(time(0)));

    // Dynamiczna alokacja macierzy
    distanceMatrix = new int*[cityCount];
    for (int i = 0; i < cityCount; i++) {
        distanceMatrix[i] = new int[cityCount];
    }

    if (symetric == 1) {
        // Wypełnianie macierzy
        for (int i = 0; i < cityCount; i++) {
            for (int j = 0; j < cityCount; j++) {
                if (i == j) {
                    distanceMatrix[i][j] = -1;  // Brak drogi do samego siebie
                } else if (i < j) {
                    // Wartości są generowane tylko dla górnej części macierzy
                    distanceMatrix[i][j] = rand() % 100 + 1;  // Losowa odległość od 1 do 100
                    distanceMatrix[j][i] = distanceMatrix[i][j];  // Odbicie wartości dla symetrii
                }
            }
        }

    }
    else {
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
}

DistMatrix::DistMatrix(int** matrix, int size) : cityCount(size) {
    // Dynamiczna alokacja macierzy
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