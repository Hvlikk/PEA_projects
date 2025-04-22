//
// GeneticAlgo.cpp
//

#include "GeneticAlgo.h"
#include <algorithm>
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>

using namespace std;

// Konstruktor - inicjalizuje parametry z konfiguracji oraz engine losowy
GeneticAlgo::GeneticAlgo(const DistMatrix& matrix, const Config& config)
        : distMatrix(matrix), config(config)
{
    cityCount = matrix.getCityCount();
    timeLimit = config.timeLimit;
    populationSize = config.populationSize;
    crossoverProbability = config.crossoverProbability;
    mutationProbability = config.mutationProbability;
    crossoverType = config.crossoverType;
    mutationType = config.mutationType;

    // Inicjalizacja engine (używamy seed z std::random_device)
    rng.seed(std::random_device{}());
}

// Metoda startowa algorytmu
void GeneticAlgo::solve() {
    initializePopulation();

    // Rejestracja ulepszeń - przechowujemy najlepszy wynik oraz czas jego znalezienia
    vector<SolutionRecord> improvements;

    // Znajdź najlepszy osobnik początkowy
    best = *min_element(population.begin(), population.end(),
                        [](const Individual& a, const Individual& b) {
                            return a.fitness < b.fitness;
                        });
    improvements.push_back({ best.fitness, best.tour, 0 });

    auto startTime = chrono::steady_clock::now();
    int generation = 0;

    while (chrono::duration_cast<chrono::seconds>(chrono::steady_clock::now() - startTime).count() < timeLimit) {
        vector<Individual> newPopulation;

        // Elityzm - zawsze zachowaj najlepszego osobnika
        newPopulation.push_back(best);

        // Tworzenie nowej populacji przy pomocy selekcji, krzyżowania i mutacji
        while (newPopulation.size() < population.size()) {
            Individual parent1 = tournamentSelection();
            Individual parent2 = tournamentSelection();

            Individual offspring;
            if (std::uniform_real_distribution<>(0.0, 1.0)(rng) < crossoverProbability) {
                offspring = crossover(parent1, parent2);
            } else {
                offspring = parent1;
            }

            if (std::uniform_real_distribution<>(0.0, 1.0)(rng) < mutationProbability) {
                mutate(offspring);
            }

            offspring.fitness = calculateFitness(offspring.tour);
            newPopulation.push_back(offspring);
        }

        population = move(newPopulation);
        generation++;

        // Aktualizacja najlepszego osobnika
        auto currentBest = *min_element(population.begin(), population.end(),
                                        [](const Individual& a, const Individual& b) {
                                            return a.fitness < b.fitness;
                                        });
        if (currentBest.fitness < best.fitness) {
            best = currentBest;
            auto elapsed = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startTime).count();
            improvements.push_back({ best.fitness, best.tour, elapsed });
            cout << "Nowe ulepszenie: " << best.fitness << " w generacji " << generation << endl;
        }
    }

    // Wyświetlenie najlepszego rozwiązania
    cout << "Najlepsze rozwiazanie znalezione po " << generation << " pokoleniach, o dlugosci: " << best.fitness << endl;
    cout << "Trasa: ";
    for (auto city : best.tour) {
        cout << city << " ";
    }
    cout << endl;
    if (!improvements.empty()) {
        saveResultsToCSV(config.saveFile, improvements.back());
    }
}

// Inicjalizacja populacji przy użyciu losowego przetasowania tras
// Dzięki temu zapewniamy większą różnorodność osobników
void GeneticAlgo::initializePopulation() {
    population.clear();

    // Pierwszy osobnik - generowany metodą nearest neighbour
    {
        // Wybieramy losowy punkt startowy
        std::uniform_int_distribution<> startDist(0, cityCount - 1);
        int startCity = startDist(rng);
        Individual indiv = greedyIndividual(startCity);
        indiv.fitness = calculateFitness(indiv.tour);
        population.push_back(indiv);
    }

    // Pozostałe osobniki - generowane przez shuffle
    for (int i = 1; i < populationSize; i++) {
        Individual indiv;
        indiv.tour.resize(cityCount);
        // Uzupełniamy trasę kolejnymi miastami
        for (int j = 0; j < cityCount; j++) {
            indiv.tour[j] = j;
        }
        // Utrzymujemy pierwszy element jako stały, a resztę tasujemy
        std::shuffle(indiv.tour.begin() + 1, indiv.tour.end(), rng);
        indiv.fitness = calculateFitness(indiv.tour);
        population.push_back(indiv);
    }
}

// Generowanie trasy metodą nearest neighbour (można zostawić jako alternatywę)
GeneticAlgo::Individual GeneticAlgo::greedyIndividual(int startCity) {
    Individual indiv;
    indiv.tour.reserve(cityCount);
    vector<bool> visited(cityCount, false);
    int currentCity = startCity;
    indiv.tour.push_back(currentCity);
    visited[currentCity] = true;

    for (int i = 1; i < cityCount; i++) {
        int nextCity = -1;
        int bestDist = std::numeric_limits<int>::max();
        for (int j = 0; j < cityCount; j++) {
            if (!visited[j]) {
                int d = distMatrix.getDistanceMatrix()[currentCity][j];
                if (d < bestDist) {
                    bestDist = d;
                    nextCity = j;
                }
            }
        }
        if (nextCity == -1)
            break;
        indiv.tour.push_back(nextCity);
        visited[nextCity] = true;
        currentCity = nextCity;
    }
    return indiv;
}

