//
// Created by Alexey Lapin on 3/18/23.
//

#include "NonlinearEquations.h"
#include "methods/nonlinear/HalfDivisionMethod.h"
#include "methods/nonlinear/SecantMethod.h"
#include "methods/nonlinear/SimpleIterationMethod.h"
#include "methods/nonlinear/NewtonMethod.h"
#include "graph/draw/Axis.h"
#include "graph/draw/AxisNumbers.h"
#include "graph/draw/Grid.h"
#include "graph/draw/FuncGraph.h"
#include <unordered_map>
#include <thread>
#include "validator/Validator.h"
void NonlinearEquations::process() {
    std::unordered_map<int, double(*)( double)> function;
    function[1] = [](double x) { return x * x * x - x + 4; };
    function[2] = [](double x) { return sin(x*x)+0.5; };
    function[3] = [](double x) { return -2.4*x*x*x+1.27*x*x+8.63*x+2.31; };
    function[4] = [](double x) { return log(x) + 1.5*x + abs(x*x); };
    function[5] = [](double x) { return 2*x*x*x - 1.89*x*x - 5*x +2.34; };
    int chose;
    std::cout<< "1. y = x^3 - x + 4\n" << "2. y = sin(x^2) + 0.5\n"
                << "3. y = -2.4*x^3 + 1.27x^2 + 8.63x + 2.31\n"
                << "4. y = ln(x) + 1.5x + |x^2|\n" << "5. y = 2x^3 - 1.89x^2 - 5x + 2.34\n";
    std::cin >> chose;
    auto func = function[chose];
    std::vector<std::unique_ptr<IShape>> shapes;
    shapes.push_back(std::make_unique<Axis>(3));
    shapes.push_back(std::make_unique<AxisNumbers>());
    shapes.push_back(std::make_unique<Grid>(1));
    shapes.push_back(std::make_unique<FuncGraph>(func, 100.0));
    MainWindow::getInstance().setShapes(shapes);
    MainWindow::getInstance().display();
    double a, b, tolerance;
    std::cout << "Enter a, b, tolerance: ";
    std::cin >> a >> b >> tolerance;
    try{
        if(!Validator::validateUniquenessOfRoots(a, b, func)){
            std::cout << "There are no roots in this interval \n";
            return;
        }
    }
    catch (std::exception &e){
        std::cout << e.what() << std::endl;
        return;
    }
    std::string fun;
    std::cout << "1. Half division method\n" << "2. Secant method\n"
              << "3. Simple iteration method\n" << "4. Newton's method\n" << "5. Exit\n";
    std::cin >> chose;
    std::unique_ptr<IMethod> method;
    switch(chose){
        case 1: {
            std::cout << "Half division method\n";
            method = std::make_unique<HalfDivisionMethod>(a, b, tolerance,func);
            break;
        }
        case 2: {
            std::cout << "Secant method\n";
            method = std::make_unique<SecantMethod>(a, b, tolerance,func);
            break;
        }
        case 3: {
            std::cout << "Simple iteration method\n";
            method = std::make_unique<SimpleIterationMethod>(a, b, tolerance,func);
            break;
        }
        case 4: {
            std::cout << "Newton's method\n";
            method = std::make_unique<NewtonMethod>(a,b, tolerance,func);
            break;
        }
        case 5:
            return;
        default:
            std::cout << "Wrong input\n";
            return;
    }
    try {
        method->solve();
    }
    catch (std::exception &e){
        std::cout << e.what() << std::endl;
        return;
    }
}
