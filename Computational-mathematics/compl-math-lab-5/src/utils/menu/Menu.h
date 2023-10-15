//
// Created by Alexey Lapin on 4/26/23.
//

#ifndef COMPLMATH5_MENU_H
#define COMPLMATH5_MENU_H

#include "IStep.h"
#include <vector>
class Menu {
    std::vector<IStep *> steps;
public:
    void addStep(IStep *step);
    void run();
    IStep *getStep(int index);

};


#endif //COMPLMATH5_MENU_H
