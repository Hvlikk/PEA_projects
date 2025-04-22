#include "DistMatrix.h"
#include "Config.h"
#include <vector>
#include <string>
#include <chrono>
#include <random>

using namespace std;

class GeneticAlgo {
public:
    struct Individual {
        std::vector<int> tour;
        int fitness;
    };

    // Struktura do zapisywania historii ulepszeń
    struct SolutionRecord {
        int cost;
        std::vector<int> tour;
        long long timeFound; // czas w milisekundach
    };

    GeneticAlgo(const DistMatrix& matrix, const Config& config);
    void solve();

private:
    // Parametry algorytmu
    int cityCount;
    int populationSize;
    int timeLimit;
    double crossoverProbability;
    double mutationProbability;
    std::string crossoverType; // np. "OX" lub "PMX"
    std::string mutationType;  // np. "swap" lub "inversion"

    const DistMatrix& distMatrix;
    Config config;

    std::vector<Individual> population;
    Individual best;

    std::mt19937 rng;

    // Metody pomocnicze
    void initializePopulation();
    Individual greedyIndividual(int startCity);
    int calculateFitness(const std::vector<int>& tour);

    // Operatory krzyżowania
    Individual crossover(const Individual& parent1, const Individual& parent2);
    Individual crossoverOX(const Individual& parent1, const Individual& parent2);
    Individual crossoverPMX(const Individual& parent1, const Individual& parent2);

    // Selekcja
    Individual tournamentSelection();

    // Mutacje
    void mutate(Individual& indiv);
    void mutationSwap(Individual& indiv);
    void mutationInversion(Individual& indiv);
    void saveResultsToCSV(const std::string& filename, const SolutionRecord& bestSolution);
};
