//
// Created by Miłosz on 13.10.2024.
//

#ifndef PEA_1_DISTANCEMATRIX_H
#define PEA_1_DISTANCEMATRIX_H


class DistanceMatrix {
private:
    int** distanceMatrix;
    int cityCount;
public:
    DistanceMatrix(const char* filename);
    DistanceMatrix(int** matrix, int size);
    DistanceMatrix(int cities);
    ~DistanceMatrix();
    void displayMatrix();
    int getSize() const {return cityCount;};
    int get(int i, int j) const {return distanceMatrix[i][j];};
};


#endif //PEA_1_DISTANCEMATRIX_H
