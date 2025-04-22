//
// Created by Miłosz on 16.01.2025.
//

#include "Config.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

bool Config::loadConfig(const char* configFile) {
    ifstream file(configFile);
    if (!file.is_open()) {
        cerr << "Nie można otworzyć pliku konfiguracyjnego!" << endl;
        return false;
    }

    unordered_map<string, string> configMap;
    string line;
    while (getline(file, line)) {
        // Pomijamy ewentualne linie puste lub zaczynające się od '#'
        if (line.empty() || line[0] == '#') {
            continue;
        }

        size_t delimiterPos = line.find('=');
        if (delimiterPos != string::npos) {
            string key = line.substr(0, delimiterPos);
            string value = line.substr(delimiterPos + 1);
            configMap[key] = value;
        }
    }
    file.close();

    // Przypisanie wartości dla algorytmu genetycznego
    try {
        filePath = configMap.at("file_path");
        timeLimit = stoi(configMap.at("time_limit"));
        populationSize = stoi(configMap.at("population_size"));
        crossoverProbability = stod(configMap.at("crossover_probability"));
        mutationProbability = stod(configMap.at("mutation_probability"));
        crossoverType = configMap.at("crossover_type");
        mutationType = configMap.at("mutation_type");
        saveFile = configMap.at("fileToSave");
    } catch (const out_of_range& e) {
        cerr << "Błąd w pliku konfiguracyjnym: brak wymaganych parametrów GA!" << endl;
        return false;
    } catch (const invalid_argument& e) {
        cerr << "Błąd w pliku konfiguracyjnym: niepoprawny format wartości GA!" << endl;
        return false;
    }

    return true;
}
