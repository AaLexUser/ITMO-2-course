#include <iostream>
#include "SystemsNonlinearEquations.h"
#include "NonlinearEquations.h"

int main()
{
    int choice;
    std::cout << "1. Nonlinear equations\n" << "2. Systems nonlinear equations\n" << "3. Exit\n";
    std::cin >> choice;
    switch(choice){
        case 1: {
            std::unique_ptr<IEquations> nonlinearEquations = std::make_unique<NonlinearEquations>();
            nonlinearEquations->process();
            break;
        }
        case 2: {
            std::unique_ptr<IEquations> systemsNonlinearEquations = std::make_unique<SystemsNonlinearEquations>();
            systemsNonlinearEquations->process();
            break;
        }
        case 3:
            return 0;
        default:
            std::cout << "Wrong input\n";
            return 0;
    }
    return 0;
}
