//
// Created by Miłosz on 13.10.2024.
//

#include "RandomInspectionTSP.h"
#include <iostream>
#include <algorithm>  // for std::shuffle
#include <ctime>      // for random seed
#include <cstdlib>    // for rand() and srand()
#include <limits>

using namespace std;

// Constructor: Initialize reference to DistanceMatrix
RandomInspectionTSP::RandomInspectionTSP(DistanceMatrix& dm)
        : distanceMatrix(dm), cityCount(dm.getSize()), bestDistance(numeric_limits<int>::max()) {
    bestPath = new int[cityCount + 1]; // Allocate memory for best path, +1 for return to start
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

// Destructor: Free dynamically allocated memory
RandomInspectionTSP::~RandomInspectionTSP() {
    delete[] bestPath;
}

// Method to find a random path with a set number of iterations
void RandomInspectionTSP::findRandomPath(int iterations) {
    int* currentPath = new int[cityCount + 1]; // Array for the current random path
    int currentDistance = 0;

    // Initialize the cities array
    for (int i = 0; i < cityCount; i++) {
        currentPath[i] = i;
    }

    // Perform random shuffling for a given number of iterations
    for (int iter = 0; iter < iterations; iter++) {
        // Shuffle the cities to get a random path
        random_shuffle(&currentPath[1], &currentPath[cityCount]); // Shuffle from city 1 to cityCount-1

        // Calculate the distance of this random path
        currentDistance = 0;
        bool validPath = true;
        for (int i = 0; i < cityCount - 1; i++) {
            int dist = distanceMatrix.get(currentPath[i], currentPath[i + 1]);
            if (dist == -1) {
                validPath = false;
                break;
            }
            currentDistance += dist;
        }

        // Add the distance back to the starting city
        int returnDist = distanceMatrix.get(currentPath[cityCount - 1], currentPath[0]);
        if (returnDist != -1 && validPath) {
            currentDistance += returnDist;
        } else {
            validPath = false;
        }

        // If the current random path is shorter than the best path found so far, update it
        if (validPath && currentDistance < bestDistance) {
            bestDistance = currentDistance;
            for (int i = 0; i < cityCount; i++) {
                bestPath[i] = currentPath[i];
            }
            bestPath[cityCount] = bestPath[0]; // Complete the cycle by returning to the starting city
        }
    }

    delete[] currentPath; // Clean up dynamic memory
}

// Method to display the best path found
void RandomInspectionTSP::displayBestPath() const {
    if (bestDistance == numeric_limits<int>::max()) {
        cout << "Nie znaleziono poprawnej trasy." << endl;
    } else {
        cout << "Najkrótsza ścieżka (Losowa): ";
        for (int i = 0; i <= cityCount; i++) { // cityCount + 1 because we return to the starting city
            cout << bestPath[i] << " ";
        }
        cout << endl;
        cout << "Długość ścieżki (Losowa): " << bestDistance << endl;
    }
}