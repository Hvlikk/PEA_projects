//
// Created by Miłosz on 13.10.2024.
//

#include "iostream"
#include "fstream"
#include "Application.h"
#include "DistMatrix.h"
#include "../Algos/Asym/DFSSearchAS.h"
#include "../Algos/Asym/DFSSearchAS.h"
#include "../Algos/Asym/LowestCostSearchAS.h"
#include "../Algos/Symetric/BFSSearchS.h"
#include "../Algos/Symetric/DFSSearchS.h"
#include "../Algos/Symetric/LCSearchS.h"
#include "chrono"
#include "fstream"
#include "unistd.h"
using namespace std;
#include "iostream"

void Application::runApp() {

    //Nazwa pliku z danymi, stworzenie macierzy odległości, która jest przechowywana w klasie DistanceMatrix
    //const char* filename = "dane.txt";
    //DistMatrix dm(filename);
    DistMatrix chuj(14, 0);
    DFSSearchAS dfsSearchAsXD(chuj);
    dfsSearchAsXD.solve();
    dfsSearchAsXD.displayResult();
    system("pause");

    // Wyświetlamy macierz
//    dm.displayMatrix();
    ofstream dataOut("results13BESTASYM.txt", ios::app);
    for (int i = 0; i < 20; i++) {
            DistMatrix dm(13, 0);
        // Stworzenie obiektu klasy BruteForceTSP i przekazanie referencji do macierzy incydencji
        LowestCostSearchAS bruteForce(dm);
            auto startBF = chrono::high_resolution_clock::now();
            bruteForce.solve();
            auto endBF = chrono::high_resolution_clock::now();
            auto durationBF = chrono::duration_cast<chrono::nanoseconds>(endBF - startBF);
            bruteForce.displayResult();
            cout << durationBF.count() << " ns (BFS - NS) " << endl;
            dataOut << durationBF.count() << endl;
    }
    dataOut.close();

    dataOut.open("results14BESTASYM.txt", ios::app);
    for (int i = 0; i < 20; i++) {
        DistMatrix dm(14, 0);
        // Stworzenie obiektu klasy BruteForceTSP i przekazanie referencji do macierzy incydencji
        LowestCostSearchAS bruteForce(dm);
        auto startBF = chrono::high_resolution_clock::now();
        bruteForce.solve();
        auto endBF = chrono::high_resolution_clock::now();
        auto durationBF = chrono::duration_cast<chrono::nanoseconds>(endBF - startBF);
        bruteForce.displayResult();
        cout << durationBF.count() << " ns (BFS - NS) " << endl;
        dataOut << durationBF.count() << endl;
    }
    dataOut.close();

    dataOut.open("results15BESTASYM.txt", ios::app);
    for (int i = 0; i < 20; i++) {
        DistMatrix dm(15, 0);
        // Stworzenie obiektu klasy BruteForceTSP i przekazanie referencji do macierzy incydencji
        LowestCostSearchAS bruteForce(dm);
        auto startBF = chrono::high_resolution_clock::now();
        bruteForce.solve();
        auto endBF = chrono::high_resolution_clock::now();
        auto durationBF = chrono::duration_cast<chrono::nanoseconds>(endBF - startBF);
        bruteForce.displayResult();
        cout << durationBF.count() << " ns (BFS - NS) " << endl;
        dataOut << durationBF.count() << endl;
    }
    dataOut.close();

    dataOut.open("results16BESTASYM.txt", ios::app);
    for (int i = 0; i < 20; i++) {
        DistMatrix dm(16, 0);
        // Stworzenie obiektu klasy BruteForceTSP i przekazanie referencji do macierzy incydencji
        LowestCostSearchAS bruteForce(dm);
        auto startBF = chrono::high_resolution_clock::now();
        bruteForce.solve();
        auto endBF = chrono::high_resolution_clock::now();
        auto durationBF = chrono::duration_cast<chrono::nanoseconds>(endBF - startBF);
        bruteForce.displayResult();
        cout << durationBF.count() << " ns (BFS - NS) " << endl;
        dataOut << durationBF.count() << endl;
    }

    dataOut.close();

    dataOut.open("results17BESTASYM.txt", ios::app);
    for (int i = 0; i < 20; i++) {
        DistMatrix dm(17, 0);
        // Stworzenie obiektu klasy BruteForceTSP i przekazanie referencji do macierzy incydencji
        LowestCostSearchAS bruteForce(dm);
        auto startBF = chrono::high_resolution_clock::now();
        bruteForce.solve();
        auto endBF = chrono::high_resolution_clock::now();
        auto durationBF = chrono::duration_cast<chrono::nanoseconds>(endBF - startBF);
        bruteForce.displayResult();
        cout << durationBF.count() << " ns (BFS - NS) " << endl;
        dataOut << durationBF.count() << endl;
    }

    dataOut.close();

    dataOut.open("results18BESTASYM.txt", ios::app);
    for (int i = 0; i < 20; i++) {
        DistMatrix dm(18, 0);
        // Stworzenie obiektu klasy BruteForceTSP i przekazanie referencji do macierzy incydencji
        LowestCostSearchAS bruteForce(dm);
        auto startBF = chrono::high_resolution_clock::now();
        bruteForce.solve();
        auto endBF = chrono::high_resolution_clock::now();
        auto durationBF = chrono::duration_cast<chrono::nanoseconds>(endBF - startBF);
        bruteForce.displayResult();
        cout << durationBF.count() << " ns (BFS - NS) " << endl;
        dataOut << durationBF.count() << endl;
    }

    dataOut.close();

    dataOut.open("results19BESTASYM.txt", ios::app);
    for (int i = 0; i < 20; i++) {
        DistMatrix dm(19, 0);
        // Stworzenie obiektu klasy BruteForceTSP i przekazanie referencji do macierzy incydencji
        LowestCostSearchAS bruteForce(dm);
        auto startBF = chrono::high_resolution_clock::now();
        bruteForce.solve();
        auto endBF = chrono::high_resolution_clock::now();
        auto durationBF = chrono::duration_cast<chrono::nanoseconds>(endBF - startBF);
        bruteForce.displayResult();
        cout << durationBF.count() << " ns (BFS - NS) " << endl;
        dataOut << durationBF.count() << endl;
    }
    dataOut.close();


    dataOut.open("results20BESTASYM.txt", ios::app);
    for (int i = 0; i < 20; i++) {
        DistMatrix dm(20, 0);
        // Stworzenie obiektu klasy BruteForceTSP i przekazanie referencji do macierzy incydencji
        LowestCostSearchAS bruteForce(dm);
        auto startBF = chrono::high_resolution_clock::now();
        bruteForce.solve();
        auto endBF = chrono::high_resolution_clock::now();
        auto durationBF = chrono::duration_cast<chrono::nanoseconds>(endBF - startBF);
        bruteForce.displayResult();
        cout << durationBF.count() << " ns (BFS - NS) " << endl;
        dataOut << durationBF.count() << endl;
    }
    dataOut.close();
    dataOut.open("results13BESTSYM.txt", ios::app);
    for (int i = 0; i < 20; i++) {
        DistMatrix dm(13, 1);
        // Stworzenie obiektu klasy BruteForceTSP i przekazanie referencji do macierzy incydencji
        LCSearchS bruteForce(dm);
        auto startBF = chrono::high_resolution_clock::now();
        bruteForce.solve();
        auto endBF = chrono::high_resolution_clock::now();
        auto durationBF = chrono::duration_cast<chrono::nanoseconds>(endBF - startBF);
        bruteForce.displayResult();
        cout << durationBF.count() << " ns (BFS - NS) " << endl;
        dataOut << durationBF.count() << endl;
    }
    dataOut.close();

    dataOut.open("results14BESTSYM.txt", ios::app);
    for (int i = 0; i < 20; i++) {
        DistMatrix dm(14, 1);
        // Stworzenie obiektu klasy BruteForceTSP i przekazanie referencji do macierzy incydencji
        LCSearchS bruteForce(dm);
        auto startBF = chrono::high_resolution_clock::now();
        bruteForce.solve();
        auto endBF = chrono::high_resolution_clock::now();
        auto durationBF = chrono::duration_cast<chrono::nanoseconds>(endBF - startBF);
        bruteForce.displayResult();
        cout << durationBF.count() << " ns (BFS - NS) " << endl;
        dataOut << durationBF.count() << endl;
    }
    dataOut.close();

    dataOut.open("results15BESTSYM.txt", ios::app);
    for (int i = 0; i < 20; i++) {
        DistMatrix dm(15, 1);
        // Stworzenie obiektu klasy BruteForceTSP i przekazanie referencji do macierzy incydencji
        LCSearchS bruteForce(dm);
        auto startBF = chrono::high_resolution_clock::now();
        bruteForce.solve();
        auto endBF = chrono::high_resolution_clock::now();
        auto durationBF = chrono::duration_cast<chrono::nanoseconds>(endBF - startBF);
        bruteForce.displayResult();
        cout << durationBF.count() << " ns (BFS - NS) " << endl;
        dataOut << durationBF.count() << endl;
    }
    dataOut.close();

    dataOut.open("results16BESTSYM.txt", ios::app);
    for (int i = 0; i < 20; i++) {
        DistMatrix dm(16, 1);
        // Stworzenie obiektu klasy BruteForceTSP i przekazanie referencji do macierzy incydencji
        LCSearchS bruteForce(dm);
        auto startBF = chrono::high_resolution_clock::now();
        bruteForce.solve();
        auto endBF = chrono::high_resolution_clock::now();
        auto durationBF = chrono::duration_cast<chrono::nanoseconds>(endBF - startBF);
        bruteForce.displayResult();
        cout << durationBF.count() << " ns (BFS - NS) " << endl;
        dataOut << durationBF.count() << endl;
    }

    dataOut.close();

    dataOut.open("results17BESTSYM.txt", ios::app);
    for (int i = 0; i < 20; i++) {
        DistMatrix dm(17, 1);
        // Stworzenie obiektu klasy BruteForceTSP i przekazanie referencji do macierzy incydencji
        LCSearchS bruteForce(dm);
        auto startBF = chrono::high_resolution_clock::now();
        bruteForce.solve();
        auto endBF = chrono::high_resolution_clock::now();
        auto durationBF = chrono::duration_cast<chrono::nanoseconds>(endBF - startBF);
        bruteForce.displayResult();
        cout << durationBF.count() << " ns (BFS - NS) " << endl;
        dataOut << durationBF.count() << endl;
    }

    dataOut.close();

    dataOut.open("results18BESTSYM.txt", ios::app);
    for (int i = 0; i < 20; i++) {
        DistMatrix dm(18, 1);
        // Stworzenie obiektu klasy BruteForceTSP i przekazanie referencji do macierzy incydencji
        LCSearchS bruteForce(dm);
        auto startBF = chrono::high_resolution_clock::now();
        bruteForce.solve();
        auto endBF = chrono::high_resolution_clock::now();
        auto durationBF = chrono::duration_cast<chrono::nanoseconds>(endBF - startBF);
        bruteForce.displayResult();
        cout << durationBF.count() << " ns (BFS - NS) " << endl;
        dataOut << durationBF.count() << endl;
    }

    dataOut.close();

    dataOut.open("results19BESTSYM.txt", ios::app);
    for (int i = 0; i < 20; i++) {
        DistMatrix dm(19, 1);
        // Stworzenie obiektu klasy BruteForceTSP i przekazanie referencji do macierzy incydencji
        LCSearchS bruteForce(dm);
        auto startBF = chrono::high_resolution_clock::now();
        bruteForce.solve();
        auto endBF = chrono::high_resolution_clock::now();
        auto durationBF = chrono::duration_cast<chrono::nanoseconds>(endBF - startBF);
        bruteForce.displayResult();
        cout << durationBF.count() << " ns (BFS - NS) " << endl;
        dataOut << durationBF.count() << endl;
    }
    dataOut.close();


    dataOut.open("results20BESTSYM.txt", ios::app);
    for (int i = 0; i < 20; i++) {
        DistMatrix dm(20, 1);
        // Stworzenie obiektu klasy BruteForceTSP i przekazanie referencji do macierzy incydencji
        LCSearchS bruteForce(dm);
        auto startBF = chrono::high_resolution_clock::now();
        bruteForce.solve();
        auto endBF = chrono::high_resolution_clock::now();
        auto durationBF = chrono::duration_cast<chrono::nanoseconds>(endBF - startBF);
        bruteForce.displayResult();
        cout << durationBF.count() << " ns (BFS - NS) " << endl;
        dataOut << durationBF.count() << endl;
    }
    dataOut.close();
    // Stworzenie obiektu klasy ClosestNeighbourTSP i przekazanie referencji do macierzy incydencji
    /* DFSSearchAS dfsSearchAs(dm); // Create an instance of the NearestNeighborTSP
     auto startDFS = chrono::high_resolution_clock::now();
     dfsSearchAs.solve();
     auto endDFS = chrono::high_resolution_clock::now();
     auto durationDFS = chrono::duration_cast<chrono::nanoseconds>(endDFS - startDFS);
     dfsSearchAs.displayResult();
     cout << durationDFS.count() << " ns (DFS - NS)" << endl;


    LowestCostSearchAS lowest(dm);
    auto startLCS = chrono::high_resolution_clock::now();
    lowest.solve();
    auto endLCS = chrono::high_resolution_clock::now();
    auto durationLCS = chrono::duration_cast<chrono::nanoseconds >(endLCS - startLCS);
    lowest.displayResult();
    cout << durationLCS.count() << " ns (LCS - NS)" << endl;

    BFSSearchS bfsSym(dm);
    auto startBFS = chrono::high_resolution_clock::now();
    bfsSym.solve();
    auto endBFS = chrono::high_resolution_clock::now();
    auto durationBFS = chrono::duration_cast<chrono::nanoseconds>(endBFS - startBFS);
    bfsSym.displayResult();
    cout << durationBFS.count() << " ns (BFS - S) " << endl;

    DFSSearchS dfsSym(dm);
    auto startDFSS = chrono::high_resolution_clock::now();
    dfsSym.solve();
    auto endDFSS = chrono::high_resolution_clock::now();
    auto durationDFSS = chrono::duration_cast<chrono::nanoseconds>(endDFSS - startDFSS);
    dfsSym.displayResult();
    cout << durationDFSS.count() << " ns (DFS - S) " << endl;

    LCSearchS lcsSym(dm);
    auto startLCSS = chrono::high_resolution_clock::now();
    lcsSym.solve();
    auto endLCSS = chrono::high_resolution_clock::now();
    auto durationLCSS = chrono::duration_cast<chrono::nanoseconds>(endLCSS - startLCSS);
    lcsSym.displayResult();
    cout << durationLCSS.count() << " ns (LCS - S) " << endl;
    //auto startNN = chrono::high_resolution_clock::now();
    //closestNTSP.findShortestPath();     // Find the shortest path using nearest neighbor heuristic
   // auto endNN = chrono::high_resolution_clock::now();
   //auto durationNN = chrono::duration_cast<chrono::nanoseconds>(endNN - startNN);
    // Wyswietlenie trasy i jej dystansu
   // closestNTSP.displayBestPath();
*/
   // dataOut << "Czas wykonania algorytmu przegladu najblizszego sasiada (ns)";
   // dataOut << endl;
   // dataOut << durationNN.count() << endl;

    // Stworzenie obiektu klasy RandomInspectionTSP i przekazanie referencji do macierzy incydencji
   // RandomInspectionTSP randomTSP(dm); // Create an instance of the RandomTSP
//auto startR = chrono::high_resolution_clock::now();
//randomTSP.findRandomPath(dm.getIterations()); // Find a random path with 200 iterations
//auto endR = chrono::high_resolution_clock::now();
   // auto durationR = chrono::duration_cast<chrono::nanoseconds>(endR - startR);

    // Wyswietlenie trasy i jej dystansu
    //randomTSP.displayBestPath();
   // dataOut << "Czas wykonania algorytmu przegladu losowego (ns)";
   // dataOut << endl;
   // dataOut << durationR.count() << endl;


}
