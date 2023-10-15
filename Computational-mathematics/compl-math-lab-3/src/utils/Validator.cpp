//
// Created by Alexey Lapin on 4/6/23.
//

#include "Validator.h"
#include "../methods/SimpsonMethod.h"
#include "../methods/IMethod.h"
#include "../methods/RectangleMethod.h"
#include "../methods/TrapezoidMethod.h"


bool Validator::validateConvergence(double & a, double & b, double (*f)(double), double tolerance, int choice) {
    if(!validatePoint(a, f)){
        if(validatePoint(a+1e-9, f)){
            a += 1e-9;
            return true;
        }
        return false;
    }
    if(!validatePoint(b, f)){
        if(validatePoint(b-1e-9, f)){
            b -= 1e-9;
            return true;
        }
        return false;
    }
    if(!validateInterval(a, b, f, tolerance, choice)){
        return false;
    }
    return true;
}

bool Validator::validatePoint(double a, double (*f)(double)) {
    if(std::isnan(f(a)) || std::isinf(f(a)) || f(a) > 1e+8 || f(a) < -1e+8) {
        return false;
    }
    return true;
}

bool Validator::validateInterval(double a, double b, double (*f)(double), double tolerance, int choice) {
    double h = (b - a)/100;
    for(double i = 0; i <= 100; i++){
        if(!validatePoint(a + i * h, f)) {
            std::unique_ptr<IMethod> method;
            std::pair<double, double> res1, res2;
            double delta = 1e-5;
            double cr = a + i * h - delta;
            double cl = a + i * h + delta;
            switch (choice) {
                case 1: {
                    int choice2;
                    std::cout << "1. Left rectangle method" << std::endl;
                    std::cout << "2. Right rectangle method" << std::endl;
                    std::cout << "3. Middle rectangle method" << std::endl;
                    std::cin >> choice2;
                    method = std::make_unique<RectangleMethod>(a, cr, tolerance, f, choice2);
                    std::cout << "Please wait..." << std::endl;
                    res1 = method->solve();
                    method = std::make_unique<RectangleMethod>(cl, b, tolerance, f, choice2);
                    res2 = method->solve();
                    std::cout << "n: " << std::max(res1.first, res2.first) << " I: " << res1.second + res2.second
                              << std::endl;
                    break;
                }
                case 2: {
                    method = std::make_unique<TrapezoidMethod>(a, cr, tolerance, f);
                    std::cout << "Please wait..." << std::endl;
                    res1 = method->solve();
                    method = std::make_unique<TrapezoidMethod>(cl, b, tolerance, f);
                    res2 = method->solve();
                    std::cout << "n: " << std::max(res1.first, res2.first) << " I: " << res1.second + res2.second
                              << std::endl;
                    break;
                }
                case 3: {
                    method = std::make_unique<SimpsonMethod>(a, cr, tolerance, f);
                    std::cout << "Please wait..." << std::endl;
                    res1 = method->solve();
                    method = std::make_unique<SimpsonMethod>(cl, b, tolerance, f);
                    res2 = method->solve();
                    std::cout << "n: " << std::max(res1.first, res2.first) << " I: " << res1.second + res2.second
                              << std::endl;
                    break;
                }
                default:
                    std::cout << "Wrong choice" << std::endl;
                    exit(0);
                    return false;

            }
            exit(0);
            return false;
        }
    }
    return true;
}




