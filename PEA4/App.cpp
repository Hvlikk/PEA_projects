//
// Created by Miłosz on 16.01.2025.
//

#include "App.h"
#include "DistMatrix.h"
#include "fstream"
#include "iostream"
#include "Config.h"
#include "GeneticAlgo.h"
using namespace std;

void App::runApp() {

    Config config;
    char* configFile = "config8OXI.txt";

    if (!config.loadConfig(configFile)) {
        cerr << "Nie udało się wczytać pliku konfiguracyjnego." << endl;
        exit(1);
    }

    DistMatrix matrix(config.filePath.c_str());
    matrix.displayMatrix();

    GeneticAlgo ga(matrix, config);
    ga.solve();

    GeneticAlgo ga1(matrix, config);
    ga1.solve();

    GeneticAlgo ga2(matrix, config);
    ga2.solve();

    GeneticAlgo ga3(matrix, config);
    ga3.solve();

    GeneticAlgo ga4(matrix, config);
    ga4.solve();

    configFile = "config8OXS.txt";
    config.loadConfig(configFile);

    GeneticAlgo ga5(matrix, config);
    ga5.solve();

    GeneticAlgo ga6(matrix, config);
    ga6.solve();

    GeneticAlgo ga7(matrix, config);
    ga7.solve();

    GeneticAlgo ga8(matrix, config);
    ga8.solve();

    GeneticAlgo ga9(matrix, config);
    ga9.solve();

    configFile = "config8PMXS.txt";
    config.loadConfig(configFile);

    GeneticAlgo ga10(matrix, config);
    ga10.solve();

    GeneticAlgo ga11(matrix, config);
    ga11.solve();

    GeneticAlgo ga12(matrix, config);
    ga12.solve();

    GeneticAlgo ga13(matrix, config);
    ga13.solve();

    GeneticAlgo ga14(matrix, config);
    ga14.solve();

    configFile = "config8PMXI.txt";
    config.loadConfig(configFile);

    GeneticAlgo ga15(matrix, config);
    ga15.solve();

    GeneticAlgo ga16(matrix, config);
    ga16.solve();

    GeneticAlgo ga17(matrix, config);
    ga17.solve();

    GeneticAlgo ga18(matrix, config);
    ga18.solve();

    GeneticAlgo ga19(matrix, config);
    ga19.solve();

    configFile = "config10OXS.txt";
    config.loadConfig(configFile);

    GeneticAlgo ga20(matrix, config);
    ga20.solve();

    GeneticAlgo ga21(matrix, config);
    ga21.solve();

    GeneticAlgo ga22(matrix, config);
    ga22.solve();

    GeneticAlgo ga23(matrix, config);
    ga23.solve();

    GeneticAlgo ga24(matrix, config);
    ga24.solve();

    configFile = "config10OXI.txt";
    config.loadConfig(configFile);

    GeneticAlgo ga25(matrix, config);
    ga25.solve();

    GeneticAlgo ga26(matrix, config);
    ga26.solve();

    GeneticAlgo ga27(matrix, config);
    ga27.solve();

    GeneticAlgo ga28(matrix, config);
    ga28.solve();

    GeneticAlgo ga29(matrix, config);
    ga29.solve();

    configFile = "config10PMXS.txt";
    config.loadConfig(configFile);

    GeneticAlgo ga30(matrix, config);
    ga30.solve();

    GeneticAlgo ga31(matrix, config);
    ga31.solve();

    GeneticAlgo ga32(matrix, config);
    ga32.solve();

    GeneticAlgo ga33(matrix, config);
    ga33.solve();

    GeneticAlgo ga34(matrix, config);
    ga34.solve();

    configFile = "config10PMXI.txt";
    config.loadConfig(configFile);

    GeneticAlgo ga35(matrix, config);
    ga35.solve();

    GeneticAlgo ga36(matrix, config);
    ga36.solve();

    GeneticAlgo ga37(matrix, config);
    ga37.solve();

    GeneticAlgo ga38(matrix, config);
    ga38.solve();

    GeneticAlgo ga39(matrix, config);
    ga39.solve();

    configFile = "config12OXS.txt";
    config.loadConfig(configFile);

    GeneticAlgo ga40(matrix, config);
    ga40.solve();

    GeneticAlgo ga41(matrix, config);
    ga41.solve();

    GeneticAlgo ga42(matrix, config);
    ga42.solve();

    GeneticAlgo ga43(matrix, config);
    ga43.solve();

    GeneticAlgo ga44(matrix, config);
    ga44.solve();

    configFile = "config12OXI.txt";
    config.loadConfig(configFile);

    GeneticAlgo ga45(matrix, config);
    ga45.solve();

    GeneticAlgo ga46(matrix, config);
    ga46.solve();

    GeneticAlgo ga47(matrix, config);
    ga47.solve();

    GeneticAlgo ga48(matrix, config);
    ga48.solve();

    GeneticAlgo ga49(matrix, config);
    ga49.solve();

    configFile = "config12PMXS.txt";
    config.loadConfig(configFile);

    GeneticAlgo ga50(matrix, config);
    ga50.solve();

    GeneticAlgo ga51(matrix, config);
    ga51.solve();

    GeneticAlgo ga52(matrix, config);
    ga52.solve();

    GeneticAlgo ga53(matrix, config);
    ga53.solve();

    GeneticAlgo ga54(matrix, config);
    ga54.solve();

    configFile = "config12PMXI.txt";
    config.loadConfig(configFile);

    GeneticAlgo ga55(matrix, config);
    ga55.solve();

    GeneticAlgo ga56(matrix, config);
    ga56.solve();

    GeneticAlgo ga57(matrix, config);
    ga57.solve();

    GeneticAlgo ga58(matrix, config);
    ga58.solve();

    GeneticAlgo ga59(matrix, config);
    ga59.solve();

    system("pause");

}