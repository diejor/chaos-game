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
                output::debug("Middle Point between " + p1.to_string() + " and " + p2.to_string() +
                              " is " + middle.to_string() + " with displacement " +
                              displacement.to_string());
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

    // take the the 1/ths displacement between this point and other
    Point Point::displacement_by(const Point& other, int percentage = 100) const {
        Point dsplcmt = displacement(other);
        dsplcmt.row *= percentage / 100.0;
        dsplcmt.col *= percentage / 100.0;
        return dsplcmt;
    }

    Point Point::rotate(int degrees) const {
        Point result;
        double radians = degrees * M_PI / 180.0;
        result.col = col * cos(radians) - row * sin(radians);
        result.row = col * sin(radians) + row * cos(radians);
        return result;
    }

    double Point::distance(const Point& other) const {
        Point dsplcmt = displacement(other);
        return sqrt(pow(dsplcmt.row, 2) + pow(dsplcmt.col, 2));
    }

    bool Point::operator==(const Point& other) const {
        return row == other.row && col == other.col;
    }

    string Point::to_string() const {
        string result = "(" + std::to_string(row) + ", " + std::to_string(col) + ")";
        return result;
    }

}  // namespace grid
