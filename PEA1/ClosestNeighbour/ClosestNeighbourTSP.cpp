//
// Created by Miłosz on 13.10.2024.
//

#include "ClosestNeighbourTSP.h"
#include <iostream>
#include <limits>

using namespace std;

// Constructor: Initialize reference to DistanceMatrix
ClosestNeighbourTSP::ClosestNeighbourTSP(DistanceMatrix& dm)
        : distanceMatrix(dm), cityCount(dm.getSize()), bestDistance(0) {
    bestPath = new int[cityCount + 1]; // Allocate memory for best path, +1 for return to start
}

// Destructor: Free dynamically allocated memory
ClosestNeighbourTSP::~ClosestNeighbourTSP() {
    delete[] bestPath;
}

// Method to find the shortest path using the nearest neighbor algorithm
void ClosestNeighbourTSP::findShortestPath() {
    bool* visited = new bool[cityCount]; // Array to track visited cities
    for (int i = 0; i < cityCount; i++) {
        visited[i] = false; // Initially, no city is visited
    }

    int currentCity = 0;  // Start from city 0
    visited[currentCity] = true;
    bestPath[0] = currentCity;

    bestDistance = 0; // Initialize total distance to 0

    // Loop to visit all cities
    for (int i = 1; i < cityCount; i++) {
        int nearestCity = -1;
        int shortestDistance = numeric_limits<int>::max();

        // Find the nearest unvisited city
        for (int j = 0; j < cityCount; j++) {
            if (!visited[j]) {
                int distance = distanceMatrix.get(currentCity, j);
                if (distance != -1 && distance < shortestDistance) {
                    shortestDistance = distance;
                    nearestCity = j;
                }
            }
        }

        // Move to the nearest city
        visited[nearestCity] = true;
        bestPath[i] = nearestCity;
        bestDistance += shortestDistance;
        currentCity = nearestCity;
    }

    // Return to the starting city
    int returnDistance = distanceMatrix.get(currentCity, 0);
    if (returnDistance != -1) {
        bestDistance += returnDistance;
    }
    bestPath[cityCount] = 0; // Complete the cycle by returning to the starting city

    delete[] visited; // Clean up dynamic memory
}

// Method to display the best path found
void ClosestNeighbourTSP::displayBestPath() const {
    cout << "Najkrotsza sciezka (NN): ";
    for (int i = 0; i <= cityCount; i++) { // cityCount + 1 because we return to the starting city
        cout << bestPath[i] << " ";
    }
    cout << endl;
    cout << "Dlugosc sciezki (NN): " << bestDistance << endl;
}
