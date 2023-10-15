//
// Created by Alexey Lapin on 3/16/23.
//

#ifndef COMPLMATH2_AXIS_H
#define COMPLMATH2_AXIS_H

#include "../MainWindow.h"
#include "AbstractShape.h"

class Axis : public AbstractShape{
public:
    explicit Axis(int thickness) : thickness_(thickness) {}
    void draw() override;
    [[nodiscard]] std::unique_ptr<IShape> clone() const override;
private:
    int thickness_;
};


#endif //COMPLMATH2_AXIS_H
