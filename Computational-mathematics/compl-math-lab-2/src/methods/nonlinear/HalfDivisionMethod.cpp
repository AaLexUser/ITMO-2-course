#include "HalfDivisionMethod.h"

void HalfDivisionMethod::solve() {
    double x = (a_ + b_) / 2;
    if(f_(a_) * f_(x) > 0){
        a_ = x;
    } else {
        b_ = x;
    }
    if(abs(a_- b_) < tolerance_){
        x = (a_ + b_) / 2;
        int n = round(abs(log10(tolerance_)));
        const double multiplier = std::pow(10.0, n);
        std::cout << "x = " << ceil(x * multiplier) / multiplier << std::endl;
        std::cout << "f(x) = " << ceil(f_(x) * multiplier) / multiplier  << std::endl;
        std::cout << "counter = " << counter << std::endl;
        return;
    }
    else { counter++; solve();};
}
