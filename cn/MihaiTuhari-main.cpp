// Mihai Tuhari, gr 1 / an 3 / ID Mate-Info
#include <iostream>
#include <cmath>

using namespace std;

const int MAX = 10; // Dimensiunea maximă a matricii

// Functia de citire a matricei extinse
void citesteMatriceExtinsa(float a[MAX][MAX], int &n) {
    cout << "n = ";
    cin >> n;
    cout << "Introduceti coeficientii matricei extinse: " << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n + 1; j++) {
            cout << "a[" << i << "][" << j << "] = ";
            cin >> a[i][j];
        }
    }
}

// Functia de afisare a solutiilor
void afisareSolutii(float x[MAX], int n) {
    cout << "Solutii: " << endl;
    for (int i = 1; i <= n; i++) {
        cout << "x[" << i << "] = " << x[i] << endl;
    }
}

// Functia de afisare pentru matrice
void afisareMatrice(float m[MAX][MAX], int n, const string &nume) {
    cout << "Matricea " << nume << ":" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
}

// 1. Rezolvarea sistemului cu matrice triunghiulară inferioară
void rezolvaInferioara(float L[MAX][MAX], float b[MAX], float x[MAX], int n) {
    for (int i = 1; i <= n; i++) {
        x[i] = b[i];
        for (int j = 1; j < i; j++) {
            x[i] -= L[i][j] * x[j];
        }
        x[i] /= L[i][i];
    }
}

// 2. Rezolvarea sistemului cu matrice triunghiulară superioară
void rezolvaSuperioara(float U[MAX][MAX], float b[MAX], float x[MAX], int n) {
    for (int i = n; i >= 1; i--) {
        x[i] = b[i];
        for (int j = i + 1; j <= n; j++) {
            x[i] -= U[i][j] * x[j];
        }
        x[i] /= U[i][i];
    }
}

// 3. Metoda Gauss cu pivotare totală
void gaussPivotareTotala(float a[MAX][MAX], float x[MAX], int n) {
    for (int i = 1; i <= n; i++) {
        int pivotRow = i, pivotCol = i;

        for (int j = i; j <= n; j++) {
            for (int k = i; k <= n; k++) {
                if (fabs(a[j][k]) > fabs(a[pivotRow][pivotCol])) {
                    pivotRow = j;
                    pivotCol = k;
                }
            }
        }

        if (pivotRow != i) swap(a[i], a[pivotRow]);
        if (pivotCol != i) {
            for (int j = 1; j <= n + 1; j++) swap(a[j][i], a[j][pivotCol]);
        }

        for (int j = i + 1; j <= n; j++) {
            float ratio = a[j][i] / a[i][i];
            for (int k = 1; k <= n + 1; k++) {
                a[j][k] -= ratio * a[i][k];
            }
        }
    }

    for (int i = n; i >= 1; i--) {
        x[i] = a[i][n + 1];
        for (int j = i + 1; j <= n; j++) {
            x[i] -= a[i][j] * x[j];
        }
        x[i] /= a[i][i];
    }
}

// 4. Metoda Gauss-Jordan pentru determinarea inversei
void gaussJordanInversa(float a[MAX][MAX], int n) {
    float inv[MAX][MAX];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) inv[i][j] = (i == j) ? 1 : 0;
    }

    for (int i = 1; i <= n; i++) {
        float pivot = a[i][i];
        for (int j = 1; j <= n; j++) {
            a[i][j] /= pivot;
            inv[i][j] /= pivot;
        }
        for (int j = 1; j <= n; j++) {
            if (i != j) {
                float ratio = a[j][i];
                for (int k = 1; k <= n; k++) {
                    a[j][k] -= ratio * a[i][k];
                    inv[j][k] -= ratio * inv[i][k];
                }
            }
        }
    }

    cout << "Inversa: " << endl;
    afisareMatrice(inv, n, "Inversa");
}

// 5. Factorizare LU și rezolvarea sistemului
void factorizareLU(float a[MAX][MAX], float L[MAX][MAX], float U[MAX][MAX], int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j < i) L[j][i] = 0;
            else {
                L[i][j] = a[i][j];
                for (int k = 1; k < i; k++) L[i][j] -= L[i][k] * U[k][j];
            }
        }
        for (int j = 1; j <= n; j++) {
            if (j < i) U[i][j] = 0;
            else if (i == j) U[i][j] = 1;
            else {
                U[i][j] = a[i][j] / L[i][i];
                for (int k = 1; k < i; k++) U[i][j] -= ((L[i][k] * U[k][j]) / L[i][i]);
            }
        }
    }
    afisareMatrice(L, n, "L");
    afisareMatrice(U, n, "U");
}

// 6. Factorizare Cholesky \( L^T L \)
void factorizareCholesky(float A[MAX][MAX], float L[MAX][MAX], int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            float sum = 0;
            if (i == j) {
                for (int k = 1; k < j; k++) sum += pow(L[j][k], 2);
                L[j][j] = sqrt(A[j][j] - sum);
            } else {
                for (int k = 1; k < j; k++) sum += L[i][k] * L[j][k];
                L[i][j] = (A[i][j] - sum) / L[j][j];
            }
        }
    }
    afisareMatrice(L, n, "L (Cholesky)");
}

// 7. Factorizare QR folosind Gram-Schmidt
void factorizareQR(float A[MAX][MAX], float Q[MAX][MAX], float R[MAX][MAX], int n) {
    for (int k = 1; k <= n; k++) {
        float norm = 0;
        for (int i = 1; i <= n; i++) norm += A[i][k] * A[i][k];
        R[k][k] = sqrt(norm);
        for (int i = 1; i <= n; i++) Q[i][k] = A[i][k] / R[k][k];
        for (int j = k + 1; j <= n; j++) {
            R[k][j] = 0;
            for (int i = 1; i <= n; i++) R[k][j] += Q[i][k] * A[i][j];
            for (int i = 1; i <= n; i++) A[i][j] -= Q[i][k] * R[k][j];
        }
    }
    afisareMatrice(Q, n, "Q");
    afisareMatrice(R, n, "R");
}

int main() {
    int n;
    float a[MAX][MAX], x[MAX], L[MAX][MAX] = {0}, U[MAX][MAX] = {0}, Q[MAX][MAX] = {0}, R[MAX][MAX] = {0};

    citesteMatriceExtinsa(a, n);

    cout << "Gauss cu pivotare totală: " << endl;
    gaussPivotareTotala(a, x, n);
    afisareSolutii(x, n);

    cout << "Inversa folosind Gauss-Jordan: " << endl;
    gaussJordanInversa(a, n);

    cout << "Factorizare LU și rezolvare: " << endl;
    factorizareLU(a, L, U, n);

    // Rezolvăm sistemul pentru factorizarea LU
    float b[MAX] = {0}; // Termenii liberi
    float y[MAX]; // Soluția intermediară
    for (int i = 1; i <= n; i++) {
        b[i] = a[i][n + 1];
    }

    rezolvaInferioara(L, b, y, n); // L * y = b
    rezolvaSuperioara(U, y, x, n); // U * x = y
    afisareSolutii(x, n);

    cout << "Factorizare Cholesky (L^T L) și rezolvare: " << endl;
    factorizareCholesky(a, L, n);
    rezolvaInferioara(L, b, y, n); // L * y = b
    rezolvaSuperioara(L, y, x, n); // L^T * x = y
    afisareSolutii(x, n);

    cout << "Factorizare QR: " << endl;
    factorizareQR(a, Q, R, n);

    return 0;
}
