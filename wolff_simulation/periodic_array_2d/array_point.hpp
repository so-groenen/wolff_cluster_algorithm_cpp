#ifndef ARRAY_POINT_HPP
#define ARRAY_POINT_HPP
#include <iostream>

namespace periodic_array_2d
{
    struct ArrayPoint
    {
        int x{};
        int y{};
        ArrayPoint() = default;
        ArrayPoint(int X, int Y)
            : x{X}, y{Y}
        {}   
        ~ArrayPoint() = default;
        bool operator==(const ArrayPoint& other) const = default;
    };
}


#endif