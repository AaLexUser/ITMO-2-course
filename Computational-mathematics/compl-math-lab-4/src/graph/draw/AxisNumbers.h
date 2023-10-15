//
// Created by Alexey Lapin on 3/17/23.
//

#ifndef COMPLMATH2_AXISNUMBERS_H
#define COMPLMATH2_AXISNUMBERS_H


#include "AbstractShape.h"

class AxisNumbers : public AbstractShape{
public:
    void draw() override;
    [[nodiscard]] std::unique_ptr<IShape> clone() const override;
private:
};


#endif //COMPLMATH2_AXISNUMBERS_H
