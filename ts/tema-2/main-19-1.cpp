#include <iostream>
#include <cmath>
#include <random>

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

int main() {
    // Parametrii pentru Beta(3, 5)
    double a = 3.0;
    double b = 5.0;

    // Generare folosind metoda Beta3
    double beta3 = algoritm_Beta3(a, b);
    std::cout << "Variabila Beta(3, 5) generata prin Algoritmul Beta3: " << beta3 << std::endl;

    // Generare folosind metoda Norm2
    double norm2 = algoritm_Norm2(a, b);
    std::cout << "Variabila Beta(3, 5) generata prin Algoritmul Norm2: " << norm2 << std::endl;

    return 0;
}
