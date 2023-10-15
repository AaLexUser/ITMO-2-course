//
// Created by Alexey Lapin on 4/6/23.
//

#ifndef COMPLMATH3_VALIDATOR_H
#define COMPLMATH3_VALIDATOR_H

#include <iostream>
class Validator {
public:
    static bool validateConvergence(double & a, double & b, double (*f)(double), double tolerance, int choice);
    static bool validatePoint(double a, double (*f)(double));
private:
    static bool validateInterval(double a, double b, double (*f)(double), double tolerance, int choice);

};


#endif //COMPLMATH3_VALIDATOR_H
