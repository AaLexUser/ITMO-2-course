#include <iostream>

#include "methods/RectangleMethod.h"
#include "methods/TrapezoidMethod.h"
#include "methods/SimpsonMethod.h"
#include <unordered_map>
#include <cmath>
#include "utils/Validator.h"
int main() {
    int choice;
    std::unordered_map<int, double(*)( double)> function;
    function[1] = [](double x) { return 1 / (1 + x * x); };
    function[2] = [](double x) { return x*x; };
    function[3] = [](double x) { return 5*x*x*x - 2 * x * x + 3 * x - 15 ; };
    function[4] = [](double x) { return sin(x) ; };
    function[5] = [](double x) { return 1 / sqrt(x); };
    function[6] = [](double x) { return 1 / (1 - x); };
    function[7] = [](double x) { return 1 / abs(1 - x); };
    std::cout << "Choose function:" << std::endl;
    std::cout << "1. 1 / (1 + x * x)" << std::endl;
    std::cout << "2. x^2" << std::endl;
    std::cout << "3. 5x^3 - 2x^2 + 3x - 15" << std::endl;
    std::cout << "4. sin(x)" << std::endl;
    std::cout << "5. 1 / sqrt(x)" << std::endl;
    std::cout << "6. 1 / (1 - x)" << std::endl;
    std::cout << "7. 1 / |1 - x|" << std::endl;
    std::cin >> choice;
    auto func = function[choice];
    std::cout << "Choose method:" << std::endl;
    std::cout << "1. Rectangle method" << std::endl;
    std::cout << "2. Trapezoid method" << std::endl;
    std::cout << "3. Simpson method" << std::endl;
    std::cin >> choice;
    double tolerance;
    std::cout << "Enter tolerance:" << std::endl;
    std::cin >> tolerance;
    double a, b;
    std::cout << "Enter a, b:" << std::endl;
    std::cin >> a >> b;
    if(!Validator::validateConvergence(a, b, func, tolerance, choice)){
        std::cout << "Not converge" << std::endl;
        return 0;
    }
    std::unique_ptr<IMethod> method;
    switch (choice) {
        case 1:
            int choice2;
            std::cout << "1. Left rectangle method" << std::endl;
            std::cout << "2. Right rectangle method" << std::endl;
            std::cout << "3. Middle rectangle method" << std::endl;
            std::cin >> choice2;
            method = std::make_unique<RectangleMethod>(a, b, tolerance, func, choice2);
            break;
        case 2:
            method = std::make_unique<TrapezoidMethod>(a, b, tolerance, func);
            break;
        case 3:
            method = std::make_unique<SimpsonMethod>(a, b, tolerance, func);
            break;
        default:
            std::cout << "Wrong choice" << std::endl;
            return 0;
    }
    std::pair<double, double> res = method->solve();
    std::cout << "n = " << res.first << std::endl;
    int st = round(abs(log10(tolerance)));
    const double multiplier = std::pow(10.0, st);
    std::cout << "I = " <<  ceil(res.second * multiplier) / multiplier << std::endl;
    return 0;
}
