//
// Created by Miłosz on 13.10.2024.
//

#ifndef PEA_1_RANDOMINSPECTIONTSP_H
#define PEA_1_RANDOMINSPECTIONTSP_H
#include "../DistanceMatrix.h"

class RandomInspectionTSP {
private:
    DistanceMatrix& distanceMatrix; // Reference to the distance matrix
    int* bestPath;                  // Array to store the best path found
    int cityCount;                  // Number of cities
    int bestDistance;               // Total distance for the best path

public:
    RandomInspectionTSP(DistanceMatrix& dm);  // Constructor
    ~RandomInspectionTSP();                   // Destructor

    void findRandomPath(int iterations); // Method to perform randomized search
    void displayBestPath() const;    // Method to display the best path
};


#endif //PEA_1_RANDOMINSPECTIONTSP_H
