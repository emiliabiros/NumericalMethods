#include "vectalg.h"

void swap(double& a, double& b) {
    double temp = a;
    a = b;
    b = temp;
}

Vector calcNorms(const Matrix& A) {
    size_t n = A.size();
    Vector norms(n);

    for (size_t i = 0; i < n; i++) {
        double maxVal = 0.;
        for (size_t j = 0; j < n; j++) {
            double absVal = abs(A(i, j));
            if (absVal > maxVal) {
                maxVal = absVal;
            }
        }
        norms[i] = maxVal;
    }
    return norms;
}

Vector solveEquations(const Matrix& A, const Vector& b, double eps);

Vector iterativeRefinement (const Matrix& A, const Vector& b, double eps, Vector& x) {
    Vector residualVector = residual_vector(A, b, x);
    size_t n = A.size();

    while (residualVector.max_norm() >= eps) {
        Vector e = solveEquations(A, residualVector, eps);
        for (int i = 0; i < n; i++) {
            x[i] += e[i];
        }
        residualVector = residual_vector(A, b, x);
    }
    return x;
}

Vector solveEquations(const Matrix& A, const Vector& b, double eps) {
    size_t n = A.size();
    Matrix matrix(A);
    Vector vector(b);
    Vector norms = calcNorms(matrix);

    for (size_t i = 0; i < n; i++) {
        size_t maxId = i;
        double maxVal = abs(matrix(i, i)) / norms[i];

        for (size_t j = i + 1; j < n; j++) {
            double currentVal = abs(matrix(j, i)) / norms[j];
            if (currentVal > maxVal) {
                maxId = j;
                maxVal = currentVal;
            }
        }

        if (maxId != i) {
            for (size_t j = 0; j < n; j++) {
                swap(matrix(i, j), matrix(maxId, j));
            }
            swap(vector[i], vector[maxId]);
            swap(norms[i], norms[maxId]);
        }

        for (size_t j = i + 1; j < n; j++) {
            double factor = matrix(j, i) / matrix(i, i);
            for (size_t k = i; k < n; k++) {
                matrix(j, k) -= factor * matrix(i, k);
            }
            vector[j] -= factor * vector[i];
        }
    }

    Vector result(n);
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (size_t j = i + 1; j < n; j++) {
            sum += matrix(i, j) * result[j];
        }
        result[i] = (vector[i] - sum) / matrix(i, i);
    }

    result = iterativeRefinement(A, b, eps, result);

    return result;
}