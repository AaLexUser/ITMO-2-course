//
// Created by Alexey Lapin on 4/19/23.
//

#ifndef COMPLMATH4_APPROXIMATIONENUM_H
#define COMPLMATH4_APPROXIMATIONENUM_H
enum ApproximationEnum{
#   define X(a) a,
#   include "ApproximationEnum.def"
#   undef X
};
char const* const approximation_str[] = {
#   define X(a) #a,
#   include "ApproximationEnum.def"
#   undef X
        0
};

#endif //COMPLMATH4_APPROXIMATIONENUM_H
