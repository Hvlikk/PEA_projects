//
// Created by Miłosz on 03.11.2024.
//

#ifndef PEA2_DISTMATRIX_H
#define PEA2_DISTMATRIX_H


class DistMatrix {
private:
    int** distanceMatrix;
    int cityCount;
    int iterations;
public:
    DistMatrix(const char* filename);
    DistMatrix(int** matrix, int size);
    DistMatrix(int cities, int symetric);
    ~DistMatrix();
    void displayMatrix();
    int getSize() const {return cityCount;};
    int get(int i, int j) const {return distanceMatrix[i][j];};
    int getIterations() const {return iterations;};
    int** getMatrix() const {
        return distanceMatrix;
    }
};


#endif //PEA2_DISTMATRIX_H
