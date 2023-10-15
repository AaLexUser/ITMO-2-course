#include "SimpleIterationMethod.h"

void SimpleIterationMethod::solve() {
    double x1 = phi(x0_, sigma_, f_);
    if(abs(x1 - x0_) < tolerance_){
        int n = round(abs(log10(tolerance_)));
        const double multiplier = std::pow(10.0, n);
        std::cout << "x = " << ceil(x1 * multiplier) / multiplier  << std::endl;
        std::cout << "f(x) = " << ceil(f_(x1) * multiplier) / multiplier  << std::endl;
        std::cout << "counter = " << counter << std::endl;
        return;
    }
    else {
        x0_ = x1;
        counter++;
        solve();
    };
}


double SimpleIterationMethod::phi(double x, double sigma, double (*f)(double)) {
    return x - f(x) / sigma;
}

SimpleIterationMethod::SimpleIterationMethod(double a, double b, double tolerance, double (*f)(double))
    : IMethod(a,b,f, tolerance){
    x0_ = abs(MathUtils::derivative(f_, a_)) > abs(MathUtils::derivative(f, b_)) ? a_ : b_;
    sigma_ = abs(MathUtils::derivative(f_, x0_));
    if(1-MathUtils::derivative(f_,a)/sigma_ >= 1 &&
         1-MathUtils::derivative(f_,b)/sigma_ >= 1
    ) {
        throw std::runtime_error("Method does not converge");
    }
}
