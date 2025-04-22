//
// Created by Miłosz on 11.01.2025.
//

#ifndef PEA4_CONFIG_H
#define PEA4_CONFIG_H

#include <string>
using namespace std;


class Config {
public:
    string filePath;
    int timeLimit;
    int populationSize;
    double crossoverProbability;
    double mutationProbability;
    string crossoverType;
    string mutationType;
    string saveFile;

    bool loadConfig(const char* configFile);
};

#endif // PEA4_CONFIG_H
