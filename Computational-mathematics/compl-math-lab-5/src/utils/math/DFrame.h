//
// Created by Alexey Lapin on 4/15/23.
//

#ifndef COMPLMATH4_NDARRAY_H
#define COMPLMATH4_NDARRAY_H

#include <vector>
template<typename T>
class DFrame{
public:
    static DFrame<T> from_vector(std::vector<std::vector<T>> data) {
        return DFrame<T>(data);
    }
private:
    std::vector<std::vector<T>> _data;
};
extern DFrame<int> df;

#endif //COMPLMATH4_NDARRAY_H
