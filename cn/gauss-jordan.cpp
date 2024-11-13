#include<iostream>
#include<cstdlib>

using namespace std;

int gaussJ() {
    float a[10][10], x[10], ratio;
    int i, j, k, n;

    // g++ main.cpp -o main
    cout << "Gauss-Jordan" << endl;

    // Intrari
    // Citirea numărului de necunoscute
    cout << "n = ";
    cin >> n;

    // Citirea matricei extinse
    cout << endl << "Introduceti coeficientii matricei extinse: " << endl;
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n + 1; j++) {
            cout << "a[" << i << "][" << j << "] = ";
            cin >> a[i][j];
        }

        cout << endl;
    }

    // Aplicarea metodei Gauss-Jordan
    for (i = 1; i <= n; i++) {
        if (a[i][i] == 0.0) {
            cout << "Eroare matematica!";
            exit(0);
        }

        for (j = 1; j <= n; j++) {
            if (i != j) {
                ratio = a[j][i] / a[i][i];
                for (k = 1; k <= n + 1; k++) {
                    a[j][k] = a[j][k] - ratio * a[i][k];
                }
            }
        }
    }

    // Obtinerea solutiei */
    for (i = 1; i <= n; i++) {
        x[i] = a[i][n + 1] / a[i][i];
    }

    // Afisarea solutiei
    cout << endl << "Solutie: " << endl;
    for (i = 1; i <= n; i++) {
        cout << "x[" << i << "] = " << x[i] << endl;
    }

    return (0);
}
