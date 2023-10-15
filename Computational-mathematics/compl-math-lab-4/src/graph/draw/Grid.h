//
// Created by Alexey Lapin on 3/16/23.
//

#ifndef COMPLMATH2_GRID_H
#define COMPLMATH2_GRID_H

#include "AbstractShape.h"

class Grid : public AbstractShape{
public:
    explicit Grid(int thickness) : thickness_(thickness) {}
    void draw() override;
    [[nodiscard]] std::unique_ptr<IShape> clone() const override;
private:
    int thickness_;
};


#endif //COMPLMATH2_GRID_H
