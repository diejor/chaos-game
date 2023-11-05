#include <vector>

#include "polygon.hpp"

using namespace std;
using namespace grid;

namespace grid {
    Polygon::Polygon(vector<Point> vertices, Point center) {
        this->vertices = vertices;
        this->center = center;
    }

    Polygon::Polygon(Point center, int num_rotations, int radius) {
        int step_degree = 360 / num_rotations;
        this->center = center;
        for (int i = 0; i < num_rotations; i++) {
            Point radius_point = Point(0, radius);
            Point p = Point(-radius, 0).rotate(step_degree * i);
            p = p.add(center);
            vertices.push_back(p);
        }
    }
}  // namespace grid
