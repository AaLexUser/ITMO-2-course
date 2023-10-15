//
// Created by Alexey Lapin on 3/18/23.
//

#ifndef COMPLMATH2_NONLINEAREQUATIONS_H
#define COMPLMATH2_NONLINEAREQUATIONS_H


#include "IEquations.h"

#include "graph/MainWindow.h"

class NonlinearEquations : public IEquations{
    public:
        void process() override;
};


#endif //COMPLMATH2_NONLINEAREQUATIONS_H
