#include <iostream>
#include <cstdlib>

/**
 * Simulare Monte Carlo pentru probabilitatea de a obtine un numar ca suma a doua zaruri aruncate.
 *
 * Acest program simuleaza aruncarea a două zaruri de un numar setat de un milion de ori si calculeaza
 * probabilitatea ca suma celor doua zaruri sa fie egală cu un numar introdus de la tastatura.
 *
 * Programul:
 *  1. Solicita utilizatorului sa introduca un numar tinta pentru suma celor doua zaruri,
 *     avand valoare intre 2 si 12.
 *  2. Simuleaza aruncarea a doua zaruri pentru fiecare din numarul de aruncări specificat.
 *     Aceasta este o metoda de simulare Monte Carlo, in care generam o serie de aruncari aleatorii
 *     pentru a estima probabilitatea unui eveniment (suma sa fie cea introdusa).
 *  3. Verifica dacă suma obținuta este cea introdusa si numara de cate ori se intampla acest lucru.
 *  4. Calculeaza probabilitatea ca suma să fie cea introdusa, afisand rezultatul ca procentaj.
 *
 * @author Mihai Tuhari (FMI ID, anul 3)
*/

int numarAruncari = 1000000;
int sumaTinta;

double simuleazaAruncareZaruri() {
    int sumaNimerita = 0;

    for (int i = 0; i < numarAruncari; i++) {
        int zar1 = rand() % 6 + 1; // Simulam aruncarea primului zar
        int zar2 = rand() % 6 + 1; // Simulam aruncarea celui de-al doilea zar
        int suma = zar1 + zar2;

        if (suma == sumaTinta) {
            sumaNimerita++;
        }
    }

    double probabilitate = static_cast<double>(sumaNimerita) / numarAruncari;

    return probabilitate;
}

int main() {
    std::cout << "Introduceti numarul tinta pentru suma zarurilor: ";
    std::cin >> sumaTinta;

    if (sumaTinta < 2 || sumaTinta > 12) {
        std::cout << "❌ Numar invalid. Trebuie sa fie intre 2 si 12.";
        return 0;
    }

    double probability = simuleazaAruncareZaruri();
    std::cout << "🎲 Probabilitatea de a obtine suma zarurilor " << sumaTinta
              << " din " << numarAruncari << " aruncari este de aproximativ: "
              << (probability * 100) << "%";

    return 1;
}
