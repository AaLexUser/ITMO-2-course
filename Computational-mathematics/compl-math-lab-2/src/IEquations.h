//
// Created by Alexey Lapin on 3/18/23.
//

#ifndef COMPLMATH2_IEQUATIONS_H
#define COMPLMATH2_IEQUATIONS_H

#include <iostream>

class IEquations {
    public:
        virtual void process() = 0;
        virtual ~IEquations() = default;
};


#endif //COMPLMATH2_IEQUATIONS_H
