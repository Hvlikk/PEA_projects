//
// Created by Miłosz on 13.10.2024.
//

#include "iostream"
#include "fstream"
#include "Application.h"
#include "DistanceMatrix.h"
#include "CompleteInspection/CompleteInspectionTSP.h"
#include "ClosestNeighbour/ClosestNeighbourTSP.h"
#include "RandomInspection/RandomInspectionTSP.h"
#include "chrono"
#include "fstream"
#include "unistd.h"
using namespace std;


void Application::runApp() {

    //const char* filename = "dane.txt";
    //DistanceMatrix dm(filename);

    // Obiekt do pliku wynikowego
    ofstream outputFile1("bruteForce_4.txt", ios::app);  // Otwieramy w trybie dopisywania
    if (!outputFile1.is_open()) {
        cerr << "Nie można otworzyć pliku do zapisu!" << endl;
        exit(50);
    }

    // Obiekt do pliku wynikowego
    ofstream outputFile2("closestNeigh_4.txt", ios::app);  // Otwieramy w trybie dopisywania
    if (!outputFile2.is_open()) {
        cerr << "Nie można otworzyć pliku do zapisu!" << endl;
        exit(51);
    }

    // Obiekt do pliku wynikowego
    ofstream outputFile3("random_4.txt", ios::app);  // Otwieramy w trybie dopisywania
    if (!outputFile3.is_open()) {
        cerr << "Nie można otworzyć pliku do zapisu!" << endl;
        exit(52);
    }

    //Nazwa pliku z danymi, stworzenie macierzy odległości, która jest przechowywana w klasie DistanceMatrix
    //const char* filename = "dane.txt";
    //DistanceMatrix dm(filename);

    // Wyświetlamy macierz
    //dm.displayMatrix();

    for (int i = 0; i < 100; i++) {

        cout << "**********************";
        cout << "I = " << i << endl;
        cout << "**********************";

        int citiesCount = 13;
        DistanceMatrix dm(citiesCount);
        dm.displayMatrix();

        // Create the BruteForceTSP object
        CompleteInspectionTSP bruteForce(dm);
        auto startBF = chrono::high_resolution_clock::now();
        // Calculate the shortest path using brute force
        int shortestDistance = bruteForce.calculateShortestPath();
        auto endBF = chrono::high_resolution_clock::now();
        auto durationBF = chrono::duration_cast<chrono::milliseconds>(endBF - startBF);
        outputFile1 << durationBF.count() << "\n";
        // Display the shortest path and its distance
        bruteForce.displayBestPath();


        ClosestNeighbourTSP closestNTSP(dm); // Create an instance of the NearestNeighborTSP
        auto startNN = chrono::high_resolution_clock::now();
        closestNTSP.findShortestPath();     // Find the shortest path using nearest neighbor heuristic
        auto endNN = chrono::high_resolution_clock::now();
        auto durationNN = chrono::duration_cast<chrono::milliseconds>(endNN - startNN);
        outputFile2 << durationNN.count() << "\n";
        closestNTSP.displayBestPath();      // Display the path and its total distance


        RandomInspectionTSP randomTSP(dm); // Create an instance of the RandomTSP

        auto startR = chrono::high_resolution_clock::now();
        randomTSP.findRandomPath(1000); // Find a random path with 1000 iterations
        auto endR = chrono::high_resolution_clock::now();
        auto durationR = chrono::duration_cast<chrono::milliseconds>(endR - startR);
        outputFile3 << durationR.count() << "\n";
        randomTSP.displayBestPath();    // Display the best path found
    }

    }


