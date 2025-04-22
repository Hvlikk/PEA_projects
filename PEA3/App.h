//
// Created by Miłosz on 16.12.2024.
//

#ifndef PEA3_APP_H
#define PEA3_APP_H


class App {
private:
    int** distanceMatrix;
    int cityCount;
public:
    void runApp();
    int get();
    int getSize();
    void displayMatrix();
};


#endif //PEA3_APP_H
