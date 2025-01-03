#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>
#include "helper_validation.h"

/*
 * Metoda 1: Generare Beta(a, b) folosind Gamma
 *
 * Teorie:
 * Conform teoremei, daca X1 ~ Gamma(a, 1) si X2 ~ Gamma(b, 1) sunt variabile aleatoare independente,
 * atunci variabila aleatoare X = X1 / (X1 + X2) urmeaza o distributie Beta(a, b).
 * Aceasta metoda implica generarea a doua variabile Gamma si calcularea raportului lor.
 */
double generateBetaGamma(double a, double b, std::mt19937 &gen) {
    double x1 = Helper::generateGamma(a, gen);
    double x2 = Helper::generateGamma(b, gen);
    return x1 / (x1 + x2);
}

/*
 * Metoda 2: Generare Beta(a, b) folosind statistici de ordine
 *
 * Teorie:
 * Daca U1, U2, ..., Un sunt variabile aleatoare independente si uniforme pe [0, 1], iar n = a + b - 1,
 * atunci statisticile de ordine U(1) < U(2) < ... < U(n) satisfac U(a) ~ Beta(a, b).
 * Aceasta metoda implica generarea de n variabile uniforme, sortarea lor si returnarea a-1 statisticii de ordine.
 */
double generateBetaOrderStatistics(int a, int b, std::mt19937 &gen) {
    int n = a + b - 1;
    std::vector<double> uValues(n);

    // Generam variabile uniforme
    std::uniform_real_distribution<> uniformDist(0.0, 1.0);
    for (int i = 0; i < n; ++i) {
        uValues[i] = uniformDist(gen);
    }

    // Sortam valorile
    std::sort(uValues.begin(), uValues.end());

    // Returnam a-1 statistica de ordine
    return uValues[a - 1];
}

int main() {
    double a = 3.0;
    double b = 5.0;
    int sampleSize = 1000;

    double expectedMean = a / (a + b);
    double expectedVariance = (a * b) / ((a + b) * (a + b) * (a + b + 1));

    // Seed pentru generatorul de numere aleatoare
    std::random_device rd;
    std::mt19937 gen(rd());

    // Generam valori pentru ambele metode
    std::vector<double> samplesGamma(sampleSize);
    std::vector<double> samplesOrderStatistics(sampleSize);

    for (int i = 0; i < sampleSize; ++i) {
        samplesGamma[i] = generateBetaGamma(a, b, gen);
        samplesOrderStatistics[i] = generateBetaOrderStatistics(static_cast<int>(a), static_cast<int>(b), gen);
    }

    // Calculam statisticile pentru fiecare metoda
    double meanGamma = Helper::mean(samplesGamma); // Media 1
    double meanOrderStatistics = Helper::mean(samplesOrderStatistics); // Media 2

    double varianceGamma = Helper::variance(samplesGamma); // Dispersia 1
    double varianceOrderStatistics = Helper::variance(samplesOrderStatistics); // Dispersia 2

    // Afisam rezultatele
    std::cout << std::fixed << std::setprecision(10);
    std::cout << "----------------------------------------------------------------------" << std::endl;
    std::cout << "|                       | General      | Metoda 1     | Metoda 2     |" << std::endl;
    std::cout << "----------------------------------------------------------------------" << std::endl;
    std::cout << "| Media                 | " << expectedMean << " | " << meanGamma << " | " << meanOrderStatistics
              << " |" << std::endl;
    std::cout << "| Dispersia de selectie | " << expectedVariance << " | " << varianceGamma << " | "
              << varianceOrderStatistics << " |" << std::endl;
    std::cout << "----------------------------------------------------------------------" << std::endl;

    return 0;
}
