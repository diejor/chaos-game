#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>

#include "point.hpp"

using namespace std;
using namespace grid;

namespace grid {
    struct Polygon {
        vector<Point> vertices;
        Point center;

        Polygon(vector<Point> vertices, Point center);

        Polygon(Point center, int num_rotations, int radius);
    };
}  // namespace grid

#endif  // POLYGON_HPP
