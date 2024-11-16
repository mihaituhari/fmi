#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<double> MetodaJacobi(vector<vector<double>> &A, vector<double> &b, double eps) {
    int n = A.size();
    vector<double> x0(n, 0); // solutia initiala
    vector<double> x1(n); // solutia noua
    double norm; // norma pentru convergenta

    do {
        // Calculam noile valori x1
        for (int j = 0; j < n; j++) {
            double suma = 0;
            for (int k = 0; k < n; k++) {
                if (k != j) {
                    suma += A[j][k] * x0[k];
                }
            }
            x1[j] = (b[j] - suma) / A[j][j];
        }

        // Calculam norma (suma Jacobi)
        norm = 0;
        for (int j = 0; j < n; j++) {
            norm += fabs(x1[j] - x0[j]);
        }

        // Actualizam solutia
        x0 = x1;

    } while (norm >= eps);

    return x0;
}

int main() {
    // Sistem de test:
    // 4x + y + z = 6
    // x + 4y + z = 6
    // x + y + 4z = 6

    vector<vector<double>> A = {
            {4, 1, 1},
            {1, 4, 1},
            {1, 1, 4}
    };

    vector<double> b = {6, 6, 6};
    double eps = 0.0001;

    vector<double> solutie = MetodaJacobi(A, b, eps);

    cout << "Solutia sistemului este:\n";
    for (int j = 0; j < solutie.size(); j++) {
        cout << "x" << j + 1 << " = " << solutie[j] << endl;
    }

    return 0;
}
