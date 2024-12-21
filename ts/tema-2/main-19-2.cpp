#include <iostream>
#include <random>
#include <vector>
#include <numeric>
#include <cmath>

/**
 * Sa se genereze variabila geometrica prin doua metode (curs 7).
 * Variabila geometrica reprezinta numarul de esecuri inainte de primul succes, care este intotdeauna un numar intreg.
 *
 * @author Mihai Tuhari
 */

// Initializare generator de numere aleatoare global
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> uniform(0.0, 1.0); // Distributie uniforma pe [0, 1]

/**
 * Algoritmul Binom1.
 *
 * → Intrare: n, p
 * → P1: i = 1, X = 0;
 * → P2: Se genereaza Z_i ∼ Bern(p), X := X + Z_i;
 * → P3: Daca i = n stop, altfel i := i + 1, mergi la P2;
 * → Iesire: Variabila aleatoare geometrica X.
 *
 * @param p Probabilitatea de succes
 * @param n Numarul maxim de iteratii
 *
 * @return int Variabila aleatoare geometrica
 */
int algoritm_Binom1(double p, int n) {
    // Initializare distributie Bernoulli
    std::bernoulli_distribution bernoulli(p);

    int X = 0; // Variabila geometrica - numaram esecurile

    for (int i = 0; i < n; ++i) { // Repetam pentru cel mult n iteratii
        if (bernoulli(gen)) {
            return X; // Primul succes - returnam numarul de esecuri
        }

        ++X; // Esec
    }

    return X; // Returnam numarul total de esecuri daca nu am avut succes
}

/**
 * Algoritmul Bernoulli.
 *
 * → Intrare: Probabilitatea de succes p
 * → P1: Se genereaza U ∼ U(0, 1);
 * → P2: Daca U ≤ 1 - p atunci Z = 0, altfel Z = 1;
 * → Iesire: Variabila aleatoare Z.
 *
 * @param p Probabilitatea de succes.
 *
 * @return int Variabila aleatoare geometrica (numarul de esecuri).
 */
int algoritm_Bernoulli(double p) {
    int X = 0; // Variabila geometrica - numaram esecurile

    // Generam pana cand avem un succes
    while (true) {
        double U = uniform(gen); // Generam o valoare uniforma

        if (U > 1 - p) { // Verificam daca avem succes
            break; // Succes - oprim bucla
        }

        ++X; // Incrementam pentru fiecare esec
    }

    return X; // Returnam numarul total de esecuri
}

/**
 * Functie pentru calculul mediei, dispersiei si deviatiei standard a selectiei.
 *
 * @param values Vectorul de valori generate.
 * @return Tuple (media, dispersia, deviatie standard).
 */
std::tuple<double, double, double> calculareMedieSiDispersie(const std::vector<int>& values) {
    // Calculam suma tuturor valorilor
    double sum = std::accumulate(values.begin(), values.end(), 0.0);

    // Calculam media valorilor
    double mean = sum / values.size();

    // Calculam suma patratelor valorilor
    double sq_sum = std::inner_product(values.begin(), values.end(), values.begin(), 0.0);

    // Calculam dispersia folosind formula dispersiei populatiei
    double variance = (sq_sum / values.size()) - (mean * mean);

    // Calculam deviatie standard
    double stddev = std::sqrt(variance);

    // Returnam media, dispersia si deviatia standard ca tuple
    return {mean, variance, stddev};
}

int main() {
    // Probabilitatea de succes
    double p = 0.5;
    int n = 100; // Numar maxim de iteratii pentru metoda Binom1
    int sample_size = 1000; // Numar de esantioane generate

    // Vectori pentru stocarea esantioanelor
    std::vector<int> samples_binom1;
    std::vector<int> samples_bernoulli;

    // Generare folosind metoda Binom1
    for (int i = 0; i < sample_size; ++i) {
        samples_binom1.push_back(algoritm_Binom1(p, n));
    }

    // Generare folosind metoda Bernoulli
    for (int i = 0; i < sample_size; ++i) {
        samples_bernoulli.push_back(algoritm_Bernoulli(p));
    }

    // Calculul mediei, dispersiei si deviatiei standard pentru Binom1
    auto [mean_binom1, variance_binom1, stddev_binom1] = calculareMedieSiDispersie(samples_binom1);
    std::cout << "Metoda Binom1:\n";
    std::cout << "Media: " << mean_binom1 << ", Dispersia: " << variance_binom1 << ", Deviatie standard: " << stddev_binom1 << "\n\n";

    // Calculul mediei, dispersiei si deviatiei standard pentru Bernoulli
    auto [mean_bernoulli, variance_bernoulli, stddev_bernoulli] = calculareMedieSiDispersie(samples_bernoulli);
    std::cout << "Metoda Bernoulli:\n";
    std::cout << "Media: " << mean_bernoulli << ", Dispersia: " << variance_bernoulli << ", Deviatie standard: " << stddev_bernoulli << "\n\n";

    return 0;
}
