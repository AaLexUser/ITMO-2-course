//
// Created by Alexey Lapin on 3/18/23.
//

#ifndef COMPLMATH2_SYSTEMSNONLINEAREQUATIONS_H
#define COMPLMATH2_SYSTEMSNONLINEAREQUATIONS_H


#include "IEquations.h"
#include "methods/systems_nonlinear/NewtonSystemMethod.h"
class SystemsNonlinearEquations : public IEquations {
    public:
        void process() override;

};


#endif //COMPLMATH2_SYSTEMSNONLINEAREQUATIONS_H
