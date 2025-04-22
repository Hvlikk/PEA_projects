#ifndef DISTMATRIX_H
#define DISTMATRIX_H

#include <string>

class DistMatrix {
private:
    int** distanceMatrix; // Wskaźnik na dynamicznie alokowaną macierz odległości
    int cityCount;        // Liczba miast

public:
    // Konstruktor wczytujący dane z pliku .ATSP
    DistMatrix(const char* filename);

    // Konstruktor generujący macierz na podstawie liczby miast i trybu symetrii
    DistMatrix(int cities, int symetric);

    // Konstruktor przyjmujący istniejącą macierz i jej rozmiar
    DistMatrix(int** matrix, int size);

    // Destruktor zwalniający pamięć
    ~DistMatrix();

    // Metoda wyświetlająca macierz
    void displayMatrix();
};

#endif // DISTMATRIX_H