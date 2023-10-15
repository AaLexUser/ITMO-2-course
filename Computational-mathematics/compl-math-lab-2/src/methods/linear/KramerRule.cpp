//
// Created by Alexey Lapin on 3/18/23.
//

#include "KramerRule.h"

void KramerRule::solve(double a[][2], const double b[], double* x) {
    double d = a[0][0] * a[1][1] - a[0][1] * a[1][0];
    double dx = b[0] * a[1][1] - b[1] * a[0][1];
    double dy = a[0][0] * b[1] - a[1][0] * b[0];
    x[0] = dx / d;
    x[1] = dy / d;
}
