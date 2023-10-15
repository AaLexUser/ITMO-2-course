//
// Created by Alexey Lapin on 3/18/23.
//

#include "SystemsNonlinearEquations.h"
#include "python/CPython.h"
#include <unordered_map>


void SystemsNonlinearEquations::process() {
    std::unordered_map<int, std::pair<double(*)(double, double), double(*)(double, double)>> functions;
    functions[1] = {[](double x, double y) { return x*x + y*y - 4; },
                    [](double x, double y) { return -3*x*x + y; }};
    functions[2] = {[](double x, double y) { return 0.1*x*x+x+0.2*y*y-0.3; },
                    [](double x, double y) { return 0.2*x*x+y+0.1*x*y-0.7; }};
    functions[3] = {[](double x, double y) { return abs(x)+abs(y)-4; },
                    [](double x, double y) { return abs(x*x-y*y)-1; }};
    int chose;
    std::cout << "1.\tf1(x,y) = x^2 + y^2 - 4\n\tf2(x,y) = -3x^2 + y\n"
            << "2.\tf1(x,y) = 0.1x^2 + x + 0.2y^2 - 0.3\n\tf2(x,y) = 0.2x^2 + y + 0.1xy - 0.7\n"
            << "3.\tf1(x,y) = |x| + |y| - 4\n\tf2(x,y) = |x^2 - y^2| - 1\n";
    std::cin >> chose;
    CPython python;
    python.choose_functions_and_plot(chose);
    double x0, y0, tolerance;
    std::cout << "Enter x0, y0, tolerance: ";
    std::cin >> x0 >> y0 >> tolerance;

    NewtonSystemMethod newtonSystemMethod(x0, y0, tolerance, functions[chose].first, functions[chose].second);
    newtonSystemMethod.solve();
}