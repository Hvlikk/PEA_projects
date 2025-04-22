//
// Created by Miłosz on 16.12.2024.
//

#include "App.h"
#include "DistMatrix.h"
#include "fstream"
#include "iostream"
using namespace std;
void App::runApp() {

    //Nazwa pliku z danymi, stworzenie macierzy odległości, która jest przechowywana w klasie DistanceMatrix
    const char* filename = "dane.atsp";
    DistMatrix dm(filename);

    //Wyświetlamy macierz
    dm.displayMatrix();
}
