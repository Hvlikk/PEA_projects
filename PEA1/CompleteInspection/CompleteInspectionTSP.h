//
// Created by Miłosz on 13.10.2024.
//

#ifndef PEA_1_COMPLETEINSPECTIONTSP_H
#define PEA_1_COMPLETEINSPECTIONTSP_H
#include "../DistanceMatrix.h"

class CompleteInspectionTSP {
private:
    DistanceMatrix& distanceMatrix; // Reference to the distance matrix
    int* bestPath;                  // Best path found so far (dynamically allocated)
    int bestDistance;               // Distance of the best path
    int cityCount;                  // Number of cities

    void findBestPath(int* cities, bool* visited, int currentIndex, int currentDistance, int count);

public:
    CompleteInspectionTSP(DistanceMatrix& dm);
    ~CompleteInspectionTSP();               // Destructor to free allocated memory
    int calculateShortestPath();    // Calculate the shortest path
    void displayBestPath();         // Display the best path found
    int calculatePathDistance(const int* path); // Calculate the distance of a given path

};


#endif //PEA_1_COMPLETEINSPECTIONTSP_H