// Obliczanie długości trasy
int GeneticAlgo::calculateFitness(const vector<int>& tour) {
    int total = 0;
    int **matrix = distMatrix.getDistanceMatrix();
    for (size_t i = 0; i < tour.size() - 1; i++) {
        total += matrix[tour[i]][tour[i+1]];
    }
    // Dodajemy dystans powrotny do miasta początkowego
    total += matrix[tour.back()][tour.front()];
    return total;
}

// Wybór operatora krzyżowania (OX lub PMX)
GeneticAlgo::Individual GeneticAlgo::crossover(const Individual& parent1, const Individual& parent2) {
    if (crossoverType == "OX") {
        return crossoverOX(parent1, parent2);
    } else if (crossoverType == "PMX") {
        return crossoverPMX(parent1, parent2);
    } else {
        return crossoverOX(parent1, parent2);
    }
}

// Selekcja turniejowa
GeneticAlgo::Individual GeneticAlgo::tournamentSelection() {
    std::uniform_int_distribution<> distIndex(0, populationSize - 1);
    // Turniej 2-osobowy – dla większej różnorodności
    Individual bestCandidate = population[distIndex(rng)];
    Individual candidate = bestCandidate;
            //population[distIndex(rng)];
    if (candidate.fitness < bestCandidate.fitness) {
        bestCandidate = candidate;
    }
    return bestCandidate;
}

// Krzyżowanie Order Crossover (OX)
GeneticAlgo::Individual GeneticAlgo::crossoverOX(const Individual& parent1, const Individual& parent2) {
    Individual child;
    child.tour.resize(cityCount, -1);

    std::uniform_int_distribution<> dist(0, cityCount - 1);
    int start = dist(rng);
    int end = dist(rng);
    if (start > end)
        swap(start, end);

    // Kopiujemy fragment z parent1
    for (int i = start; i <= end; i++) {
        child.tour[i] = parent1.tour[i];
    }

    // Uzupełniamy pozostałe miejsca z parent2
    int current = (end + 1) % cityCount;
    for (int i = 0; i < cityCount; i++) {
        int candidate = parent2.tour[(end + 1 + i) % cityCount];
        if (find(child.tour.begin(), child.tour.end(), candidate) == child.tour.end()) {
            child.tour[current] = candidate;
            current = (current + 1) % cityCount;
        }
    }
    return child;
}

// Krzyżowanie PMX (Partially Mapped Crossover)
GeneticAlgo::Individual GeneticAlgo::crossoverPMX(const Individual& parent1, const Individual& parent2) {
    Individual child = parent1; // startujemy z kopią parent1
    std::uniform_int_distribution<> dist(0, cityCount - 1);
    int start = dist(rng);
    int end = dist(rng);
    if (start > end)
        swap(start, end);

    // Budujemy mapowanie dla regionu krzyżowania
    vector<int> mapping(cityCount, -1);
    for (int i = start; i <= end; i++) {
        mapping[parent2.tour[i]] = parent1.tour[i];
        child.tour[i] = parent2.tour[i];
    }

    // Poprawiamy konflikty poza regionem krzyżowania
    for (int i = 0; i < cityCount; i++) {
        if (i >= start && i <= end)
            continue;
        int gene = parent1.tour[i];
        while (find(child.tour.begin() + start, child.tour.begin() + end + 1, gene) != child.tour.begin() + end + 1) {
            gene = mapping[gene];
        }
        child.tour[i] = gene;
    }
    return child;
}

// Operator mutacji (swap lub inversion)
void GeneticAlgo::mutate(Individual& indiv) {
    if (mutationType == "swap") {
        mutationSwap(indiv);
    } else if (mutationType == "inversion") {
        mutationInversion(indiv);
    } else {
        // Domyślnie swap
        mutationSwap(indiv);
    }
}

// Mutacja swap - zamiana dwóch losowych miast
void GeneticAlgo::mutationSwap(Individual& indiv) {
    std::uniform_int_distribution<> dist(1, cityCount - 1); // zachowujemy pierwszy element
    int idx1 = dist(rng);
    int idx2 = dist(rng);
    while (idx2 == idx1) {
        idx2 = dist(rng);
    }
    swap(indiv.tour[idx1], indiv.tour[idx2]);
}

// Mutacja inversion - odwrócenie fragmentu trasy
void GeneticAlgo::mutationInversion(Individual& indiv) {
    std::uniform_int_distribution<> dist(1, cityCount - 1); // zachowujemy pierwszy element
    int start = dist(rng);
    int end = dist(rng);
    if (start > end)
        swap(start, end);
    reverse(indiv.tour.begin() + start, indiv.tour.begin() + end + 1);
}

// Funkcja zapisująca wyniki do pliku CSV
void GeneticAlgo::saveResultsToCSV(const std::string& filename, const SolutionRecord& bestSolution) {
    std::ofstream file(filename, ios::app);

    if (!file.is_open()) {
        cerr << "Nie udało się otworzyć pliku do zapisu: " << filename << endl;
        return;
    }

    // Zapisujemy nagłówki pliku CSV
    file << "Koszt,Trasa\n";

    // Zapisujemy najlepszy wynik
    file << bestSolution.cost << ",\"";

    // Zapis trasy jako ciągu liczb oddzielonych spacją
    for (size_t i = 0; i < bestSolution.tour.size(); ++i) {
        file << bestSolution.tour[i];
        if (i != bestSolution.tour.size() - 1) {
            file << " ";
        }
    }

    file << "\"\n"; // Zamykamy linię CSV
    file.close();

    cout << "Najlepszy wynik zapisano do pliku: " << filename << endl;
}