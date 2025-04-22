//
// Created by Miłosz on 13.10.2024.
//

#ifndef PEA_1_APPLICATION_H
#define PEA_1_APPLICATION_H


class Application {
private:
    int** distanceMatrix;
    int cityCount;
public:
    void runApp();
    int get();
    int getSize();
    void displayMatrix();
};


#endif //PEA_1_APPLICATION_H
