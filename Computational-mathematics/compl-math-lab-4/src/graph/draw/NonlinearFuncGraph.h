//
// Created by Alexey Lapin on 3/21/23.
//

#ifndef COMPLMATH2_NONLINEARFUNCGRAPH_H
#define COMPLMATH2_NONLINEARFUNCGRAPH_H

#include "AbstractShape.h"
#include <cmath>
class NonlinearFuncGraph  : public AbstractShape{
public:
    NonlinearFuncGraph(double (*)(double x, double y), double);
    void draw() override;
    [[nodiscard]] std::unique_ptr<IShape> clone() const override;
private:
    double (*f_)(double x, double y);
    double pointsPerSegment_;
    double leftX_;
    double rightX_;
    double downY_;
    double upY_;
};


#endif //COMPLMATH2_NONLINEARFUNCGRAPH_H
