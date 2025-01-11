#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>
#include "helper_validation.h"

/*
 * Metoda 1: Generare variabila geometrica folosind algoritmul Pascal
 *
 * Curs 7, pag. 10-11
 *
 * Teorie:
 * Generam variabile Bernoulli repetate pana la primul succes.
 * Conform algoritmului Pascal, numaram numarul de esecuri pana la aparitia unui succes.
 * Programul folosește o distribuție Bernoulli repetata pentru a numara eșecurile pana la apariția unui succes.
 */
int generateGeometricPascal(double p, std::mt19937 &gen) {
    std::bernoulli_distribution bernoulliDist(p);
    int failures = 0;

    while (!bernoulliDist(gen)) {
        failures++;
    }

    return failures;
}

/*
 * Metoda 2: Generare variabila geometrica folosind "Algoritm Geometrică"
 *
 * Curs 7, pag. 12
 *
 * Teorie:
 * Variabila geometrica poate fi generata direct folosind metoda inversa:
 * X = floor(log(U) / log(1-p)), unde U este uniforma pe [0, 1].
 */
int generateGeometricInverse(double p, std::mt19937 &gen) {
    std::uniform_real_distribution<> uniformDist(0.0, 1.0);
    double u = uniformDist(gen);

    return static_cast<int>(std::floor(std::log(u) / std::log(1.0 - p)));
}

/**
 * Sa se genereze variabila geometrica prin doua metode (curs 7).
 *
 * Ambele metode sunt validate prin compararea mediilor si dispersiei obținute cu cele teoretice
 */
int main() {
    double p = 0.3; // Probabilitatea de succes
    double q = 1.0 - p; // Complementul lui p
    int sampleSize = 1000;

    double expectedMean = q / p; // Media asteptata
    double expectedVariance = q / (p * p); // Dispersia asteptata

    // Seed pentru generatorul de numere aleatoare
    std::random_device rd;
    std::mt19937 gen(rd());

    // Generam valori pentru ambele metode
    std::vector<int> samplesPascal(sampleSize);
    std::vector<int> samplesInverse(sampleSize);

    for (int i = 0; i < sampleSize; ++i) {
        samplesPascal[i] = generateGeometricPascal(p, gen);
        samplesInverse[i] = generateGeometricInverse(p, gen);
    }

    // Calculam statisticile pentru fiecare metoda
    double meanPascal = Helper::mean(std::vector<double>(samplesPascal.begin(), samplesPascal.end())); // Media 1
    double meanInverse = Helper::mean(std::vector<double>(samplesInverse.begin(), samplesInverse.end())); // Media 2

    double variancePascal = Helper::variance(std::vector<double>(samplesPascal.begin(), samplesPascal.end())); // Dispersia 1
    double varianceInverse = Helper::variance(std::vector<double>(samplesInverse.begin(), samplesInverse.end())); // Dispersia 2

    // Afisam rezultatele
    std::cout << std::fixed << std::setprecision(10);
    std::cout << "----------------------------------------------------------------------" << std::endl;
    std::cout << "|                       | General      | Metoda 1     | Metoda 2     |" << std::endl;
    std::cout << "----------------------------------------------------------------------" << std::endl;
    std::cout << "| Media                 | " << expectedMean << " | " << meanPascal << " | " << meanInverse << " |" << std::endl;
    std::cout << "| Dispersia de selectie | " << expectedVariance << " | " << variancePascal << " | " << varianceInverse << " |" << std::endl;
    std::cout << "----------------------------------------------------------------------" << std::endl;

    return 0;
}
