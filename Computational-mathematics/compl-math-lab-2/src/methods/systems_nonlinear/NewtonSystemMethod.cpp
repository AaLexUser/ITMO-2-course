#include "NewtonSystemMethod.h"
#include "../linear/KramerRule.h"

void NewtonSystemMethod::solve() {
    double dxf = MathUtils::partialDerivative(f_, x0_, y0_);
    double dyf = MathUtils::partialDerivative(f_, x0_, y0_, 0.0001, false);
    double dxg = MathUtils::partialDerivative(g_, x0_, y0_);
    double dyg = MathUtils::partialDerivative(g_, x0_, y0_, 0.0001, false);
    double a[2][2] = {{dxf, dyf}, {dxg, dyg}};
    double b[2] = {-f_(x0_, y0_), -g_(x0_, y0_)};
    KramerRule::solve(a, b, roots_);
    double x1 = x0_ + roots_[0];
    double y1 = y0_ + roots_[1];
    if (abs(x1 - x0_) < tolerance_ && abs(y1 - y0_) < tolerance_) {
        int n = round(abs(log10(tolerance_)));
        const double multiplier = std::pow(10.0, n);
        std::cout << "x = " << ceil(x1 * multiplier) / multiplier << std::endl;
        std::cout << "y = " << ceil(y1 * multiplier) / multiplier << std::endl;
        std::cout << "f(x, y) = " << ceil(f_(x1, y1) * multiplier) / multiplier << std::endl;
        std::cout << "g(x, y) = " << ceil(g_(x1, y1) * multiplier) / multiplier << std::endl;
        std::cout << "|x - x0| = " << abs(x1 - x0_) << std::endl;
        std::cout << "|y - y0| = " << abs(y1 - y0_) << std::endl;
        std::cout << "counter = " << counter_ << std::endl;
        return;
    } else {
        x0_ = x1;
        y0_ = y1;
        counter_++;
        solve();
    }
}

NewtonSystemMethod::NewtonSystemMethod(double x0, double y0, double tolerance, double (*f)(double, double),
                                       double (*g)(double, double))
                                       : ISystemMethod(x0, y0, tolerance, f, g){

}
