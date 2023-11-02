#include <cmath>
#include "string"


#include "global.hpp"
#include "output.hpp"
#include "point.hpp"


using namespace std;

namespace grid {

    namespace debug {
        void middle_point(const Point& p1, const Point& p2, const Point& displacement,
                          const Point& middle) {
            if (global::debug_flags::MIDDLE_POINT) {
                output::debug("Middle Point between " + p1.to_string() + " and " +
                              p2.to_string() + " is " + middle.to_string() +
                              " with displacement " + displacement.to_string());
            }
        }
    }  // namespace debug

    Point Point::add(const Point& other) const {
        Point result;
        result.row = row + other.row;
        result.col = col + other.col;
        return result;
    }

    Point Point::subtract(const Point& other) const {
        Point result;
        result.row = row - other.row;
        result.col = col - other.col;
        return result;
    }

    Point Point::displacement(const Point& other) const {
        Point result;
        result.row = other.row - row;
        result.col = other.col - col;
        return result;
    }

    Point Point::dsplcmt_to_middle(const Point& other) const {
        Point displacement = this->displacement(other);
        displacement.row /= 2;
        displacement.col /= 2;
        return displacement;
    }

    Point Point::rotate(int degrees) const {
        Point result;
        double radians = degrees * M_PI / 180.0;
        result.col = col * cos(radians) - row * sin(radians);
        result.row = col * sin(radians) + row * cos(radians);
        return result;
    }

    string Point::to_string() const {
        string result = "(" + std::to_string(row) + ", " + std::to_string(col) + ")";
        return result;
    }

    vector<Point> polygon(const Point& center, int num_rotations, int radius) {
        vector<Point> result;
        int step_degree = 360 / num_rotations;
        for (int i = 0; i < num_rotations; i++) {
            Point radius_point = Point(0, radius);
            Point p = Point(-radius,0).rotate(step_degree * i);
            p = p.add(center);
            result.push_back(p);
        }
        return result;
    }
}  // namespace grid
