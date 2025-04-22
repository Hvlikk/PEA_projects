//
// Created by Miłosz on 03.11.2024.
//

#ifndef PEA2_APPLICATION_H
#define PEA2_APPLICATION_H


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


#endif //PEA2_APPLICATION_H
