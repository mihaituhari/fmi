#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <numeric>
#include <tuple>

/**
 * Sa se genereze variabila Beta(3, 5) prin doua metode (curs 6).
 *
 * @author Mihai Tuhari
 */

// Initializare generator de numere aleatoare global
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> uniform(0.0, 1.0); // Distributie uniforma pe [0, 1]
std::exponential_distribution<> exp_dist(1.0); // Distributie exponentiala Exp(1)

/**
 * Algoritmul Beta3.
 *
 * → Intrare: 0 < a, b < 1
 * → P1: Se genereaza U1,U2 ∼ U(0, 1) independente;
 * → P2: V = U1 ^1/a, T = U2 ^1/b;
 * → P3: Daca V + T < 1 mergi la P4, altfel mergi la P1;
 * → P4: X := V / (V+T);
 * → Iesire: Variabila aleatoare X.
 *
 * @param a
 * @param b
 *
 * @return double
 */
double algoritm_Beta3(double a, double b) {
    double V, T, X;

    do {
        // P1) Generam doua valori uniforme independente pe [0, 1]
        double U1 = uniform(gen);
        double U2 = uniform(gen);

        // P2) Transformam valorile uniforme conform puterilor inverse ale parametrilor
        V = pow(U1, 1.0 / a);
        T = pow(U2, 1.0 / b);
    } while (V + T >= 1.0); // P3) Respingem daca suma depaseste 1

    // P4) Calculăm variabila Beta conform formulei X = V / (V + T)
    X = V / (V + T);

    return X;
}

/**
 * Algoritmul Norm2.
 *
 * → Intrare:
 * → P1: Se genereaza U ∼ U(0, 1);
 * → P2: Se genereaza Y ∼ Exp(1);
 * → P3: Daca U ≤ e^(-Y^2 / 2 + Y - 0.5) mergi la P4, altfel mergi la P1;
 * → P4: X1 := Y;
 * → P5: Se genereaza U ∼ U(0, 1);
 * → P6: Daca U ≤ 0.5 atunci s = 1, altfel s := −1;
 * → P7: X := sX1;
 * → Iesire: Variabila aleatoare X.
 *
 * @param a
 * @param b
 *
 * @return double
 */
double algoritm_Norm2(double a, double b) {
    double X1, U;

    // P1-P4: Generare X1 folosind metoda de compunere-respingere
    do {
        U = uniform(gen);         // P1) Generam U ∼ U(0, 1)
        double Y = exp_dist(gen); // P2) Generam Y ∼ Exp(1)

        if (U <= exp(-Y * Y / 2.0 + Y - 0.5)) {
            X1 = Y;              // P4) Acceptam Y
            break;
        }
    } while (true);

    // P5-P6: Generam U si determinam semnul s
    U = uniform(gen); // P5) Generam U ∼ U(0, 1)
    int s = (U <= 0.5) ? 1 : -1; // P6) Determinam semnul lui s

    // P7: Calculam X conform formulei X = s * X1
    double X = s * X1;

    // Scalam variabila folosind parametrii a si b
    return (X + a) / (a + b);
}

/**
 * Functie pentru calculul mediei, dispersiei si deviatiei standard a selectiei.
 *
 * @param values Vectorul de valori generate.
 * @return Tuple (media, dispersia, deviatie standard).
 */
std::tuple<double, double, double> calculareMedieSiDispersie(const std::vector<double>& values) {
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
    // Parametrii pentru Beta(3, 5)
    double a = 3.0;
    double b = 5.0;
    int n = 1000; // Numar de esantioane generate

    // Vectori pentru stocarea esantioanelor
    std::vector<double> samples_beta3;
    std::vector<double> samples_norm2;

    // Generare folosind metoda Beta3
    for (int i = 0; i < n; ++i) {
        samples_beta3.push_back(algoritm_Beta3(a, b));
    }

    // Generare folosind metoda Norm2
    for (int i = 0; i < n; ++i) {
        samples_norm2.push_back(algoritm_Norm2(a, b));
    }

    // Calculul mediei, dispersiei si deviatiei standard pentru Beta3
    auto [mean_beta3, variance_beta3, stddev_beta3] = calculareMedieSiDispersie(samples_beta3);
    std::cout << "Metoda Beta3:\n";
    std::cout << "Media: " << mean_beta3 << ", Dispersia: " << variance_beta3 << ", Deviatie standard: " << stddev_beta3 << "\n\n";

    // Calculul mediei, dispersiei si deviatiei standard pentru Norm2
    auto [mean_norm2, variance_norm2, stddev_norm2] = calculareMedieSiDispersie(samples_norm2);
    std::cout << "Metoda Norm2:\n";
    std::cout << "Media: " << mean_norm2 << ", Dispersia: " << variance_norm2 << ", Deviatie standard: " << stddev_norm2 << "\n\n";

    return 0;
}
