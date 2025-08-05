#include <iostream>
using namespace std;

void SOR(double** bands, const double* diagonal, const double* b, double* x, int iterations, int n, double w, int M) {
    auto* x0 = new double[n];

    for (int i = 0; i < n; i++) {
        x0[i] = x[i];
    }

    for (int iter = 0; iter < iterations; iter++) {
        for (int i = 0; i < n; i++) {
            double s = b[i];

            for (int m = max(0, i - M); m < i; m++) {
                s -= bands[i - m - 1][m] * x0[m];
            }

            for (int m = i + 1; m < min(n, i + M + 1); m++) {
                s -= bands[m - i - 1][i] * x0[m];
            }

            x0[i] = (1 - w) * x0[i] + w * s / diagonal[i];
        }

        for (int i = 0; i < n; i++) {
            x[i] = x0[i];
        }
    }

    delete[] x0;
}

int main() {
    cout.precision(10);
    cout << scientific;

    int N, M;
    cin >> N >> M;

    auto** bands = new double*[M];
    for (int i = 0; i < M; i++) {
        bands[i] = new double[N];
        for (int j = 0; j < N; j++) {
            bands[i][j] = 0.;
        }
    }

    for (int i = M - 1; i >= 0; i--) {
        for (int j = 0; j < N - i - 1; j++) {
            cin >> bands[i][j];
        }
    }

    auto* diagonal = new double[N];
    for (int i = 0; i < N; i++) {
        cin >> diagonal[i];
    }

    auto* y = new double[N];
    for (int i = 0; i < N; i++) {
        cin >> y[i];
    }

    auto* x = new double[N];
    for (int i = 0; i < N; i++) {
        cin >> x[i];
    }

    double w;
    int iterations;
    cin >> w >> iterations;

    SOR(bands, diagonal, y, x, iterations, N, w, M);

    for (int i = 0; i < N; i++) {
        cout << x[i] << endl;
    }

    for (int i = 0; i < M; i++) {
        delete[] bands[i];
    }

    delete[] bands;
    delete[] diagonal;
    delete[] y;
    delete[] x;

    return 0;
}