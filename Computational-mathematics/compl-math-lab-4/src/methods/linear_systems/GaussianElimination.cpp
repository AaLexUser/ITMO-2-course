//
// Created by Alexey Lapin on 4/12/23.
//

#include "GaussianElimination.h"

std::vector<double> GaussianElimination::solve(std::vector<std::vector<double>> A, std::vector<double> b) {
    std::vector<double> x(A.size());
    solve(A, b, x);
    return x;
}

void GaussianElimination::solve(std::vector<std::vector<double>> &A, std::vector<double> &b, std::vector<double> &x) {
    int n = A.size();
    // Gaussian elimination with partial pivoting
    for (int i = 0; i < n; i++) {
        // find pivot row and swap with current row
        int max_row = i;
        for (int j = i+1; j < n; j++) {
            if (abs(A[j][i]) > abs(A[max_row][i])) {
                max_row = j;
            }
        }
        if (max_row != i) {
            std::swap(A[i], A[max_row]);
            std::swap(b[i], b[max_row]);
        }
        const double eps = 1e-9; // tolerance for near-zero values
        // check for near-zero pivot element
        if (abs(A[i][i]) < eps) {
            std::cerr << "Error: near-zero pivot element" << std::endl;
            exit(1);
        }

        // eliminate lower triangular elements
        for (int j = i+1; j < n; j++) {
            double mult = A[j][i] / A[i][i];
            for (int k = i; k < n; k++) {
                A[j][k] -= mult * A[i][k];
            }
            b[j] -= mult * b[i];
        }
    }
    const double multiplier = std::pow(10.0, 6);
    // back substitution to solve for x
    for (int i = n-1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i+1; j < n; j++) {
            sum += A[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / A[i][i];

    }
}
