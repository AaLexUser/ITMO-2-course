#include "SecantMethod.h"

void SecantMethod::solve() {
    double x2 = x1_ - f_(x1_) * (x1_ - x0_) / (f_(x1_) - f_(x0_));
    if(abs(x2 - x1_) < tolerance_){
        int n = round(abs(log10(tolerance_)));
        const double multiplier = std::pow(10.0, n);
        std::cout << "x = " <<  ceil(x2 * multiplier) / multiplier << std::endl;
        std::cout << "f(x) = " <<  ceil(f_(x2) * multiplier) / multiplier << std::endl;
        std::cout << "counter = " << counter << std::endl;
        return;
    }
    else {
        x0_ = x1_;
        x1_ = x2;
        counter++;
        solve();
    };

}

SecantMethod::SecantMethod(double a, double b, double tolerance, double (*f)(double))
    : IMethod(a, b, f, tolerance){
    if(f_(a) * MathUtils::secondDerivative(f_, a) > 0){
        x0_ = a;
    } else {
        x0_ = b;
    }
    x1_ = x0_ + 0.5;

}
