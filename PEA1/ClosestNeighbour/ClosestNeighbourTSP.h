//
// Created by Miłosz on 13.10.2024.
//

#ifndef PEA_1_CLOSESTNEIGHBOURTSP_H
#define PEA_1_CLOSESTNEIGHBOURTSP_H
#include "../DistanceMatrix.h"

class ClosestNeighbourTSP {
    DistanceMatrix& distanceMatrix; // Reference to the distance matrix
    int* bestPath;                  // Array to store the best path found
    int cityCount;                  // Number of cities
    int bestDistance;               // Total distance for the best path

public:
    ClosestNeighbourTSP(DistanceMatrix& dm); // Constructor
    ~ClosestNeighbourTSP();                  // Destructor

    void findShortestPath();      // Method to perform nearest neighbor algorithm
    void displayBestPath() const; // Method to display the best path
};


#endif //PEA_1_CLOSESTNEIGHBOURTSP_H
