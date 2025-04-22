#ifndef DISTMATRIX_H
#define DISTMATRIX_H

#include <string>

class DistMatrix {
private:
    int** distanceMatrix;
    int cityCount;

public:
    DistMatrix(const char* filename); // Konstruktor wczytujący dane z pliku
    ~DistMatrix();


    void displayMatrix();           // wyświetlanie macierzy
    int** getDistanceMatrix() const; // getter
    int getCityCount() const;       // getter

};

#endif // DISTMATRIX_H