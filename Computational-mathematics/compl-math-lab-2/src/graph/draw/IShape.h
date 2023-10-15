//
// Created by Alexey Lapin on 3/19/23.
//

#ifndef COMPLMATH2_ISHAPE_H
#define COMPLMATH2_ISHAPE_H
class IShape{
public :
    virtual void draw() = 0;
    virtual ~IShape() = default;
    [[nodiscard]] virtual std::unique_ptr<IShape> clone() const = 0;
};
#endif //COMPLMATH2_ISHAPE_H
