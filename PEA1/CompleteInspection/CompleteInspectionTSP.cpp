//
// Created by Miłosz on 13.10.2024.
//

#include "CompleteInspectionTSP.h"
#include <iostream>
#include <limits>
using namespace std;

// Constructor: Initialize reference to DistanceMatrix and set initial best distance
CompleteInspectionTSP::CompleteInspectionTSP(DistanceMatrix& dm)
        : distanceMatrix(dm), bestDistance(numeric_limits<int>::max()), cityCount(dm.getSize()) {
    // Dynamically allocate memory for the best path
    bestPath = new int[cityCount];
}

// Destructor to free allocated memory
CompleteInspectionTSP::~CompleteInspectionTSP() {
    delete[] bestPath;  // Free the dynamically allocated bestPath
}

// Function to calculate the shortest path using brute force
int CompleteInspectionTSP::calculateShortestPath() {
    int* cities = new int[cityCount];   // Dynamically allocate an array for cities
    bool* visited = new bool[cityCount]; // Visited cities tracker

    // Initialize the cities array
    for (int i = 0; i < cityCount; i++) {
        cities[i] = i;
        visited[i] = false; // Initially, no city has been visited
    }

    // Start with the first city as the current city
    visited[0] = true;  // Mark the first city as visited

    // Recursively find the best path
    findBestPath(cities, visited, 1, 0, 1);

    // Clean up dynamic memory
    delete[] cities;
    delete[] visited;

    return bestDistance;
}

// Recursive function to find the best path
void CompleteInspectionTSP::findBestPath(int* cities, bool* visited, int currentIndex, int currentDistance, int count) {
    // If all cities have been visited, calculate the distance back to the starting city
    if (count == cityCount) {
        int lastSegmentDistance = distanceMatrix.get(cities[currentIndex - 1], cities[0]);
        if (lastSegmentDistance == -1) lastSegmentDistance = 0; // Self-loop, treat as 0

        int totalDistance = currentDistance + lastSegmentDistance;
        if (totalDistance < bestDistance) {
            bestDistance = totalDistance; // Update best distance
            for (int i = 0; i < cityCount; i++) {
                bestPath[i] = cities[i]; // Save the current best path
            }
        }
        return;
    }

    // Visit each city that hasn't been visited yet
    for (int i = 1; i < cityCount; i++) {
        if (!visited[i]) {
            int segmentDistance = distanceMatrix.get(cities[currentIndex - 1], i);
            if (segmentDistance == -1) segmentDistance = 0; // Self-loop, treat as 0

            visited[i] = true; // Mark this city as visited
            cities[currentIndex] = i; // Add the city to the current path

            // Recur with the updated path and distance
            findBestPath(cities, visited, currentIndex + 1, currentDistance + segmentDistance, count + 1);

            // Backtrack: Mark the city as unvisited for the next iteration
            visited[i] = false;
        }
    }
}

// Function to display the best path found, with the full cycle (returning to the start)
void CompleteInspectionTSP::displayBestPath() {
    if (bestDistance == numeric_limits<int>::max()) {
        cout << "Nie znaleziono poprawnej trasy." << endl;
    } else {
        cout << "Najkrotsza sciezka: ";
        for (int i = 0; i < cityCount; i++) {
            cout << bestPath[i] << " ";  // Print the cities in the path
        }
        cout << bestPath[0] << " ";  // Append the starting city at the end to form a cycle
        cout << endl;
        cout << "Dlugosc sciezki: " << bestDistance << endl;
    }
}
