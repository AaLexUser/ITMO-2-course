//
// Created by Alexey Lapin on 4/26/23.
//

#include "Menu.h"

void Menu::addStep(IStep *step) {
    steps.push_back(step);
}

void Menu::run() {
    for (auto step : steps) {
        step->run();
    }
}
