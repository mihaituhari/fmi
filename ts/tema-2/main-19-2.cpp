#include <iostream>
#include <random>

/**
 * Sa se genereze variabila geometrica prin doua metode (curs 7).
 * Variabila geometrica reprezinta numarul de esecuri inainte de primul succes, care este intotdeauna un numar întreg.
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

    return X;
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

    while (true) {
        double U = uniform(gen); // P1) Generam o valoare uniforma

        if (U > 1 - p) { // P2) Verificam daca avem succes
            break; // Succes - oprim bucla
        }

        ++X; // Esec
    }

    return X;
}

int main() {
    // Probabilitatea de succes
    double p = 0.5;
    int n = 100; // Numar maxim de iteratii pentru metoda Binom1

    // Generare folosind metoda Binom1
    int geometric1 = algoritm_Binom1(p, n);
    std::cout << "Variabila geometrica generata prin metoda Binom1: " << geometric1 << std::endl;

    // Generare folosind metoda Bernoulli
    int geometric2 = algoritm_Bernoulli(p);
    std::cout << "Variabila geometrica generata prin metoda Bernoulli: " << geometric2 << std::endl;

    return 0;
}
